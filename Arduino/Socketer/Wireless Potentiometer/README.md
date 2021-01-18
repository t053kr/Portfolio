# Wireless potentiometer with Socketer
Documentation is for Arduino <-> Unreal Engine project.

This project connects physical world into virtual world wirelessly. In this project a player can send a command wirelessly to Arduino. When a player press keyboard number 1 it will give controls to Arduino potentiometer to adjust a light in the game. When a player press x on keyboard it will disconnect the connection.

Data transfer between Arduino and computer is made wirelessly in WiFi network. To do this, [Sparkfun ESP8266 WiFi shield](https://www.sparkfun.com/products/13287) and a plugin for TCP communication is needed. This demo uses [Socketer v0.4 plugin](https://github.com/How2Compute/Socketer) and [Unreal Engine 4.25.4](https://www.unrealengine.com/en-US/)

_Note: Signal between UE and Arduino varies a lot. It is sometimes needed to send multiple commands before one is received by the other end. This happens also with Sparkfun ESP8266 Shield Demo so I came to conclusion that the reason is hardware related_

## Table of contents
* [Dependencies](#dependencies)
* [Installation](#installation)
* [Usage](#usage)

## Dependencies

### Hardware
* Potentiometer
* LED light
* 220R resistor
* Jumper cables x 5
* Breadboard
* Sparkfun ESP8266 WiFi shield

### Software

#### Unreal Engine
* [Socketer v0.4 plugin](https://github.com/How2Compute/Socketer)

#### Arduino Uno
* [Arduino IDE](https://www.arduino.cc/en/software)

#### Sparkfun ESP8266 WiFi shield
* [Library and instructions for Sparkfun ESP8266 WiFi shield](https://learn.sparkfun.com/tutorials/esp8266-wifi-shield-hookup-guide?_ga=2.232777183.154801248.1606463257-1158639612.1605182896#installing-the-esp8266-at-library)

## Installation

### Arduino

#### Hardware
1. Attach WiFi shield in top of Arduino board
2. Connect potentiometer with jumper cables. Side pins are connected to ground(left leg) and 5V(right leg). Middle pin is connected to analog pin A0
3. Connect 220R resistor and LED light so it's longer leg is connected to resistor
4. Add jumper cable from digital pin 11 to other end or resistor
5. Add the last jumper cable from ground to shorter leg of LED light

#### ARDUINO IDE
1. Download library for [Sparkfun ESP8266 WiFi shield](https://learn.sparkfun.com/tutorials/esp8266-wifi-shield-hookup-guide?_ga=2.232777183.154801248.1606463257-1158639612.1605182896#installing-the-esp8266-at-library)
2. Add Sparkfun library to Arduino directory `C:\Program Files (x86)\Arduino\libraries`
3. Open [code](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/Socketer/Wireless%20Potentiometer/wifiPotTimer.ino) in Adruino IDE
4. Replace network settings to match yours: values of mySSID[] & myPSK[]
4. Plugin USB cable and upload the code
5. Start serial monitor
6. If your network settings are correct server should start automatically
7. Notify IP address that is shown, you need to apply it later to blueprint node


#### Unreal Engine
1. Download Socketer Plugin from [Github](https://github.com/How2Compute/Socketer)
2. Start a new project in Unreal Engine
3. Create a folder named "Plugins" in the project directory and add Socketer plugin folder there
4. Open Unreal Engine and enable plugin `Edit/Plugins` and restart Unreal Engine
5. Add [potWifi.umap](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/Socketer/Wireless%20Potentiometer/potWifi.umap) and [potWifi_BuiltData.uasset](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/Socketer/Wireless%20Potentiometer/potWifi_BuiltData.uasset) to `<your project>\Content`
6. Open level blueprint and change IP to match the one your WiFi shield has

## Usage

1. Upload code to Arduino via USB cable. If code is already uploaded connect a power source and server should start
2. Start Unreal Engine game level potWifi
3. Use keyboard number 1 to send signal to Arduino to start using potentiometer
4. Use potentiometer to adjust light in the game (3 sec timer, in use when LED lights up)
5. Use keyboard button x to disconnect connection
6. Values of potentiometer and states of notifying light are also printed in the screen
