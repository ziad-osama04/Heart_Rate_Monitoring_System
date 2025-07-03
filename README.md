
# **Arduino-Based Heart Rate Monitor with ECG Simulation**  

![IMG_7789](https://github.com/user-attachments/assets/44438372-78d8-48bc-a38f-ab77b4b7ca35)

---

## **📝 Table of Contents**  
1. [Project Overview](#-project-overview)  
2. [Features](#-features)  
3. [Hardware Components](#-hardware-components)  
4. [Software Requirements](#-software-requirements)  
5. [Circuit Diagram](#-circuit-diagram)  
6. [Installation & Setup](#-installation--setup)  
7. [How It Works](#-how-it-works)  
8. [Code Explanation](#-code-explanation)  
9. [Results & Demo](#-results--demo)  
10. [Contributing](#-contributing)  
11. [License](#-license)  
12. [Team](#-team)  

---

## **🌟 Project Overview**  
This project is an **Arduino-based Heart Rate Monitor** that measures heart rate using a Pulse Sensor and simulates an ECG-like signal for visualization. The system calculates the Beats Per Minute (BPM), displays the results on an LCD screen, and sends real-time data to the Serial Plotter for waveform visualization.  

---

## **✨ Features**  
- Real-time heart rate monitoring using a Pulse Sensor.  
- ECG-like signal simulation using Gaussian functions (P, QRS, and T waves).  
- Smoothing of the ECG signal using a moving average filter.  
- Error calculation based on normal heart rate ranges (60-100 BPM).  
- Status display ("Normal" or "Abnormal") on an LCD screen.  
- Real-time data visualization using the Arduino Serial Plotter.  

---

## **🛠️ Hardware Components**  
- Arduino Uno  
- Pulse Sensor  
- 16x2 LCD Screen  
- Jumper Wires  
- Breadboard  
- Resistors (if needed)  
- LED (for heartbeat detection)  

---

## **💻 Software Requirements**  
- Arduino IDE  
- Libraries:  
  - `PulseSensorPlayground` (for Pulse Sensor integration)  
  - `LiquidCrystal` (for LCD display)  

---

## **🔌 Circuit Diagram**  
![Installation with LCD 16x2](https://github.com/user-attachments/assets/294dbebc-15c1-46c8-abbb-382137a853b7)

**Connections:**  
- **Pulse Sensor**: Connect the signal wire to `A0`, VCC to `5V`, and GND to `GND`.  
- **LCD Screen**: Connect RS to `3`, E to `5`, D4 to `7`, D5 to `9`, D6 to `11`, D7 to `13`.  
- **LED**: Connect the anode to `PIN 1` and the cathode to `GND` (with a resistor).  

---

## **⚙️ Installation & Setup**  
1. Clone this repository:  
   ```bash
   git clone https://github.com/your-username/arduino-heart-rate-monitor.git
   ```  
2. Open the `arduino-heart-rate-monitor.ino` file in the Arduino IDE.  
3. Install the required libraries (`PulseSensorPlayground` and `LiquidCrystal`) via the Library Manager.  
4. Connect the hardware components as per the circuit diagram.  
5. Upload the code to your Arduino Uno.  
6. Open the Serial Monitor or Serial Plotter to view the results.  

---

## **🔄 How It Works**  
1. The **Pulse Sensor** detects the heartbeat and sends the analog signal to the Arduino.  
2. The Arduino processes the signal, filters it, and calculates the heart rate (BPM).  
3. The **LCD screen** displays the heart rate, error percentage, and status (Normal/Abnormal).  
4. A synthetic ECG signal is generated using Gaussian functions and smoothed using a moving average filter.  
5. The ECG-like signal is sent to the **Serial Plotter** for real-time visualization.  

---

## **🧑‍💻 Code Explanation**  
The code is divided into the following sections:  
1. **Libraries & Setup**: Includes necessary libraries and initializes the LCD and Pulse Sensor.  
2. **Signal Filtering**: Applies a low-pass filter to smooth the raw sensor data.  
3. **BPM Calculation**: Detects heartbeats and calculates the average BPM over 10 readings.  
4. **ECG Signal Simulation**: Generates a synthetic ECG signal using Gaussian functions.  
5. **Serial Communication**: Sends data to the Serial Plotter for visualization.  
6. **LCD Display**: Updates the LCD screen with the heart rate, error percentage, and status.  

---

## **📊 Results & Demo**  

### **Video Demo**  

https://github.com/user-attachments/assets/888f92ed-696d-4c29-9af9-6b0cfff5da94

---

## **👥 Team**  
This project was developed by:  
- **Anas Mohamed** – Project Lead & Software Development
- **Mohamed Ward** – Testing & Debugging
- **Hassan Badawy & Ziad Osama** – Hardware Integration  
- **Mostafa Hany** – Signal Processing & Algorithm Design   

---

## **🔗 Links**  
- LinkedIn : linkedin.com/in/anas-mohamed-716959313/
