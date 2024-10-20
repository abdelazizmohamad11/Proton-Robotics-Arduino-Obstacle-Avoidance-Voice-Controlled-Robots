# Proton Robotics: Obstacle Avoidance and Voice-Controlled Robots

This project explores two versions of an Arduino-based robot designed to navigate its environment and interact with users. The first version, **Proton 1.0**, is an **Obstacle Avoidance Robot** controlled by a smartphone via Bluetooth. The second version, **Proton 2.0**, is an **Advanced Voice-Controlled Robot** using **Arduino Nano BLE 33 Sense** and **Picovoice** for voice recognition.

## **Project Overview**
- Created by: Abdelaziz Mohamad & Tarek Ismail
- Date of Completion: June 2024
- Project Type: Arduino Robotics (Obstacle Avoidance & Voice-Controlled Robots)
  
---

## **Version 1.0: Arduino Obstacle Avoidance Robot (Proton 1.0)**

### **Overview**
Proton 1.0 is a basic robot designed to avoid obstacles autonomously and can also be controlled remotely using a smartphone through the HC-05 Bluetooth module. The project showcases the integration of various sensors and components to create a smart, interactive robot.

### **Components Used**
- Arduino Uno
- HC-05 Bluetooth Module
- Ultrasonic Sensor (for obstacle detection)
- L293D Motor Driver Shield
- Servo Motor (for ultrasonic sensor movement)
- OLED Display (for visual feedback)
- 4-wheel car chassis
- Battery holder with switch (4xAA batteries)

### **How It Works**
1. **Obstacle Avoidance**: The ultrasonic sensor scans the surroundings using a servo motor and detects obstacles. Based on the distance data, the robot decides whether to move forward, turn, or stop.
2. **Smartphone Control**: Using an app created in **MIT App Inventor**, the robot can be controlled remotely via Bluetooth. Users can send commands such as "move forward," "turn left," "turn right," or "stop."
3. **Visual Feedback**: The robot's OLED screen displays animations (happy, sad, angry) based on the robot's current state or user commands.

### **Features**
- **Obstacle detection and avoidance** using ultrasonic sensors.
- **Smartphone control** via Bluetooth (HC-05).
- **Visual feedback** with OLED animations (e.g., happy, sad, angry).
- **Movement functions**: Forward, backward, left, right, and stop.
  
### **Reports**
A comprehensive **report** for Proton 1.0 is available in the `reports` folder, detailing the assembly process, components used, and the MIT App for Bluetooth control.

---

## **Version 2.0: Advanced Voice-Controlled Robot (Proton 2.0)**

### **Overview**
Proton 2.0 is a more advanced version of the original robot, designed to respond to voice commands using the **Arduino Nano BLE 33 Sense** and **Picovoice** for natural language processing. This version of the robot offers an interactive experience with voice-based control over its movements and functionalities.

### **Components Used**
- Arduino Nano BLE 33 Sense
- Built-in sensors (Microphone, Accelerometer, Gyroscope, Environmental Sensors)
- Picovoice open-source models: **Porcupine** (Wake Word Detection) and **Rhino** (Speech-to-Intent)

### **How It Works**
1. **Voice Recognition**: The robot uses **Picovoice's Porcupine** engine to detect the wake word ("Proton") and **Rhino** to understand and execute voice commands (e.g., "Move forward", "Show me happy").
2. **Environmental Interactions**: In addition to movement, the robot can provide environmental data (e.g., temperature, humidity) and respond with emotional expressions through animations on the display.
3. **Advanced Intent Recognition**: The system uses context arrays to interpret various commands and act accordingly. For example, commands can include movements, displaying emotions, or providing environmental information.

### **Features**
- **Voice-Controlled Movement**: Commands such as "move forward", "turn left", "stop", etc.
- **Emotion Display**: The robot can show emotional states such as "happy", "sad", or "angry" based on voice commands.
- **Environmental Sensing**: Using built-in sensors, the robot can report temperature, humidity, and pressure upon request.
- **Wake Word Detection**: Activated by the wake word "Proton" via Picovoice's Porcupine engine.

### **Reports**
A detailed **report** for Proton 2.0 can be found in the `Reports` folder, covering the implementation of voice recognition and the full functionality of the robot.

---

## **How to Start the Project**

### **For Version 1.0 (Proton 1.0)**
1. Clone the repository.
2. Open the `Proton 1.0` folder and upload the code to your **Arduino Uno**.
3. Follow the instructions in the report to connect the components (ultrasonic sensor, motors, OLED display, Bluetooth).
4. Use the **MIT App Inventor** application to connect your smartphone to the robot via Bluetooth and control its movements.

### **For Version 2.0 (Proton 2.0)**
1. Clone the repository.
2. Open the `Proton 2.0` folder and upload the code to your **Arduino Nano BLE 33 Sense**.
3. Install **Picovoice** models as described in the report.
4. Use voice commands to control the robot (after triggering the wake word "Proton").

---

## **Screenshots and Videos**

You can find **screenshots** and **videos** demonstrating the robots in action in the `media` folder.

---

## **Future Improvements**
A potential future improvement would be to physically integrate the two versions of Proton. The Arduino Nano BLE 33 Sense could act as the machine learning brain responsible for processing speech recognition through its advanced sensors and voice capabilities. Once the voice commands are recognized, they would be sent to the Arduino Uno, which would control the robot's body, including the wheels and movement functions.

This integration would result in a fully functional robot controlled entirely by voice, combining the strengths of both versions—speech recognition from Proton 2.0 and the obstacle avoidance and movement capabilities from Proton 1.0—to create a more interactive and intelligent robotic system.



---

## **Reports**
We highly recommend reading the **reports** provided for both versions, located in the `Reports` folder. They provide a complete guide for building and understanding the functionality of both the obstacle avoidance and voice-controlled versions of Proton.

---
