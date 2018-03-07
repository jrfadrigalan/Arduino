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
#include <ESP8266WiFi.h>//Wifi 
#include <Wire.h>//Wiring
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

//setting network name, password, server address, WiFi client, 
const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";
char server[] = "18.220.146.199";///Website IP/18.220.146.199
IPAddress server_addr(18,220,146,199);
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char user[]= "root";
char password_phpmyadmin[]= "2464";
char query[]= "SELECT Celsius FROM HTU21D_Stream WHERE ID = '1'";

WiFiClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);


//LED setting pin
int gpio0_pin=0;

void setup(){
Serial.begin(115200);

//Sets the pin to an output and turns the LED off for now
pinMode(gpio0_pin, OUTPUT);
digitalWrite(gpio0_pin,LOW);

// set up the LCD's number of columns and rows:

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

Serial.println("Connecting...");
if (conn.connect(server_addr, 3306, user, password_phpmyadmin)) {
delay(1000);
}
else{
Serial.println("Connection failed.");
conn.close();
}
}

void loop(){
    row_values *row = NULL;
  long head_count = 0;

  delay(1000);

  Serial.println("1) Demonstrating using a cursor dynamically allocated.");
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(query);
  // Fetch the columns (required) but we don't use them.
  column_names *columns = cur_mem->get_columns();

  // Read the row (we are only expecting the one)
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  // Deleting the cursor also frees up memory used
  delete cur_mem;

  // Show the result
  Serial.print("  NYC pop = ");
  Serial.println(head_count);

  delay(500);

  Serial.println("2) Demonstrating using a local, global cursor.");
  // Execute the query
  cur.execute(query);
  // Fetch the columns (required) but we don't use them.
  cur.get_columns();
  // Read the row (we are only expecting the one)
  do {
    row = cur.get_next_row();
    if (row != NULL) {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  // Now we close the cursor to free any memory
  cur.close();

  // Show the result but this time do some math on it
  Serial.print("  NYC pop = ");
  Serial.println(head_count);
  Serial.print("  NYC pop increased by 12 = ");
  Serial.println(head_count+12);

}


