#include <SoftwareSerial.h>  

int ambVal = 0;  // define the voltage value of photo diode in digital pin 0
int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int lastValue = 0; // to remember last value from ambient LED

// variables to handle value drifting
int lastValueP = 0; 
int lastValueM = 0; 

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup(){
  Serial.begin(9600); //Configure baud rate 9600
  
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600

}
void loop(){
  
  if(bluetooth.available())  // If the bluetooth sent any characters
    {
      // Send any characters the bluetooth prints to the serial monitor
      Serial.print((char)bluetooth.read());  
    }
  useAmbientLED(); // send ambient LED values via bluetooth
}

void useAmbientLED(){
  // Read analog values and map it to 8 bits, 
  // if value differs +-1 from previous then send it via bluetooth
  
  ambVal = analogRead(0); // Read voltage value ranging from 0 -1023
  ambVal = map(ambVal, 0, 1023, 0, 255); // clamp analog values from 0-1023, map to 0-255

  /*
  if(ambVal != lastValue){ // if current value differs from previously stored value
    Serial.println(ambVal); // print voltage value to serial monitor
    lastValue = ambVal; // store latest value
    bluetooth.write(lastValue); // send latest value as bytes via bluetooth
  }
  */
  
  if(ambVal < lastValueM || ambVal > lastValueP){ // if current value differs from previously stored value
    Serial.println(ambVal); // print voltage value to serial monitor
    lastValue = ambVal; // store latest value

    // values for handling value drifting
    lastValueP = ambVal + 1; 
    lastValueM =  ambVal - 1;
     
    bluetooth.write(lastValue); // send bytes via bluetooth
    }
  
  delay(10);  // delay for 10ms
}
