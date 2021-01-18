/*
   Arduino potentiometer & 7-segment LED

   This code will check if user input is a valid number and then pass that information to sevseg-LED
   Potentiometer input is read continuously and printed to serial.

   How to connect potentiometer: Potentiometer's middle pin is connected to analog pin. Side pins 5V and ground
   Analog input is 10 bits range 0-1023, analog output has acceptable range of 8 bits (0-255). 
   Mapping function will clamp the data.

   How to connect 7-segment LED: 7-segment LED is connected to digital pins. Display has a to h sections (8 pins). 
   Pins need to be given in order at setup. Use resistors (220 ohm) between diplay pins and digital pins to avoid LED burnout. 
   When using common anode display, middle pin is connected to 5V.
   7-segment LED is used here with added (SevSeg) library: https://github.com/DeanIsMe/SevSeg
   
*/

#include "SevSeg.h"
SevSeg sevseg;

const int potPin = A0; //potentiometer middlepin

int potValue; // value from potentiometer
char uInput;

void setup() {
  Serial.begin(9600); // set baud rate
  Serial.setTimeout(100); // wait time for serial data

  // set up 7-segment led
  byte numDigits = 1; // number of digits in display
  byte digitPins[] = {}; // leave blank if 1 digit display
  byte segmentPins[] = {6, 5, 11, 10, 9, 7, 8, 12}; // digital pins connected to each segment a-h
  bool resistorsOnSegments = true; // segments used with resistors
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments); // object specification

  pinMode(potPin, INPUT); // modify potentiometer middle pin to be used as input
}

void loop() {
  while (Serial.available()) {
    setInputNumber(checkUserInput());
  }
  readPotentiometer();
}

int checkUserInput()
{
  uInput = Serial.read() - '0';
  if (uInput >= 0 && uInput <= 9) {
    return (uInput);
  }
}

void setInputNumber(int uInput) {
  sevseg.setNumber(uInput); // set number to show
  sevseg.refreshDisplay(); // must be run to display the number
}

void readPotentiometer()
{
  potValue = analogRead(potPin); // read potentiometer input
  potValue = map(potValue, 0, 1023, 0, 255); // clamp analog values from 0-1023, map to 0-255
  Serial.println(potValue);
  delay(100); // add some delay to smooth out reading
}
