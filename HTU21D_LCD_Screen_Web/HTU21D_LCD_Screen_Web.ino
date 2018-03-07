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

const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";
WiFiServer server(8888);




//LCD Display
const int rs = 1, en = 3, d4 = 15, d5 = 13, d6 = 12, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//LED
int gpio0_pin=0;
//Temperature Sensor
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];
HTU21D myHumidity;



void setup(){
Serial.begin(115200);

 pinMode(gpio0_pin, OUTPUT);
 digitalWrite(gpio0_pin,LOW);
 
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);

 lcd.setCursor(0,0); 
 Serial.println();
 Serial.print("Connecting to ");
 lcd.print("Connecting to ");
 
 lcd.setCursor(0,1);
 lcd.print(ssid);
 Serial.println(ssid);
 WiFi.begin(ssid,password);

 
 while(WiFi.status() !=WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  lcd.print(".");
 }
 lcd.clear();
 lcd.setCursor(0,0);     
 Serial.println("");
 
 lcd.setCursor(0,0);
 lcd.print("Wifi Connected");
  Serial.println("WiFi connected");
 
 //Starting the web server
 server.begin();
 Serial.println("Web server running. Waiting for the ESP IP...:");
 

 delay(10000);
 lcd.clear();
  myHumidity.begin();
  
}

void loop()
{
   WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    if (client.connected()) {
      while (client.available()) {
        char c = client.read();
        
        while (c == '\n' && blank_line) {
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h =  myHumidity.readHumidity();//constantly changing and reading
            // Read temperature as Celsius (the default)
            float t =  myHumidity.readTemperature();//constantly changing and reading
            float f = ((t*(1.8))+32);//constantly changing and reading
            // Read temperature as Fahrenheit (isFahrenheit = true)
           Serial.print("Time:");
           
 /* Serial.println(millis());
  Serial.print(" Temperature:");
  Serial.print(t, 2);
  Serial.print("*C||");
  Serial.print(f, 2);
  Serial.println("*F");
  Serial.print(" Humidity:");
  Serial.print(h, 2);
  Serial.println("%");
*/
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print (t);
  lcd. print ("*C ");
  lcd.print(f);
  lcd.print("*F");

  if (t>30){
    digitalWrite(gpio0_pin,HIGH);
  }
  else {
    digitalWrite(gpio0_pin,LOW);
  }
        
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  // your actual web page that displays temperature and humidity
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv=\"refresh\" content=\"2\"></head><body><h1>Temperature and Humidity</h1><h3>Temperature in Celsius: ");
  client.println(t);
  client.println("*C</h3><h3>Temperature in Fahrenheit: ");
  client.println(f);
  client.println("*F</h3><h3>Humidity: ");
  client.println(h);
  client.println("%</h3><h3>");
  client.println("</body></html>");     
    break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
     Serial.println();
  delay(1000);
  }
else{
  delay(500);
  Serial.print(".");
 }
}



