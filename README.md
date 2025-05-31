# D.L.E.N. – Dispozitiv LoRa de Emitere a Notificărilor

## 📌 Introducere

**D.L.E.N.** este o soluție de comunicare prin mesaje text destinată uzului civil, în special în situații de urgență (dezastre naturale, război, etc.) sau ca metodă alternativă de control pentru automatizări. Proiectul oferă un canal de comunicare fiabil, descentralizat și accesibil, ce poate funcționa în absența infrastructurii GSM și a rețelelor electrice.

Aplicația este implementabilă rapid și cu costuri reduse, adresându-se instituțiilor publice, proprietăților private sau utilizatorilor individuali. Sistemul se bazează pe plăci de dezvoltare **Heltec ESP32 LoRa V3**, dotate cu microcontroller ESP32, modul LoRa și încărcare Li-Po prin USB-C.

---

## ⚙️ Funcționalitate

- Conectare prin rețeaua Wi-Fi emisă de dispozitiv
- Portal captiv redirecționează utilizatorul către o interfață web
- Trimitere și recepție mesaje în stil aplicații de mesagerie (Messenger, WhatsApp)
- Mesajele au un timp de viață de **10 minute**, dar pot fi salvate în PDF
- Fiecare mesaj are un **ID unic** și un **nume de utilizator** (modificabil)
- **Retransmitere automată** a mesajelor între plăci (tip rețea mesh)
- Mesajele sunt ignorate dacă:
  - Se întorc la expeditor
  - Sunt retransmise de mai mult de 5 ori

---

## 🧩 Proiectare

- Scris în **Arduino IDE**
- Rulat pe **Heltec ESP32 LoRa V3**
- Consum redus de energie: ~1W la 5V
- Funcționează fără infrastructură GSM
- Carcasă 3D printată din PLA (infill 100%) pentru protecție și portabilitate

---

## 📡 Protocolul de comunicare: LoRa

LoRa (Long Range) este o tehnologie de comunicație radio pe distanțe lungi, eficientă energetic și fără licență, utilizată frecvent în rețelele IoT.

Dispozitivul folosește implicit **banda EU868**, dar poate fi adaptat ușor pentru următoarele benzi disponibile în funcție de regiune:

- **EU433 / EU868** – Europa
- **US915** – America de Nord
- **AU915 / AS923** – Asia și America de Sud
- **IN865** – India

---

## 🖥️ Interfața

- Interfață simplă, intuitivă și accesibilă oricui, indiferent de vârstă sau nivel digital
- Inspirată de aplicațiile de chat populare

---

## 🛠️ Tehnologii utilizate

- `Arduino.h` – definiții și funcții standard
- `WiFi.h` – creare punct de acces Wi-Fi
- `DNSServer.h` – DNS pentru portal captiv
- `WebServer.h` – server web
- `RadioLib.h` – comunicație LoRa

---

## 🔧 Instalare

### Cerințe:

