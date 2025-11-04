# smart-sunflower
# 🌻 Smart Sunflower Dual-Axis Solar Tracker (ESP32)

## 🔧 Overview
This project demonstrates a **dual-axis solar tracking system** using an **ESP32**, **four LDR (Light Dependent Resistors)**, and **two servo motors**.  
It automatically aligns a solar panel or sunflower model toward the brightest light source — mimicking how real sunflowers follow the sun throughout the day.

The code is a **merged version of two single-axis trackers**, controlling:
- **Servo 1 (Horizontal movement)** — based on Right and Left LDRs.  
- **Servo 2 (Vertical movement)** — based on East and West LDRs.

---

## 🧠 Features
- Dual-axis light tracking (East–West and Left–Right).  
- Smooth analog LDR readings with noise reduction (`smoothRead()` function).  
- Automatic night detection — centers servos when it’s dark.  
- Adjustable parameters for tolerance, servo limits, and step size.  
- Real-time debugging messages via Serial Monitor.

---

## ⚙️ Hardware Requirements
| Component | Quantity | Description |
|------------|-----------|-------------|
| ESP32 Dev Board | 1 | Main microcontroller |
| LDR Sensor | 4 | Light intensity sensors |
| Servo Motor | 2 | For petal movement (horizontal + vertical) |
| 10kΩ Resistors | 4 | Used in voltage divider circuits for LDRs |
| Breadboard + Wires | — | For connections |
| Power Supply (5V) | — | Powering servos safely |

---

## 🔌 Pin Connections

| Function | ESP32 Pin | Description |
|-----------|------------|-------------|
| Right LDR | 34 | Detects right-side light intensity |
| Left LDR | 32 | Detects left-side light intensity |
| East LDR | 25 | Detects east-side light intensity |
| West LDR | 26 | Detects west-side light intensity |
| Servo 1 Signal | 4 | Controls horizontal servo |
| Servo 2 Signal | 5 | Controls vertical servo |
| 5V | 5V Pin | Power for servos and LDRs |
| GND | GND | Common ground |

> ⚠️ Note: Ensure the servo power line is connected to a **separate 5V source** (with common GND) if current draw is high.

---

## 🧩 Working Principle

1. **Light Detection:**  
   Each pair of LDRs (Right–Left and East–West) measures the light intensity difference.  

2. **Signal Comparison:**  
   - If the right LDR reads higher → servo turns right.  
   - If the left LDR reads higher → servo turns left.  
   - If the difference is small → servos stay still.  

3. **Night Mode:**  
   When all LDR readings are below the `nightThreshold`, servos return to center (90°).

4. **Smooth Reading:**  
   The `smoothRead()` function averages multiple analog readings to avoid flickering movement due to noise.

---

## 🧾 Adjustable Parameters

| Variable | Description | Default |
|-----------|--------------|----------|
| `tolerance` | Minimum light difference to trigger movement | 150 |
| `nightThreshold` | Value below which it’s considered night | 3000 |
| `stepSize` | Degrees moved per update | 3 |
| `minPos` | Minimum servo angle | 30 |
| `maxPos` | Maximum servo angle | 170 |

---

## 📜 Code Summary
### 1. `setup()`
- Initializes Serial communication.  
- Attaches both servos to pins 4 and 5.  
- Calibrates system and sets servos to 90° (center).  

### 2. `smoothRead(pin)`
- Averages 5 analog readings per LDR to stabilize input.

### 3. `loop()`
- Reads all four LDRs.  
- Calculates differences (`diff1` for right/left, `diff2` for east/west).  
- Moves servos based on which side is brighter.  
- Centers servos in dark conditions.  
- Prints all activity to Serial Monitor for debugging.

---

## 🧠 Example Serial Output

```
🌻 Smart Sunflower Tracker Merged Version Started
System Calibrating... Ready!

Code1 | Right: 2100 | Left: 1300 | Diff: 800 | Servo Pos: 87
☀️ Code1 Right brighter → Turning Right
Code2 | East: 900 | West: 1800 | Diff: -900 | Servo Pos: 93
☀️ Code2 West brighter → Turning West
```

---

## 🛠️ Libraries Used
- **ESP32Servo.h** → Controls servo motors via PWM on ESP32.

Install via Arduino IDE:
```
Sketch → Include Library → Manage Libraries → Search "ESP32Servo"
```

---

## 🧾 Future Improvements
- Add OLED or LCD display to show live sensor readings.  
- Use PID control for smoother movement.  
- Log sunlight data over time using SD card or cloud.  
- Add solar panel voltage measurement for efficiency tracking.  

---

## 💡 Author & Credits
**Developed by:** Tejas chaudhari (Embedded Software Engineer)  
**Platform:** ESP32 (Arduino Framework)  
**Language:** C++  
**License:** MIT  
