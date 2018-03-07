/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Uses the HTU21D library to display the current humidity and temperature
 
 Open serial monitor at 9600 baud to see readings. Errors 998 if not sensor is detected. Error 999 if CRC is bad.
  
 Hardware Connections (Breakoutboard to Arduino):
 
HTU21 Temperature Sensor Wires

 -VCC = 3.3V
 -GND = GND
 -SDA = A4-->Pin 4-->D2 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5-->Pin 5-->D1 (use inline 330 ohm resistor if your board is 5V)

LED 

 -VCC = 3.3 V-->D3
 -GND= GND in series w/ 220 ohm resistor

 */
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"


WiFiServer server(8888);

int gpio0_pin=0;
//Create an instance of the object
HTU21D myHumidity;

void setup(){
Serial.begin(115200);

 pinMode(gpio0_pin, OUTPUT);
 digitalWrite(gpio0_pin,LOW);

  myHumidity.begin();
}

void loop()
{
    // bolean to locate when the http request ends
            float h =  myHumidity.readHumidity();
            // Read temperature as Celsius (the default)
            float t =  myHumidity.readTemperature();
            float f =  (myHumidity.readTemperature()*(9/5)+32);
  Serial.print("Time");
  long time= (millis()/1000);

  Serial.println(time);
  Serial.print(" Temperature:");
  Serial.print(t, 1);
  Serial.println("C");
  Serial.print(" Temperature:");
  Serial.print(f, 1);
  Serial.println("F");
  Serial.print(" Humidity:");
  Serial.print(h, 1);
  Serial.println("%");

  if (t>30){
    digitalWrite(gpio0_pin,HIGH);
  }
  else {
    digitalWrite(gpio0_pin,LOW);
  }
  delay(1000);
  Serial.println();
}
