#include <ESP8266WiFi.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println();
WiFi.begin("FiOS-JKY3N","sarah74julian1023aaron68");
Serial.print("Connecting");
while(WiFi.status()!=WL_CONNECTED)
  {
delay(500);
Serial.print(".");
  }
Serial.println();

Serial.print("Connected,IPaddress: ");
Serial.println(WiFi.localIP());
}
void loop() {
  // put your main code here, to run repeatedly:

}
