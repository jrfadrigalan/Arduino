/* 

  
 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 (use inline 330 ohm resistor if your board is 5V)

 */
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"

const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";
WiFiServer server(8888);

int gpio0_pin=0;

static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

//Create an instance of the object
HTU21D myHumidity;

void setup(){
Serial.begin(115200);

//Sets the pin to an output and turns the LED off for now
pinMode(gpio0_pin, OUTPUT);
digitalWrite(gpio0_pin,LOW);

Serial.println();
Serial.print("Connecting to "); 
Serial.print(ssid);
WiFi.begin(ssid,password);

while(WiFi.status() !=WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

//Starting the web server
server.begin();
Serial.println("Web server running. Waiting for the ESP IP...:");
delay(10000);

//printing the ESP IP address
Serial.println(WiFi.localIP());
  
Serial.print("Waitng for Connection") ;

myHumidity.begin();
}

void loop()
{
//This loops around and constantly updates the web browser
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
            float f =  (myHumidity.readTemperature()*(9/5)+32);//constantly changing and reading
            // Read temperature as Fahrenheit (isFahrenheit = true)
           Serial.print("Time:");
           
           Serial.println(millis());
           Serial.print(" Temperature:");
           Serial.print(t, 2);
           Serial.print("*C||");
           Serial.print(f, 2);
           Serial.println("*F");
           Serial.print(" Humidity:");
           Serial.print(h, 2);
           Serial.println("%");

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
    delay(10);
    client.stop();
    Serial.println("Disconnected.");
     Serial.println();
  delay(1000);
  }
else{
  delay(500);
  Serial.print(".");
 }
}

