#include "Arduino.h"
#include "Keyboard.h"

void setup() {
  // Keyboard.begin();
  // delay(1000);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available()) {
    Serial.println(Serial1.readString());
  }
  delay(1000);
  Serial1.println("Hi!");
}
