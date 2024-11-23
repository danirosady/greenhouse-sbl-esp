# Smart Greenhouse IoT System

This project aims to develop an IoT-based solution for a smart greenhouse using the ESP32 microcontroller. The system integrates various technologies like MQTT, RS485 communication, and sensors to create an automated and intelligent environment for optimal plant growth. The goal is to enable real-time monitoring and control of greenhouse conditions such as temperature, humidity, light, and soil moisture.

## Project Overview

The Smart Greenhouse IoT System is designed to enhance the productivity and efficiency of greenhouse farming. By using the ESP32, we can connect various sensors and actuators to monitor and control the environment. The system also leverages MQTT for real-time communication, ensuring that all devices stay connected and synchronized.

## Technologies Used

- **ESP32**: A powerful, low-cost microcontroller with Wi-Fi and Bluetooth capabilities, used for communication and control in the greenhouse.
- **MQTT**: A lightweight messaging protocol used for sending data between devices and the central server. It helps in real-time communication for sensor readings and control commands.
- **RS485**: A serial communication standard used for robust, long-distance communication between devices. This protocol is ideal for connecting sensors and actuators across the greenhouse.
- **Sensors**: Various sensors like temperature, humidity, soil moisture, and light sensors are used to gather environmental data.
- **Actuators**: Devices such as fans, lights, and water pumps are controlled based on sensor readings to maintain optimal conditions inside the greenhouse.

## Features

- Real-time monitoring of greenhouse conditions such as temperature, humidity, light, and soil moisture.
- Automatic control of irrigation systems based on soil moisture levels.
- Data logging for historical analysis and decision-making.
- Remote access to the greenhouse via a web or mobile interface.
- Alerts for abnormal conditions (e.g., high temperature or low humidity).

## Getting Started

To set up the Smart Greenhouse IoT system, follow the steps below:

### Prerequisites

- **Hardware**:
  - ESP32 Development Board
  - Sensors: Temperature, Humidity, Soil Moisture, Light, etc.
  - RS485-to-TTL converters for communication with external devices (if applicable).
  - Actuators: Pumps, Fans, Lights, etc.

- **Software**:
  - Arduino IDE or PlatformIO for ESP32 development.
  - MQTT Broker (e.g., Eclipse Mosquitto or cloud-based brokers like HiveMQ).
  - RS485 communication library for ESP32 (e.g., `ModbusMaster` or custom RS485 communication code).
  - Python or Node.js for backend data processing (optional).
  - Web interface (optional) for monitoring and control.

### Installation

1. **Install Arduino IDE (or PlatformIO)**: Download and install the Arduino IDE if you haven't already. Install the ESP32 board support package via the Board Manager in Arduino IDE.

2. **Clone the Repository**:
   Clone the project repository to your local machine:
   ```bash
   git clone https://github.com/your-username/smart-greenhouse.git
   cd smart-greenhouse
3. Install Required Libraries: In the Arduino IDE, go to Sketch > Include Library > Manage Libraries and install the following libraries:

PubSubClient for MQTT
ModbusMaster for RS485 communication (if needed)
DHT for temperature and humidity sensor (or any other sensor library you're using)

4. Configure the MQTT Broker: Set up an MQTT broker (either locally or using a cloud service) and configure the credentials in your code. Example configuration in Arduino IDE:

const char* mqttServer = "broker_address";
const int mqttPort = 1883;
const char* mqttUser = "username";
const char* mqttPassword = "password";

5. Upload the Code: Open the project in Arduino IDE, select the correct ESP32 board, and upload the code to your ESP32 device.

6. Connect the Hardware:

Connect the sensors to the ESP32 (make sure to use appropriate pins).
Set up the RS485 communication and connect the external devices (if using).

7. Start the System: Power up the system, and it should start sending sensor data to the MQTT broker and actuating devices based on the sensor readings.

## MQTT Topics and Data

### Sensor Data: The system publishes sensor data to various MQTT topics. Example:

greenhouse/temperature: Temperature reading from the sensor.
greenhouse/humidity: Humidity reading from the sensor.
greenhouse/soil_moisture: Soil moisture level reading.

### Control Topics: The system subscribes to control topics to receive commands to activate or deactivate devices:

greenhouse/irrigation/control: To turn the irrigation system on/off.
greenhouse/fan/control: To turn the fan on/off.

## Usage
Once the system is up and running, you can monitor and control the greenhouse remotely. The data from the sensors will be sent to the MQTT broker, and you can subscribe to these topics to visualize or act on the data. If a web interface or mobile app is set up, you can use it to control the actuators (e.g., turning on the water pump or adjusting the fan speed) based on real-time data.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
