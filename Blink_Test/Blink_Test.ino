int pin2=2;
int pin0=0;
void setup() {
  pinMode(pin2, OUTPUT); //initialize GPIO2 as the output
  pinMode(pin0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin2,HIGH);// turn the Led on (High=voltage level)
  digitalWrite (pin0,LOW);
  delay(500); //wait a second
  digitalWrite(pin2,LOW); //turn the LED off by making the voltage low
  digitalWrite(pin0,HIGH);
  delay(500); //wait a second
  }
