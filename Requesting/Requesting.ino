/* 

  
 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 (use inline 330 ohm resistor if your board is 5V)

 */
 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFiClient.h>

IPAddress server_addr(18,220,146,199);//http://18.220.146.199
//IPAddress server_addr(192,168,1,168);

WiFiServer server(80);
char user[]="root";
char pass[]="2464";

//USER/Network_Password
const char* ssid="FiOS-JKY3N";
const char* password="sarah74julian1023aaron68";

WiFiClient client;
MySQL_Connection conn((Client *)&client);//CREATING INSTANCE OF TH CURSOR PASSING IN THE CONNECTION
MySQL_Cursor cur = MySQL_Cursor(&conn);

//Selecting Data Here
char query[] = "SELECT Celsius FROM HTU21D_Stream WHERE ID= '1'";
void setup(){
  Serial.begin(115200);
  while (!Serial);//Waiting for Serial connection
  
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
  //printing the ESP IP address
  Serial.println(WiFi.localIP());
  //NOW CONNECTED TO WIFI

  Serial.print("Connecting...");
  while (conn.connect(server_addr, 3306, user, pass) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");
}
  

void loop()
{
  row_values *row = NULL;
  long Celsius = 0;
  
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
  Celsius = atol(row->values[0]);//atol() method save value read from the row from th first column
  }
  } while (row != NULL);
  // Deleting the cursor also frees up memory used
  delete cur_mem;
  // Show the result
  Serial.print(" Celsius = ");
  Serial.println(Celsius);
  
}

