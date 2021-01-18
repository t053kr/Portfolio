# Potentiometer & Seven segment LED
Documentation is for Arduino <-> Unreal Engine project.

This project connects physical world into virtual world. In this project a player can use keyboard numbers to illuminate seven segment LED with according number. With potentiometer player can adjust lightness of a room in the game.

Data transfer between Arduino and computer is made via USB cable. To do this, a plugin for COM communication is needed. This demo uses [UE4Duino 2.2.5 plugin](https://github.com/RVillani/UE4Duino) and [Unreal Engine 4.25.4](https://www.unrealengine.com/en-US/)

## Table of contents
* [Dependencies](#dependencies)
* [Installation](#installation)
* [Usage](#usage)

## Dependencies

### Hardware
* Potentiometer
* Seven segment LED
* 220R resistor x 8
* Jumper cables x 12
* Breadboard

### Software

#### Unreal Engine
* [UE4Duino Plugin](https://github.com/RVillani/UE4Duino)

#### Arduino Uno
* [Arduino IDE](https://www.arduino.cc/en/software)
* [Library for seven segment LED](https://github.com/DeanIsMe/SevSeg)

## Installation

### Arduino

#### Hardware
1. Connect potentiometer with jumper cables. Side pins are connected to ground(left leg) and 5V(right leg). Middle pin is connected to analog pin A0
2. Insert seven segment LED in middle of the breadboard. There are 5 pins on either side, middle pins are ANODE pins when used common anode display. Connect one of the anode pins to 5V. Remaining anode pin is not used at all
3. Connect 220R resistors from every other pin to empty rows in breadbord. 
4. Repeat next for all 8 resistors: Add jumper cable from other end of each resistor to digital pin according to the [pot_and_segled.ino script](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/UE4Duino%20plugin/Potentiometer%20%26%20SevsegLED/pot_and_segled.ino)  section `byte segmentPins[] = {6, 5, 11, 10, 9, 7, 8, 12}`
5. Pins of the component in order are:
    TOP: G, F, Com, A, B
    BOTTOM: E, D, Com, C, DP(H)
6. So do wire connections to digital pins this way:
    **TOP**: 8, 7, 5V, 6, 5
    **BOTTOM**: 9, 10, (empty) , 11, 12

#### ARDUINO IDE
1. Download library for [seven segment LED](https://github.com/DeanIsMe/SevSeg)
2. Add SevSeg library to Arduino directory `C:\Program Files (x86)\Arduino\libraries`
3. Open code in Adruino IDE
4. Plugin USB cable and upload the code


### Unreal Engine
1. Download UE4Duino Plugin from [Github]((https://github.com/RVillani/UE4Duino))
2. Start a new project in Unreal Engine
3. Create a folder named "Plugins" in the project directory and add UE4Duino plugin folder there
4. Open Unreal Engine and enable plugin `Edit/Plugins` and restart Unreal Engine
5. Add [pot.umap](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/UE4Duino%20plugin/Potentiometer%20%26%20SevsegLED/pot.umap) and [pot_BuiltData.uasset](https://github.com/HAMK-ICT-Project8/arduino-scripts/blob/main/UE4Duino%20plugin/Potentiometer%20%26%20SevsegLED/pot_BuiltData.uasset) to `<your project>\Content`

## Usage

1. Start Unreal Engine game level pot
2. Use keyboard numbers to send signal to Arduino seven segment LED
3. Use potentiometer to adjust light in the game
4. Values of keyboard presses and potentiometer are also printed in the screen
