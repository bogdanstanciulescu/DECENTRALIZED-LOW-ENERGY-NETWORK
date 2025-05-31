// Bibliotecile necesare pentru funcționarea LoRa, WiFi și server web
#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <RadioLib.h>

// Inițializare modul LoRa cu pinii specifici
SX1262 radio = new Module(SS, DIO0, RST_LoRa, BUSY_LoRa);

// Inițializare server DNS și server web
DNSServer dnsServer;
WebServer server(80);

// Capacitate maximă a istoricului de mesaje și durata lor de păstrare
#define MAX_MESAJE 20
String istoricMesaje[MAX_MESAJE];
unsigned long mesajTimp[MAX_MESAJE];
int mesajIndex = 0;
const unsigned long DURATA_MESAJ_MS = 600000; // 10 minute

// Nume de utilizator implicit
String username = "DLEN";

// Pagina HTML servită utilizatorului pentru interfața de chat WiFi
const char htmlPage[] = R"=====(<!DOCTYPE html>
 <html>
<head>
  <meta charset="UTF-8">
  <title>!DLEN!</title>
  <style>
    body { font-family: sans-serif; background: #f5f5f5; margin: 0; padding: 0; display: flex; flex-direction: column; height: 100vh; font-size: 1.2em; }
    #chat { flex: 1; padding: 0.5em; overflow-y: auto; display: flex; flex-direction: column; }
    .msg { max-width: 70%; padding: 0.7em 1.2em; margin: 0.4em 0; border-radius: 1em; word-wrap: break-word; }
    .recv { align-self: flex-start; background: #e0e0e0; }
    .sent { align-self: flex-end; background: #007bff; color: white; }
    #inputZone { display: flex; border-top: 1px solid #ccc; padding: 0.6em; background: white; }
    #msgInput { flex: 1; padding: 0.7em; border: 1px solid #ccc; border-radius: 0.8em; font-size: 0.9em; }
    button { margin-left: 0.6em; padding: 0.7em 1.2em; background: #007bff; color: white; border: none; border-radius: 0.8em; cursor: pointer; font-size: 0.9em; }
    #usernameBtn { background: #28a745; margin-left: 0; border-radius: 0.8em 0.8em 0 0; padding: 0.5em 1em; font-size: 0.9em; }
    #printBtn { position: absolute; top: 0.5em; right: 0.5em; padding: 0.5em 1em; background: #6c757d; color: white; border: none; border-radius: 0.5em; cursor: pointer; font-size: 0.9em; z-index: 1000; }
  </style>
</head>
<body>
  <button id="usernameBtn" onclick="schimbaUsername()">Setează username</button>
  <button id="printBtn" onclick="window.print()">Printare</button>
  <div id="chat"></div>
  <div id="inputZone">
    <input type="text" id="msgInput" placeholder="Scrie un mesaj...">
    <button onclick="trimite()">Trimite</button>
  </div>
  <script>
    const chat = document.getElementById('chat');
    const msgInput = document.getElementById('msgInput');
    const usernameBtn = document.getElementById('usernameBtn');
    let ultimele = "";
    let username = "";

    function adaugaMesaj(text, tip) {
      const div = document.createElement('div');
      div.className = 'msg ' + tip;
      div.innerText = text;
      chat.appendChild(div);
      chat.scrollTop = chat.scrollHeight;
    }

    function trimite() {
      const text = msgInput.value.trim();
      if (text.length === 0) return;
      fetch('/send?mesaj=' + encodeURIComponent(text))
        .then(res => res.text())
        .then(res => {
          if (res.includes("succes")) {
            adaugaMesaj("Eu: " + username + ": " + text, "sent");
            msgInput.value = "";
          } else {
            alert("Eroare: " + res);
          }
        });
    }

    function schimbaUsername() {
      const nou = prompt("Introdu noul username:", username);
      if (nou && nou.trim().length > 0) {
        fetch('/setusername?name=' + encodeURIComponent(nou.trim()))
          .then(res => res.text())
          .then(res => {
            if (res.includes("OK")) {
              username = nou.trim();
              usernameBtn.innerText = "Username: " + username;
            } else {
              alert("Eroare la setarea username-ului.");
            }
          });
      }
    }

    fetch('/getusername')
      .then(res => res.text())
      .then(name => {
        username = name.trim();
        usernameBtn.innerText = "Username: " + username;
      });

    msgInput.addEventListener("keypress", e => {
      if (e.key === "Enter") trimite();
    });

    setInterval(() => {
      fetch('/recv')
        .then(res => res.text())
        .then(txt => {
          if (txt !== ultimele) {
            ultimele = txt;
            chat.innerHTML = "";
            txt.trim().split("\n").forEach(line => {
              const tip = line.startsWith("Eu:") ? "sent" : "recv";
              adaugaMesaj(line, tip);
            });
          }
        });
    }, 1000);
  </script>
</body>
</html>
)====="; // Cod HTML și JavaScript
// Adaugă un mesaj nou în istoric și salvează timpul lui
void adaugaMesaj(const String& mesaj) {
  if (mesajIndex >= MAX_MESAJE) mesajIndex = 0;
  istoricMesaje[mesajIndex] = mesaj;
  mesajTimp[mesajIndex] = millis();
  mesajIndex++;
}

// Șterge mesajele care au depășit timpul de viață (10 minute)
void stergeMesajeExpirate() {
  unsigned long acum = millis();
  for (int i = 0; i < MAX_MESAJE; i++) {
    if (!istoricMesaje[i].isEmpty() && acum - mesajTimp[i] > DURATA_MESAJ_MS) {
      istoricMesaje[i] = "";
    }
  }
}

// Decodifică parametrii URL (e.g. %20 devine spațiu)
String urlDecode(const String& input) {
  String decoded = "";
  char c;
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == '%') {
      if (i + 2 < input.length()) {
        char hex[3] = { input[i + 1], input[i + 2], 0 };
        c = strtol(hex, nullptr, 16);
        decoded += c;
        i += 2;
      }
    } else if (input[i] == '+') {
      decoded += ' ';
    } else {
      decoded += input[i];
    }
  }
  return decoded;
}

// Servește pagina HTML la accesarea rădăcinii "/"
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Trimite un mesaj LoRa primit prin web și îl adaugă în istoric
void handleSend() {
  if (server.hasArg("mesaj")) {
    String mesaj = urlDecode(server.arg("mesaj"));
    mesaj.trim();
    if (mesaj.length() > 0) {
      String mesajComplet = "[" + username + "] " + username + ": " + mesaj;
      int status = radio.transmit(mesajComplet.c_str());
      if (status == RADIOLIB_ERR_NONE) {
        adaugaMesaj("Eu: " + mesajComplet);
        server.send(200, "text/plain", "Trimis cu succes!");
        return;
      } else {
        server.send(500, "text/plain", "Eroare la transmit()!");
        return;
      }
    }
  }
  server.send(400, "text/plain", "Parametru 'mesaj' lipsă!");
}

// Trimite toate mesajele din istoric către clientul web
void handleRecv() {
  String toate = "";
  for (int i = 0; i < MAX_MESAJE; i++) {
    if (!istoricMesaje[i].isEmpty()) {
      toate += istoricMesaje[i] + "\n";
    }
  }
  server.send(200, "text/plain", toate);
}

// Setează username-ul nou primit din interfață
void handleSetUsername() {
  if (server.hasArg("name")) {
    String numeNou = server.arg("name");
    numeNou.trim();
    if (numeNou.length() > 0 && numeNou.length() < 20) {
      username = numeNou;
      server.send(200, "text/plain", "OK");
      Serial.printf("Username schimbat în: %s\n", username.c_str());
      return;
    }
  }
  server.send(400, "text/plain", "Nume invalid!");
}

// Returnează username-ul curent
void handleGetUsername() {
  server.send(200, "text/plain", username);
}

// Redirecționează automat orice alt URL către pagina principală
void handleNotFound() {
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "redirect");
}

