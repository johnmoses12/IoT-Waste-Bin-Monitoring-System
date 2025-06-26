# 🗑️ IoT-Based Waste Bin Monitoring System

A smart IoT solution to monitor garbage levels in bins and alert the user for timely cleaning. This project uses an ultrasonic sensor with a NodeMCU to measure the fill level and update data to a real-time IoT dashboard.

---

## 🚀 Project Overview

This system solves the problem of manual checking of garbage bins in smart cities or office spaces. When the bin reaches a certain threshold, it can send notifications for cleaning.

---

## ⚙️ Technologies Used

- **NodeMCU (ESP8266)** – WiFi-enabled microcontroller
- **Ultrasonic Sensor (HC-SR04)** – Measures the garbage level
- **Arduino IDE** – For programming
- **Blynk / ThingSpeak** – For real-time monitoring dashboard
- **Jumper Wires, Breadboard** – For circuit connection

---

## 📦 Project Features

- Real-time fill level monitoring
- Wireless data transmission via Wi-Fi
- Threshold alert system (can be extended to SMS/email)
- Ideal for smart city waste management

---

## 🧠 My Role

- Designed the circuit using TinkerCAD
- Programmed the NodeMCU in Arduino IDE using C/C++
- Integrated with Blynk IoT platform
- Tested alert conditions and optimized sensor readings

---

## 🔧 How It Works

1. Ultrasonic sensor continuously checks the garbage level.
2. NodeMCU sends data to Blynk/ThingSpeak via Wi-Fi.
3. Dashboard shows bin status in real-time.

---


## 📁 Folder Structure

/IoT-Waste-Bin-Monitoring-System
│
├── iot_bin_code.ino
├── README.md
├── circuit_diagram.png
└── /media
