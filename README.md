# DECENTRALIZED-LOW-ENERGY-NETWORK
Introducere:
D.L.E.N. este o soluție de comunicare prin mesaje (de urgență/de rezervă pentru uz civil) și poate fi ușor adaptată pentru controlul automatizărilor prin mesaje.
Aplicația se adresează protecției civililor și a echipamentelor automatizate, oferind un canal de comunicare în caz de urgență (dezastre naturale, război etc.) cu autoritățile sau alți civili.
Aceasta poate fi implementată rapid și la costuri reduse, la nivelul instituțiilor publice, proprietăților private sau pentru persoane individuale.
Programul funcționează pe baza plăcilor de dezvoltare Heltec, cu microcontroller ESP32, modul LoRa și modul de încărcare a acumulatorului Li-Po. 
Alimentarea și încărcarea firmware-ului se realizează prin portul USB-C. 
Modulul LoRa permite transmiterea rapidă a mesajelor în caz de urgență. Microcontrollerul ESP32 se ocupă de portalul captiv de tip web server și de procesarea mesajelor.
[heltec](https://github.com/user-attachments/assets/dbe7e38d-718f-4415-877b-601e86b4a70f)
Funcționalitate:
Toată interacțiunea dintre utilizator și dispozitiv se realizează prin conectarea la rețeaua wireless a dispozitivului, după care utilizatorul este redirecționat într-un portal captiv web, de unde poate primi sau trimite mesaje.
Aceste mesaje pot fi citite timp de 10 minute, după care se șterg automat pentru a elibera memoria volatilă a microcontrollerului, dar ele pot fi salvate în format PDF prin butonul „Printează”.
Interfața este simplă, gândită pentru orice utilizator, indiferent de nivelul de alfabetizare digitală. 
Aceasta este concepută să semene cu aplicațiile de mesagerie (Messenger, WhatsApp etc.).
Mesajele transmise primesc un ID și numele utilizatorului – acesta poate fi modificat.
Pentru a mări raza de acțiune, mesajele sunt retransmise de fiecare placă de dezvoltare, similar unei rețele mesh. 
ID-ul este modificat pentru a reflecta traseul mesajului. Dacă mesajul ajunge înapoi la expeditor sau este retransmis de mai mult de 5 ori, acesta este ignorat și nu mai este retransmis.
Proiectare:
Codul a fost scris în Arduino IDE pentru mesageria LoRa și web serverul de tip portal captiv. Acesta este conceput pentru a funcționa pe o placă de dezvoltare open-source Heltec ESP32 LoRa V3.
Costurile de operare sunt scăzute, deoarece consumul de energie este de aproximativ 1W la o tensiune de 5V (curent direct sau dintr-o celulă Li-Po la 3,7V).
Spre deosebire de o rețea tradițională GSM, D.L.E.N. poate asigura comunicarea chiar și în situații în care rețelele de curent electric sunt afectate.
Pentru a-i oferi rezistență și portabilitate, există și o carcasă printată 3D din PLA, cu infill de 100%.
Protocolul de comunicare:
LoRa (de la „Long Range”, uneori abreviat ca „LR”) este o tehnologie fizică proprietară de comunicații radio. LoRa utilizează benzi de radiofrecvență sub-gigahertz fără licență:
EU433 (LPD433) sau EU868 (863–870/873 MHz) în Europa; AU915/AS923-1 (915–928 MHz) în America de Sud; US915 (902–928 MHz) în America de Nord; IN865 (865–867 MHz) în India; și AS923 (915–928 MHz) în Asia.
LoRa permite transmisii pe distanțe lungi cu consum redus de energie.
Este una dintre cele mai populare tehnologii de rețea pentru senzori wireless cu consum redus de energie, 
utilizată în implementarea Internetului Lucrurilor (IoT), oferind comunicații pe distanțe de peste 2 km – în comparație cu tehnologii precum Zigbee sau Bluetooth, dar cu rate de transfer mai mici.
Interfața:
Interfața este una simplă care este accesibilă tuturor indifferent de vârstă.
Tehnologii utilizate:
•	Arduino.h – bibliotecă ce conține multe definiții și articole standard.
•	WiFi.h – bibliotecă pentru crearea punctului de acces.
•	DNSServer.h – bibliotecă pentru serverul DNS al portalului captiv.
•	WebServer.h – bibliotecă pentru web server.
•	RadioLib.h – bibliotecă pentru funcționalitatea modulului LoRa.
Instalare:
Pentru a obține o aplicație complet funcțională, este necesar cel puțin un Heltec ESP32 LoRa V3, care dispune de conectivitate Wi-Fi.
Pasul 0:
Înainte de clonarea repository-ului, este necesară instalarea următoarelor:
•	Driverul pentru conexiune USB la Heltec ESP32 LoRa V3:
https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads
•	Arduino IDE pentru încărcarea sketch-urilor pe Heltec ESP32 LoRa V3.
•	Adăugarea următoarelor linkuri la preferințe în Arduino IDE:
o	https://espressif.github.io/arduino-esp32/package_esp32_index.json
o	https://resource.heltec.cn/download/package_heltec_esp32_index.json
•	Descărcarea din Library Manager și Boards Manager a plăcii Heltec ESP32 LoRa V3.
Pasul1:Copierea fișierelor într-un folder de lucru.
Pasul2:Deschiderea folderului în Arduino IDE.
Pasul3:Încărcarea sketch-ului în Heltec ESP32 LoRa V3.
Pasul4: Alimentează placa și conectează-te la rețeaua Wi-Fi emisă de aceasta.
Pasul5: Acum ești protejat de posibile întreruperi ale rețelelor GSM în caz de dezastru.
Resurse externe: Pentru documentare, s-au folosit, în afara resurselor indicate în restul acestui fișier, următoarele: 
https://en.wikipedia.org/wiki/LoRa 
https://docs.heltec.org/en/node/esp32/wifi_lora_32/index.html 
https://docs.heltec.org/en/node/esp32/_images/055.jpg
https://espressif.github.io/arduino-esp32/package_esp32_index.json https://resource.heltec.cn/download/package_heltec_esp32_index.json
Concluzie:
Am realizat o aplicație de comunicare prin mesaje text care nu necesită resurse semnificative, este descentralizată, și care poate fi folosită în caz de dezastre naturale, din cauza cărora rămânem fără current și semnal GSM.

