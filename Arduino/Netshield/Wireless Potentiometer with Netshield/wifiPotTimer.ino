/*
   Arduino potentiometer with 3 second timer and notifying light

   This code will run a server that clients can connect to.
   LED lightens up when 3 second timer is on and it is possible to use potentiometer.

   Potentiometer's middle pin is connected to analog pin. Analog input is 10 bits range 0-1023
   analog output has acceptable range of 8 bits (0-255). Mapping function  will clamp the data.
   Potentiometer will send data to client only if value differs from previous

   Sparkfun WiFi shield ESP8266 is used here with added library
*/

#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

const int LEDPin = 11; //notifying light
const int potPin = A0; // potentiometer middle pin
const char mySSID[] = "YOUR_NETWORK_SSID"; //network ssid
const char myPSK[] = "YOUR_NETWORK_PWD"; //network password

int lastValue = 0; //to remember last value from potentiometer
int potValue; //potentiometer value

String cStr; //store reveived message

ESP8266Server server = ESP8266Server(80); //server responds to clients on port 80

void setup()
{
  //configure pins to function as input or output pins
  pinMode(LEDPin, OUTPUT);
  pinMode(potPin, INPUT);

  Serial.begin(9600);
  delay(2000);

  // initializeESP8266() verifies communication with the WiFi
  // shield, and sets it up.
  initializeESP8266();
  
  connectESP8266(); //connects to the defined WiFi network.

  // displayConnectInfo prints the Shield's local IP
  // and the network it's connected to.
  displayConnectInfo();
  
  delay(1500);
  
  serverSetup();
}

void loop()
{
  // available() is an ESP8266Server function which will
  // return an ESP8266Client object for printing and reading.
  // available() has one parameter -- a timeout value. This
  // is the number of milliseconds the function waits,
  // checking for a connection.
  ESP8266Client client = server.available();
  if (client)
  {
    client.flush();
    Serial.println(F("Client Connected!"));
    while (client.connected())
    {
      if (client.available() > 0)
      {
        char c = client.read();
        cStr += c;
        
        //if received message includes string lON it will power LED:
        if (cStr.indexOf("lON") > 0) {
          digitalWrite(LEDPin, HIGH);
          Serial.println("Lighton"); //print state to serial
          
          //add "3 second window" with a self build timer to adjust potentiometer
          //delay between potentiometer value reading is 10ms and loop is run 300 timers
          for (int i = 0; i < 300 ; i++) {
            readPotentiometer();
            
            //send value to client only if different than previous
            if(potValue != lastValue){
              client.println(potValue);
              lastValue = potValue;  
              i = 0; //reset timer when value has been changed 
            }
            delay(10);     
          }
          //power off notifying LED
          digitalWrite(LEDPin, LOW);
          Serial.println("Lightoff");
          
          cStr = ""; //empty received stored string
          delay(1);
        }
        // close the connection when clients sents message that includes string "disconnected":
        if (cStr.indexOf("disconnected") > 0) {       
          delay(1); 
          Serial.println("Disconnecting connection with client" + client);         
          client.stop();     
        }        
      }
    }
    cStr = ""; 
    Serial.println("Client disconnected"); 
  }
}

void readPotentiometer()
{
  potValue = analogRead(potPin); // read potentiometer input
  potValue = map(potValue, 0, 1023, 0, 255); // clamp analog values from 0-1023, map to 0-255
}

void initializeESP8266()
{
  // esp8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  // true
  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266()
{
  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use esp8266.getMode() to check which mode it's in:
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  // esp8266.status() indicates the ESP8266's WiFi connect
  // status.
  // A return value of 1 indicates the device is already
  // connected. 0 indicates disconnected. (Negative values
  // equate to communication errors.)
  retVal = esp8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    // esp8266.connect([ssid], [psk]) connects the ESP8266
    // to a network.
    // On success the connect function returns a value >0
    // On fail, the function will either return:
    //  -1: TIMEOUT - The library has a set 30s timeout
    //  -3: FAIL - Couldn't connect to network.
    retVal = esp8266.connect(mySSID, myPSK);
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // esp8266.localIP returns an IPAddress variable with the
  // ESP8266's current local IP address.
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void serverSetup()
{
  // begin initializes a ESP8266Server object. It will
  // start a server on the port specified in the object's
  // constructor (in global area)
  server.begin();
  Serial.print("Server started!");
  Serial.println();
}


void errorLoop(int error)
{
  // errorLoop prints an error code, then loops forever.
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

void serialTrigger(String message)
{
  // serialTrigger prints a message, then waits for something
  // to come in from the serial port.
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}
