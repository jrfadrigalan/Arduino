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
 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <LiquidCrystal.h>


WiFiServer server(8888);
const int rs = 1, en = 3, d4 = 15, d5 = 13, d6 = 12, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int gpio0_pin=0;
//Create an instance of the object
HTU21D myHumidity;

void setup(){
Serial.begin(115200);

 pinMode(gpio0_pin, OUTPUT);
 digitalWrite(gpio0_pin,LOW);
 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
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

    lcd.setCursor(0,0);
  lcd.print("Hello Julian");
  lcd.print(" ");
  lcd.print(time);
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(t);
  lcd.print("C");
  

  if (t>30){
    digitalWrite(gpio0_pin,HIGH);
  }
  else {
    digitalWrite(gpio0_pin,LOW);
  }
  delay(1000);
  Serial.println();
}
