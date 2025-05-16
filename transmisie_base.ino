#include <RadioLib.h>

// Creăm un obiect LoRa SX1262 cu pinii specifici
SX1262 lora = new Module(SS, DIO0, RST_LoRa, BUSY_LoRa);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Inițializare SX1262...");

  // Inițializare LoRa @ 868 MHz
  int status = lora.begin(868.0);
  if (status != RADIOLIB_ERR_NONE) {
    Serial.print("Eroare la inițializare LoRa, cod: ");
    Serial.println(status);
    while (true);
  }

  Serial.println("LoRa SX1262 OK!");
}

void loop() {
  // Trimite dacă se tastează ceva în Serial
  if (Serial.available()) {
    String mesaj = Serial.readStringUntil('\n');
    mesaj.trim();

    int status = lora.transmit(mesaj);
    if (status == RADIOLIB_ERR_NONE) {
      Serial.print("Trimis: ");
      Serial.println(mesaj);
    } else {
      Serial.print("Eroare la trimitere: ");
      Serial.println(status);
    }
  }

  // Ascultă pachet (non-blocant)
  String primire;
  int status = lora.receive(primire);

  if (status == RADIOLIB_ERR_NONE) {
    Serial.print("Primit: ");
    Serial.println(primire);
  }
}
