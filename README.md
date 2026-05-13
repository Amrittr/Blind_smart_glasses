# 📘 Blind Person Helper System (ESP32 Based)

![Project Status](https://img.shields.io/badge/Status-Complete-success)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)

## 🧠 1. Introduction

The **Blind Person Helper System** is an assistive technology project designed to help visually impaired individuals navigate safely. This system uses ultrasonic sensors to detect obstacles in three directions (front, left, right) and provides feedback using vibration motors.

Additionally, an **SOS emergency feature** is integrated using a touch sensor and Twilio API, allowing the user to send an emergency message to a predefined contact.

---

## 🎯 2. Objective

* **Detect obstacles** in real-time
* **Provide directional feedback** using vibration
* **Enable emergency communication** using SOS button
* Build a low-cost and wearable assistive device

---

## ⚙️ 3. Components Required

### 🔌 Main Components
* ESP32 Development Board
* 3 × Ultrasonic Sensors (HC-SR04)
* 2 × Coin Vibration Motors
* 1 × Touch Sensor (TTP223)

### ⚙️ Supporting Components
* 2 × BC547 Transistors
* 5 × 1kΩ Resistors
* 3 × 2kΩ Resistors
* Jumper wires
* Breadboard

### 🔋 Power Supply
* USB cable OR 5V battery / power bank

---

## 🔧 4. Working Principle

* Ultrasonic sensors measure distance using sound waves.
* If an obstacle is detected within **5 cm**:
  * **Front** → both motors vibrate
  * **Left** → left motor vibrates
  * **Right** → right motor vibrates
* **SOS button**:
  * When pressed → ESP32 connects to WiFi
  * Sends SMS using Twilio API

---

## 🔌 5. Pin Configuration

| Component   | GPIO Pin |
| ----------- | -------- |
| Front TRIG  | 18       |
| Front ECHO  | 19       |
| Left TRIG   | 21       |
| Left ECHO   | 22       |
| Right TRIG  | 23       |
| Right ECHO  | 27       |
| Left Motor  | 25       |
| Right Motor | 26       |
| SOS Button  | 14       |

---

## ⚠️ 6. Important Safety (Voltage Divider)

The Echo pin gives 5V, but the ESP32 accepts 3.3V only. 

**Use a voltage divider:**
* ECHO → 1kΩ → ESP32
* ESP32 → 2kΩ → GND

---

## 🔌 7. Motor Connection (Using Transistor)

For each motor:
* Motor (+) → 3.3V
* Motor (–) → Collector
* Emitter → GND
* Base → GPIO via 1k resistor

---

## 🧪 8. Testing Procedure

1. Power ON ESP32
2. Open Serial Monitor (115200 baud)
3. Move object near sensors
4. Check vibration response
5. Press SOS button → check SMS

---

## 🚀 9. Applications

* Assistive device for blind people
* Smart walking stick
* Indoor navigation aid

---

## 🔮 10. Future Enhancements

* GPS location sharing
* Voice feedback system
* Mobile app integration
* AI-based object detection

---

## 🏁 11. Conclusion

This project demonstrates how embedded systems and IoT can be used to create meaningful solutions for real-world problems. It enhances safety, independence, and accessibility for visually impaired individuals.
