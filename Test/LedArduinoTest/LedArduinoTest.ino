#include "SoftwareSerial.h"

SoftwareSerial mySerial(7, 8);

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  pinMode(13, OUTPUT);

  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!mySerial.available()){}

  if (mySerial.read() == 'Y'){
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    mySerial.write('Y');
  }
}
