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
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";

IPAddress server_addr(18,220,146,199);
char user[] = "root";
char password_myphpadmin[]= "2464";

WiFiClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
/*MySQL_Cursor cur = MySQL_Cursor(&conn);*




void setup(){
Serial.begin(115200);

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

delay(10000);


//printing the ESP IP address
Serial.println(WiFi.localIP());
  
Serial.print("Waitng for Connection") ;


}

void loop()
{
//This loops around and constantly updates the web browser

}