// Inițializare LoRa, WiFi (mod AP), DNS și web server
void setup() {
  Serial.begin(115200);
  while (!Serial);

  int status = radio.begin(868.0); // frecvență LoRa
  if (status != RADIOLIB_ERR_NONE) {
    Serial.printf("radio init eșuat: %d\n", status);
    while (true);
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP("DLEN-DEVICE");
  dnsServer.start(53, "*", WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.on("/recv", handleRecv);
  server.on("/setusername", handleSetUsername);
  server.on("/getusername", handleGetUsername);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Serverul a pornit!");
}

// Bucle de rulare continuă: procesează DNS, HTTP, curăță mesaje și ascultă LoRa
void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  stergeMesajeExpirate();

  String mesajRecep;
  int state = radio.receive(mesajRecep);
  if (state == RADIOLIB_ERR_NONE) {
    mesajRecep.trim();
    if (mesajRecep.length() == 0) return;

    adaugaMesaj(mesajRecep);
    Serial.println("Msg RX: " + mesajRecep);

    // Verifică dacă mesajul are un prefix de rutare (listă de ID-uri)
    int start = mesajRecep.indexOf('[');
    int end = mesajRecep.indexOf(']');
    if (start != -1 && end != -1 && end > start) {
      String idList = mesajRecep.substring(start + 1, end);

      std::vector<String> ids;
      int last = 0;
      while (true) {
        int sep = idList.indexOf('|', last);
        if (sep == -1) {
          ids.push_back(idList.substring(last));
          break;
        }
        ids.push_back(idList.substring(last, sep));
        last = sep + 1;
      }

      // Verifică dacă a fost deja procesat
      bool dejaRetransmis = false;
      for (const auto& id : ids) {
        if (id == username) {
          dejaRetransmis = true;
          break;
        }
      }

      // Dacă nu a fost procesat, retransmite mesajul cu prefix actualizat
      if (!dejaRetransmis) {
        ids.push_back(username);
        while (ids.size() > 5) {
          ids.erase(ids.begin()); // păstrează doar ultimele 5 ID-uri
        }

        String nouPrefix = "[";
        for (size_t i = 0; i < ids.size(); i++) {
          nouPrefix += ids[i];
          if (i < ids.size() - 1) nouPrefix += "|";
        }
        nouPrefix += "]";

        String mesajNou = nouPrefix + mesajRecep.substring(end + 1);
        int txStatus = radio.transmit(mesajNou.c_str());
        if (txStatus == RADIOLIB_ERR_NONE) {
          Serial.println("Retransmis: " + mesajNou);
        } else {
          Serial.println("Eroare la retransmitere!");
        }
      } else {
        Serial.println("Mesaj deja procesat — ignor.");
      }
    } else {
      // Dacă mesajul nu are prefix, adaugă unul și retransmite
      String nouMesaj = "[" + username + "]" + mesajRecep;
      int txStatus = radio.transmit(nouMesaj.c_str());
      if (txStatus == RADIOLIB_ERR_NONE) {
        Serial.println("Retransmis (fără prefix anterior): " + nouMesaj);
      }
    }
  }

  delay(10); // o mică întârziere pentru stabilitate
}
