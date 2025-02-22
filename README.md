# Smart Incubator Using ESP32 & Blynk

## Overview
A simple **Smart Incubator** using **ESP32**, **DHT11 sensor**, and **Blynk IoT** for remote monitoring and control of temperature and humidity.

## Features
- **Automated & Manual Mode** for temperature and humidity control.
- **Heating (Bulb) & Cooling (Fan) System** based on set thresholds.
- **Blynk App Integration** for real-time monitoring and manual adjustments.

## Components
- **ESP32** (Microcontroller)
- **DHT11** (Temperature & Humidity Sensor)
- **Relay Module** (Bulb Control)
- **Fan Motor** (Humidity Control)

## Setup
1. Clone Repository:  
   ```bash
   git clone https://github.com/your-username/smart-incubator.git
   ```
2. Install required libraries: `DHT sensor`, `Blynk`, `WiFi`.
3. Update WiFi and Blynk credentials in the code.
4. Upload the code to **ESP32** using Arduino IDE.
5. Monitor data via **Blynk App**.

## How It Works
- **First 18 Days:** Temp = 15°C, Humidity = 40%.
- **Last Days:** Temp = 45°C, Humidity = 70%.
- **Manual Mode:** Users can set custom values via **Blynk**.

## Blynk Controls
| Virtual Pin | Function             |
|------------|---------------------|
| V0         | Temperature Display |
| V1         | Humidity Display    |
| V2         | Toggle Manual Mode  |
| V3         | Set Temperature     |
| V4         | Set Humidity        |

## Troubleshooting
- Check sensor wiring if values are **NaN**.
- Verify **WiFi credentials** if Blynk doesn’t connect.

## Future Enhancements
- Add **LCD display**.
- Implement **data logging**.
- Use **PID control** for stability.
