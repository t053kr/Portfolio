# Ambient LED via Bluetooth
Documentation is for Arduino <-> Unreal Engine project.

This project connects physical world into virtual world wirelessly via bluetooth. In this project ambient LED is used on Arduino to detect surrounding light level. This value is used to control a light in a gameworld. Player can also send values from the game back to Arduino. When player presses keyboard number 1 the value will be printed in Arduino Serial Monitor. 

All data transfer between Arduino and Unreal Engine is made wirelessly using bluetooth connection. To do this, [Sparkfun Bluetooth Mate Silver](https://www.sparkfun.com/products/12576?_ga=2.249061124.245259742.1607244308-1158639612.1605182896) and a plugin for COM port communication is needed. This demo uses [Unreal Engine 4.25.4](https://www.unrealengine.com/en-US/) with marketplace's [Cluster communication Port plugin](https://docs.unrealengine.com/marketplace/en-US/product/cluster-communication-port?lang=en-US). The plugin costs around 26€.

_Note: Bluetooth module has for default 1 min timeout in use, this can be modified following Sparkfun tutorial. Values that light sensor gives depends on the input voltage, resistors and the light source combination. If your bluetooth device is connected properly but the light in Unreal is not adjusting like it should, you need to modify blueprint map node or the useAmbientLED function in the Arduino code to match your current circumstances_

## Table of contents
* [Dependencies](#dependencies)
* [Installation](#installation)
* [Usage](#usage)

## Dependencies

### Hardware
* Ambient LED light
* 10k resistor
* Jumper cables x 7
* Protoshield (Not mandatory)
* Sparkfun Bluetooth Mate Silver

### Software

#### Unreal Engine
* [Cluster communication Port plugin](https://docs.unrealengine.com/marketplace/en-US/product/cluster-communication-port?lang=en-US)

#### Arduino Uno
* [Arduino IDE](https://www.arduino.cc/en/software)

#### Sparkfun Bluetooth Mate Silver
* [Instructions for Sparkfun Bluetooth](https://learn.sparkfun.com/tutorials/using-the-bluesmirf?_ga=2.139351216.245259742.1607244308-1158639612.1605182896)

## Installation

### Arduino

#### Hardware
1. Attach Protoshield on top of the Arduino board
2. Add 10k resistor on the protoshield
3. Add ambient LED light on protoshield so it's longer leg is in same section with resistor's leg with thin stripe
4. Connect Bluetooth Mate Silver with jumper cables: 
    VCC -> 5V
    GND -> Ground
    RX-I -> Digital Pin 3
    TX-O -> Digital Pin 2
5. Connect last jumper cables:
    Resistor -> 5V
    LED + resistor -> Analog pin 0
    LED shorter leg -> Ground

#### ARDUINO IDE
1. Open [code](https://github.com/HAMK-ICT-Project8/arduino-projects/tree/main/Cluster%20Communication%20Port/Ambient%20LED%20via%20BT/ambientBT.ino) in Adruino IDE
2. Plugin USB cable and upload the code

### Bluetooth pairing
1. Open up your computer's bluetooth settings. In Windows 10, right-click Bluetooth icon in toolbar -> "Add Device"
2. In "Settings" window click "Add Bluetooth Device"
3. Select Sparkfun Bluetooth module, default password is 1234
4. Check which port was assigned to it. On the right side of "Settings" window click "More Bluetooth Settings"
5. In Bluetooth Settings window go to "Serial ports" tab
6. You have now two ports assigned to the bluetooth module, note port number of the one with outgoing data

### Unreal Engine
1. Buy [Cluster communication Port plugin](https://docs.unrealengine.com/marketplace/en-US/product/cluster-communication-port?lang=en-US)
2. Start a new project in Unreal Engine
3. Create a folder named "Plugins" in the project directory and add Cluster Communication Port plugin folder there
4. Open Unreal Engine and enable plugin `Edit/Plugins` and restart Unreal Engine
5. Add [AmbientLEDviaBT.uasset](https://github.com/HAMK-ICT-Project8/arduino-projects/tree/main/Cluster%20Communication%20Port/Ambient%20LED%20via%20BT/AmbientLEDviaBT.uasset) to `<your project>\Content`
6. In Unreal Engine open AmbientLEDviaBT blueprint class and change port number to match the one that your Bluetooth module has

## Usage

1. Upload code to Arduino via USB cable. If code is already uploaded connect a power source and bluetooth will be ready to use
2. Pair your computer with Bluetooth module
3. Buy and add Cluster Com Port plugin in to your Unreal Engine project
4. Start your Unreal Engine project with AmbientLEDviaBT included
5. Use keyboard number 1 to send signal to Arduino
6. Intensity of light in the game will change according to ambient LED and value printed in screen
7. If light in the game will not change properly, check that level does not have other light sources mixing up the scene
