# 🏥 InnoVitals — IoT-Based Smart Health Monitoring and Emergency Response System

An advanced IoT-enabled health monitoring system designed for real-time patient monitoring and emergency response. Built on **ESP32** with multiple biosensors, it continuously tracks critical physiological parameters and sends instant emergency alerts via **Telegram Bot API**.

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-blue?style=flat-square)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=flat-square&logo=arduino&logoColor=white)
![Telegram](https://img.shields.io/badge/Telegram-Bot%20API-26A5E4?style=flat-square&logo=telegram&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Health%20Monitoring-green?style=flat-square)

---

## 📸 Hardware Setup / Demo

> <img width="823" height="1129" alt="WhatsApp Image 2026-04-14 at 12 34 55 PM (1)" src="https://github.com/user-attachments/assets/f38fde9f-8a59-4d87-a71b-a12ce79bc438" />
<img width="823" height="1129" alt="WhatsApp Image 2026-04-14 at 12 34 55 PM (1)" src="https://github.com/user-attachments/assets/07eac9ab-5594-47d4-a558-ac8b3c87feb7" />
<img width="1228" height="1015" alt="Screenshot (2)" src="https://github.com/user-attachments/assets/64479ec8-0f06-4675-be6f-89a993612016" />


---

## ✨ Features

| Feature | Description |
|---|---|
| 💓 SpO₂ & Heart Rate | Real-time blood oxygen and heart rate monitoring via MAX30102 |
| 🌡️ Temperature | Continuous body temperature tracking |
| 🤸 Fall Detection | Sudden fall detection using MPU-6050 Accelerometer |
| 📍 GPS Tracking | Live location tracking via NEO-6M GPS module |
| 📲 Telegram Alerts | Instant health updates and emergency notifications |
| 🆘 SOS Button | Hardware button for rapid emergency assistance requests |
| 👨‍⚕️ Remote Monitoring | Caregivers access real-time patient data remotely |

---

## 🛠️ Tech Stack

| Technology | Purpose |
|---|---|
| ESP32 Microcontroller | Core processing unit |
| Embedded C / Arduino IDE | Firmware development |
| MAX30102 Sensor | SpO₂ and Heart Rate measurement |
| MPU-6050 | Accelerometer and Gyroscope for fall detection |
| NEO-6M GPS Module | Real-time location tracking |
| Temperature Sensor | Body temperature monitoring |
| Telegram Bot API | Wireless health data and alert transmission |
| IoT Communication Protocols | Wireless data transfer |

---

## 🔧 Hardware Components

- ESP32 Microcontroller
- MAX30102 SpO₂ and Heart Rate Sensor
- Temperature Sensor
- MPU-6050 Accelerometer and Gyroscope
- NEO-6M GPS Module
- SOS Push Button
- Power Supply Module

---

## 📐 Circuit Diagram

> _Add your circuit diagram or Fritzing schematic image here_

---

## 🚀 Getting Started

### 1. Clone the repository
```bash
git clone https://github.com/SaiRithwik28/innovitals-health-monitor.git
cd innovitals-health-monitor
```

### 2. Install Arduino IDE & ESP32 Board
- Download [Arduino IDE](https://www.arduino.cc/en/software)
- Add ESP32 board URL in Preferences:
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
- Go to Tools → Board Manager → search **ESP32** → Install

### 3. Install Required Libraries
In Arduino IDE → Tools → Manage Libraries, install:
- `MAX30105` by SparkFun
- `TinyGPS++` by Mikal Hart
- `MPU6050` by Electronic Cats
- `UniversalTelegramBot` by Brian Lough
- `ArduinoJson` by Benoit Blanchon
- `OneWire` + `DallasTemperature`

### 4. Configure credentials
Open the main `.ino` file and update:
```cpp
// Wi-Fi credentials
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram Bot
#define BOT_TOKEN  "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID    "YOUR_TELEGRAM_CHAT_ID"
```

### 5. Upload to ESP32
- Connect ESP32 via USB
- Select board: **ESP32 Dev Module**
- Select correct COM port
- Click **Upload**

---

## 🧠 System Architecture

```
Sensors collect patient health parameters
        ↓
ESP32 processes and analyzes sensor data
        ↓
MPU-6050 detects sudden falls or abnormal movement
        ↓
GPS module retrieves real-time location coordinates
        ↓
Telegram Bot API sends health updates and alerts
        ↓
Caregivers receive alerts and respond immediately
```

---

## 📲 How to Set Up Telegram Bot

1. Open Telegram → search **@BotFather**
2. Send `/newbot` → follow instructions → copy the **Bot Token**
3. Search **@userinfobot** → send `/start` → copy your **Chat ID**
4. Paste both values in the code as shown above

---

## 🚨 Alert Thresholds

| Vital | Normal Range | Alert Triggered |
|---|---|---|
| Heart Rate | 60–100 BPM | < 50 or > 120 BPM |
| SpO₂ | 95–100% | < 90% |
| Temperature | 36.1–37.2°C | > 38.5°C |
| Fall Detection | No fall | Sudden acceleration spike |

---

## 🏥 Applications

- 👴 Elderly Care Monitoring
- 🏠 Home Healthcare Systems
- 🩺 Remote Patient Monitoring
- 💊 Chronic Disease Management
- 🚑 Emergency Medical Assistance

---

## 🔮 Future Enhancements

- [ ] ☁️ Cloud-based health data storage
- [ ] 🤖 AI-powered health anomaly prediction
- [ ] 📱 Mobile application integration
- [ ] 📊 Medical report generation and analytics dashboard
- [ ] 👥 Multi-patient monitoring support

---

## 👤 Author

**Maganti Sai Rithwik**
📧 sunnysairithwik@gmail.com
🔗 [GitHub](https://github.com/SaiRithwik28)

---

## ⭐ Acknowledgements

- [Ultralytics YOLOv8](https://github.com/ultralytics/ultralytics)
- [Streamlit](https://streamlit.io)
- [UniversalTelegramBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus)
- [SparkFun MAX30105](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library)
