/* 

  
 Hardware Connections (Breakoutboard to Arduino):

 --HTU21D--
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 =GPIO2/D4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 =GPIO3/D3(use inline 330 ohm resistor if your board is 5V)

 //Check pins*

 */
//Included Libraries
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"

//setting network name, password, server address, WiFi client, 
const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";
char server[] = "18.220.146.199";///Website IP/18.220.146.199
WiFiClient client;

//LED setting pin
int gpio0_pin=0;

//Function
HTU21D myHumidity;

void setup(){
Serial.begin(115200);

//Sets the pin to an output and turns the LED off for now
pinMode(gpio0_pin, OUTPUT);
digitalWrite(gpio0_pin,LOW);

//SERIAL MONITOR CHECK//
Serial.println();
Serial.print("Connecting to "); 
Serial.print(ssid);
//SERIAL MONITOR CHECK//

//Begining WiFi "What's your Wifi password?"
WiFi.begin(ssid,password);

//CONNECTION WAIT//  
while(WiFi.status() !=WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
//CONNECTION WAIT//

//SERIAL MONITOR//
Serial.println("");
Serial.println("WiFi connected");
Serial.println("Waiting for the ESP IP...:");
delay(10000);
Serial.println(WiFi.localIP());//IMPORTANT* PRINTS ESP8266 IP
Serial.print("Waitng for Connection") ;
//SERIAL MONITOR//

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
    float f =  (myHumidity.readTemperature()*(9/5)+32);

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

    client.print("GET /Stream/Send_V2.php?ID=");
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


