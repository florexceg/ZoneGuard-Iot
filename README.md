# 🏥 ZoneGuard
### IoT-Based Restricted Zone Patient Monitoring System

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![MQTT](https://img.shields.io/badge/MQTT-HiveMQ-orange)
![Node--RED](https://img.shields.io/badge/Node--RED-Dashboard-red)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 📖 Overview

ZoneGuard is an IoT-based patient monitoring system designed to enhance safety in hospital restricted zones. The system continuously monitors patient movement using multiple ESP32 nodes and provides real-time updates through an interactive Node-RED dashboard.

Whenever a patient moves from the assigned room to the corridor or reaches the exit, the system instantly updates the dashboard and generates alerts, allowing hospital staff to respond quickly.

---

## 🎯 Problem Statement

Patients in hospitals, especially those with cognitive impairments or under observation, may unintentionally enter restricted areas or attempt to leave designated zones. Continuous manual monitoring is difficult and increases the workload on healthcare staff.

ZoneGuard provides an automated monitoring solution that detects patient movement across different hospital zones and immediately alerts medical personnel when unauthorized movement occurs.

---

## 💡 Solution

ZoneGuard uses multiple ESP32-based monitoring nodes connected through the MQTT protocol using HiveMQ. Each node represents a hospital zone and publishes patient movement events in JSON format.

A central Gateway ESP32 receives emergency events and activates a buzzer when a patient reaches the exit. Simultaneously, Node-RED displays real-time patient information, movement history, timestamps, and alert status on a live dashboard.

---

# ✨ Features

- ✅ Real-time patient movement monitoring
- ✅ MQTT-based communication using HiveMQ
- ✅ ESP32 multi-node architecture
- ✅ Live Node-RED dashboard
- ✅ JSON-based messaging
- ✅ Emergency buzzer alert
- ✅ Live patient status banner
- ✅ Activity Log with movement history
- ✅ System status monitoring
- ✅ Timestamped events

---

# 🛠 Hardware Used

- ESP32 Development Boards (4)
- Push Buttons
- Active Buzzer
- Breadboards
- Jumper Wires
- USB Power Supply

---

# 💻 Software Used

- Arduino IDE
- Wokwi Simulator
- Node-RED Dashboard 2.0
- HiveMQ Public Broker
- GitHub

---

# 🏗 System Architecture

```
          ROOM NODE
               │
               │
        CORRIDOR NODE
               │
               ▼
        MQTT (HiveMQ Broker)
               ▲
               │
          EXIT NODE
               │
               ▼
          Gateway ESP32
               │
        Emergency Buzzer
               │
               ▼
        Node-RED Dashboard
```

---

# 📡 MQTT Topics

| Topic | Purpose |
|--------|---------|
| zoneguard/floo2026/events | Patient movement events |
| zoneguard/floo2026/system | Gateway heartbeat and system status |

---

# 📂 Project Structure

```
ZoneGuard
│
├── code
│   ├── Gateway
│   ├── RoomNode
│   ├── CorridorNode
│   ├── ExitNode
│   └── Node-RED
│
├── hardware
├── simulation
├── diagrams
├── images
├── docs
│
└── README.md
```

---

# 🚀 Workflow

1. Patient movement is detected.
2. ESP32 node publishes a JSON event.
3. HiveMQ broker distributes the message.
4. Gateway receives emergency events.
5. Gateway activates buzzer for exit detection.
6. Node-RED updates the dashboard in real time.
7. Activity Log stores recent patient events.

---

# 📸 Screenshots

## Live Monitoring Dashboard

_Add screenshot from the `images` folder._

## Activity Log

_Add screenshot from the `images` folder._

## Wokwi Simulation

_Add screenshot from the `images` folder._

---

# 🔮 Future Enhancements

- BLE-based patient wristband tracking
- RSSI-based indoor localization
- Mobile application notifications
- Hospital database integration
- Multi-patient monitoring
- Secure authentication and encrypted communication

---

# 👩‍💻 Team

**Florence Bridget George**

Bachelor of Engineering (Electronics and Communication Engineering)

---

# 📜 License

This project is released under the MIT License.
