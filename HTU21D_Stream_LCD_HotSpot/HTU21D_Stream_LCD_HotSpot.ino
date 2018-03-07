/*
const int D0= 16;
const int D1=5;
const int D2=4;
const int D3=0;
const int D4=2;
const int D5=14;
const int D6=12;
const int D7=13;
const int D8=15;
const int D9=3;
const int D10=1;

Hardware Connections (Breakoutboard to Arduino):
  
HTU21D Humidity Sensor Example Code
HTU21 Temperature Sensor Wires

 -VCC = 3.3V
 -GND = GND
 -SDA = A4-->Pin 4-->D2 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5-->Pin 5-->D1 (use inline 330 ohm resistor if your board is 5V)

LED 

 -VCC = 3.3 V-->D3
 -GND= GND in series w/ 220 ohm resistor

LCD Display

  The circuit:
 * LCD RS pin to digital pin 12 --> D10 --> 1 pin
 * LCD Enable pin to digital pin 11 --> D9 --> 3 pin
 * LCD D4 pin to digital pin 5 --> D8 --> 15 pin
 * LCD D5 pin to digital pin 4 --> D7 --> 13 pin
 * LCD D6 pin to digital pin 3 --> D6 --> 12 pin
 * LCD D7 pin to digital pin 2 --> D5 --> 14 pin
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)


 */
//Included Libraries
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <LiquidCrystal.h>


//setting network name, password, server address, WiFi client, 
const char* ssid="Test";
const char* password="password";
char server[] = "18.220.146.199";///Website IP/18.220.146.199
WiFiClient client;

//LCD Display
const int rs = 1, en = 3, d4 = 15, d5 = 13, d6 = 12, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LED setting pin
int gpio0_pin=0;

//Function
HTU21D myHumidity;

void setup(){
Serial.begin(115200);

//Sets the pin to an output and turns the LED off for now
pinMode(gpio0_pin, OUTPUT);
digitalWrite(gpio0_pin,LOW);

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);


//SERIAL MONITOR CHECK//
Serial.println();
Serial.print("Connecting to "); 
Serial.print(ssid);
//SERIAL MONITOR CHECK//

//LCD DISPLAY//
lcd.setCursor(0,0);
lcd.print("Connecting to ");
lcd.setCursor(0,1);
lcd.print(ssid);
//LCD DISPLAY//

//Begining WiFi "What's your Wifi password?"
WiFi.begin(ssid,password);

//CONNECTION WAIT//  
while(WiFi.status() !=WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  lcd.print(".");
}
//CONNECTION WAIT//

lcd.clear();
lcd.setCursor(0,0);

//SERIAL MONITOR//LCD DISPLAY//
Serial.println("");
Serial.println("WiFi connected");
lcd.setCursor(0,0);
lcd.print("Wifi Connected");
Serial.println("Waiting for the ESP IP...:");
delay(10000);
Serial.println(WiFi.localIP());//IMPORTANT* PRINTS ESP8266 IP
Serial.print("Waitng for Connection") ;
//SERIAL MONITOR//LCD DISPLAY//

//Function
myHumidity.begin();
}

void loop(){
  
client.connect(server,80);//Connecting to server via port 80

//Only runs if it is connected
if (client.connected()){
  for (int i=0; i<=100;i++){//Run 100 readings before restarting
    delay(300);

    //Setting the variable for humidity, celsius, & fahrenheit
    
    float h =  myHumidity.readHumidity();
    float c =  myHumidity.readTemperature();
    float f =  ((myHumidity.readTemperature()*(1.8))+32);
  
    //LCD DISPLAY//
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature:");
    lcd.setCursor(0,1);
    lcd.print (c);
    lcd. print ("*C ");
    lcd.print(f);
    lcd.print("*F");
    //LCD DISPLAY//



    //SERIAL MONITOR CHECK//
    Serial.println();
    Serial.println(i);
    Serial.println(millis());
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");
    
    Serial.print("Temperature: ");
    Serial.print(c,2);
    Serial.println("*C");
    
    Serial.print("Temperature: ");
    Serial.print(f,2);
    Serial.println("*F");
    //SERIAL MONITOR CHECK//

    client.print("GET /Stream/Send_V3.php?ID=");
    client.print(i);
    client.print("&Timestamp=");
    client.print(millis());
    client.print("&Celsius=");
    client.print(c);
    client.print("&Fahrenheit=");
    client.print(f);
    client.print("&Humidity=");
    client.print(h);
    client.println(" HTTP/1.1"); 
    client.println("Host: 18.220.146.199"); 
    client.println(); // Empty line
    client.println(); // Empty line
    client.flush();
    //Waits until all outgoing characters in buffer have been sent
    // Creates One on One sending

}
}
else {//This is only here to catch connection failures
  Serial.println("Client connection has failed");
  client.stop();
}
}


