## 📚 PROJECT OVERVIEW
The goal is to create an intelligent, cloud-connected HVAC (Heating, Ventilation, and Air Conditioning) system for ship compartments. Built around an ESP8266 NodeMCU, it monitors temperature, humidity, occupancy, and CO₂ levels to optimize comfort and safety. Data and alerts are published to an MQTT broker for real-time remote monitoring and historical logging.

## 🛠️ SYSTEM BREAKDOWN
This system controls a compartment’s climate by:

1. **MEASURING**
   - **Temperature** & **Humidity** (DHT11)
   - **Occupancy** (HC-SR04 ultrasonic)
   - **CO₂ levels** (MQ-7 gas sensor)
   - **Real Time** (DS1307 RTC)

2. **DECIDING** (onboard logic)
   - Keep **T < 25 °C** & **RH < 65 %**
   - If **T > 25 °C** & **RH > 65 %** → **AC + Fan**
   - If **T < 16 °C** & **RH < 45 %** → **Heater**
   - If **T > 25 °C** & **RH < 45 %** → **AC**
   - If **T < 16 °C** & **RH > 65 %** → **Heater + Fan**
   - Else → **Fan only**
   - If occupied & **CO₂ > 600 ppm** → **Buzzer + CO₂ LED**

3. **ACTUATING**
   - **Relays** to switch AC, Heater, and Fan
   - **RGB LEDs** for visual status (Blue = AC, Red = Heater, Green = Fan)
   - **Red LED + Buzzer** for high CO₂ alerts

4. **PUBLISHING**
   - Periodically (every 5 s) publishes JSON to MQTT
   - Includes timestamp, sensor readings, occupancy, actuator states, and CO₂ alerts
  
## **📋 REQUIRED SENSORS AND ACTUATORS**
1. DHT11 Temperature & Humidity Sensor
2. HC-SR04 Ultrasonic Sensor          
3. MQ-135 (or MQ-7) Gas Sensor       
4. DS3231 RTC Module  
5. LEDs (Blue, Green, Red)          
6. Buzzer
7. Push Button
  
## 🔄 SYSTEM FLOWCHART
The diagram below offers a clear and accurate representation of the key components, data flow, and interactions within the system.
![ICPS Project Flowchart](https://drive.google.com/uc?export=view&id=1xr49en2aMgVQj5CqvhNXhS6kqXTkhjwu)
 
## 🏗️ SOFTWARE ARCHITECTURE
### LIBRARIES & MODULES
- **ESP8266WiFi** — Wi-Fi connectivity  
- **PubSubClient** — MQTT client  
- **DHT** — Temperature/Humidity sensor  
- **NewPingESP8266** — Ultrasonic sensor  
- **RTClib** — DS3231 real-time clock

### EXECUTION FLOW
1. **Initialization (`setup()`)**
   - Begin serial for debugging
   - Start sensors (DHT11, RTC)
   - Configure all pin modes
   - Connect to Wi-Fi & MQTT

2. **Main Loop (`loop()`)** (every 5 s)
   - Read **temperature**, **humidity**, and **distance**
   - Determine **occupancy** (`distance < MAX`)
   - **HVAC Logic**: evaluate threshold conditions → AC / Heater / Fan
   - **CO₂ Logic** (if occupied): read analog → if > 600 → buzzer + LED
   - **Actuate** relays + RGB LEDs
   - **Timestamp** via DS3231
   - **Publish** all data as JSON over MQTT
   - **Delay** 5 s

## 🔧 WIRING AND SCHEMATIC
<div align="center">
  <img src="https://drive.google.com/uc?export=download&id=1P42qf2cHBNUQQzMkL7WLdpFppDT91BOX" alt="Project Wiring"/>
  <p><strong></strong> Wiring diagram of the HVAC system</p>
</div>

<br/>

<div align="center">
  <img src="https://drive.google.com/uc?export=download&id=1_1VugGr0SF2_nVfZqP1FCs67FGAofiqy" alt="Project Schematic"/>
  <p><strong></strong> Schematic layout of the system architecture</p>
</div>


## ✨ FEATURES
- **Autonomous Decision Making**  
  All control logic runs on the ESP8266 — No external controller needed.

- **Cloud Connectivity**  
  Wi-Fi + MQTT for remote monitoring, data logging, and alerting.

- **Occupancy-Aware CO₂ Alerts**  
  Only checks CO₂ when people are present → reduces false alarms.

- **Real-Time Clock (RTC)**  
  Timestamped data for accurate historical records.

