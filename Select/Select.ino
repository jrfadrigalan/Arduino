/*
MySQL Connector/Arduino Example : connect by wifi
*/
#include <WiFi.h> // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(18,220,146,199); // IP of the MySQL *server* here
char user[] = "root"; // MySQL user login username
char password[] = "2464"; // MySQL user login password
// WiFi card example

char query[] = "SELECT Celsius FROM HTU21D WHERE ID = '1'";

char ssid[] = "FiOS-JKY3N"; // your SSID
char pass[] = "sarah74julian1023aaron68"; // your SSID Password
WiFiClient client; // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);
void setup() {
Serial.begin(115200);
while (!Serial); // wait for serial port to connect. Needed for Leonardo only
// Begin WiFi section
int status = WiFi.begin(ssid, pass);
if ( status != WL_CONNECTED) {
Serial.println("Couldn't get a wifi connection");
while(true);
}
// print out info about the connection:
else {
Serial.println("Connected to network");
IPAddress ip = WiFi.localIP();
Serial.print("My IP address is: ");
Serial.println(ip);
}
// End WiFi section
Serial.println("Connecting...");
if (conn.connect(server_addr, 3306, user, password)) {
delay(1000);
}
else
Serial.println("Connection failed.");
conn.close();
}
void loop() {
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
Serial.print(" NYC pop = ");
Serial.println(head_count);
}