1. **Placă Heltec ESP32 LoRa V3**
2. **Arduino IDE**
3. **Driver USB Silabs**: [Descarcă aici](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

### Configurare Arduino IDE:

- Adaugă următoarele linkuri în `Preferences > Additional Board URLs`:
  - `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
  - `https://resource.heltec.cn/download/package_heltec_esp32_index.json`

- Instalează placa **Heltec ESP32 LoRa V3** din Boards Manager
- Instalează bibliotecile necesare din Library Manager

### Pași:

1. Clonează repository-ul
2. Deschide folderul proiectului în Arduino IDE
3. Încarcă sketch-ul pe placa Heltec
4. Alimentează placa (prin USB sau baterie Li-Po)
5. Conectează-te la rețeaua Wi-Fi emisă de placă
6. Accesează interfața web și începe comunicarea

---

## 🔗 Resurse externe

- [LoRa – Wikipedia](https://en.wikipedia.org/wiki/LoRa)
- [Documentație Heltec ESP32](https://docs.heltec.org/en/node/esp32/wifi_lora_32/index.html)
- [Imagine schemă Heltec](https://docs.heltec.org/en/node/esp32/_images/055.jpg)
- [ESP32 Board URL](https://espressif.github.io/arduino-esp32/package_esp32_index.json)
- [Heltec Board URL](https://resource.heltec.cn/download/package_heltec_esp32_index.json)

---

## ✅ Concluzie

**D.L.E.N.** este o aplicație robustă, descentralizată și ușor de implementat, oferind un canal de comunicare fiabil în situații critice, când infrastructura clasică (GSM, electricitate) poate fi compromisă. Ideală pentru situații de urgență, acest sistem poate reprezenta un element vital pentru protejarea vieții și a echipamentelor.

---

# 🌐 English Version

## Introduction

**D.L.E.N.** is a backup/emergency message communication solution designed for civil use. It can also be adapted to control automated equipment via messages. The system targets both civilian protection and automated systems management, offering a reliable communication channel during natural disasters, war, or network failures.

This solution can be implemented quickly and at low cost for public institutions, private properties, or individuals. It is based on the **Heltec ESP32 LoRa V3** development board, which includes an ESP32 microcontroller, a LoRa module, and Li-Po charging via USB-C.

---

## Features

- User connects to the device's Wi-Fi hotspot
- Redirected to a captive portal with a messaging interface
- Simple UI inspired by chat apps (Messenger, WhatsApp)
- Messages last for **10 minutes** unless saved as PDF
- Every message has a unique **ID** and a **customizable username**
- Automatic retransmission of messages between boards (mesh-like behavior)
- Messages are discarded if:
  - They return to the sender
  - They are retransmitted more than 5 times

---

## Design

- Developed in **Arduino IDE**
- Runs on **Heltec ESP32 LoRa V3**
- Low power usage (~1W at 5V)
- Fully operational without GSM or power grid
- 3D printed PLA case (100% infill) for protection and mobility

---

## Communication Protocol: LoRa

LoRa (Long Range) is a low-power, long-range radio communication protocol often used in IoT networks.

This project uses the **EU868** band by default, but the following bands are also supported based on region:

- **EU433 / EU868** – Europe
- **US915** – North America
- **AU915 / AS923** – Asia & South America
- **IN865** – India

---

## Interface

- Simple, intuitive, and easy to use regardless of age or digital literacy
- Works like popular messaging platforms

---

## Dependencies & Libraries

- `Arduino.h`
- `WiFi.h`
- `DNSServer.h`
- `WebServer.h`
- `RadioLib.h`

---

## Installation

### Requirements

1. **Heltec ESP32 LoRa V3 board**
2. **Arduino IDE**
3. **USB driver**: [Download from Silabs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

### Arduino IDE setup

- Add to **Preferences > Additional Board URLs**:
  - `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
  - `https://resource.heltec.cn/download/package_heltec_esp32_index.json`

- Install the board and required libraries from the Library and Board Managers.

### Steps

1. Clone this repository
2. Open the folder in Arduino IDE
3. Upload the sketch to your Heltec board
4. Power the device (USB or Li-Po)
5. Connect to its Wi-Fi network
6. Open the portal and start sending/receiving messages

---

## External Resources

- [LoRa – Wikipedia](https://en.wikipedia.org/wiki/LoRa)
- [Heltec Documentation](https://docs.heltec.org/en/node/esp32/wifi_lora_32/index.html)
- [Board Image](https://docs.heltec.org/en/node/esp32/_images/055.jpg)
- [ESP32 JSON](https://espressif.github.io/arduino-esp32/package_esp32_index.json)
- [Heltec JSON](https://resource.heltec.cn/download/package_heltec_esp32_index.json)

---

## Final Notes

**D.L.E.N.** is a lightweight, offline, and decentralized messaging platform for emergency use. It can operate during power outages and network failures, making it ideal for disaster preparedness or field deployment.
