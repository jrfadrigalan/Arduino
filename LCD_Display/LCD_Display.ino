/*
 This sketch prints "Hello World!" to the LCD
 and shows the time.

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

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 1, en = 3, d4 = 15, d5 = 13, d6 = 12, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0,0);
  lcd.print("Hello Julian");
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  
}
