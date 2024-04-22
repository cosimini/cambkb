#define DEBUG_MODE 1

#include "Arduino.h"
#include "Keyboard.h"
// project specific libraries in ../include
#include "pinout.h"

void setup() {
  // Keyboard.begin();
  // delay(1000);
  Serial1.begin(9600);  // Serial1 is the hardware UART on pins 1 and 2 of the pro-micro
  // Set up pins
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(COL0, INPUT_PULLUP);
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  pinMode(COL3, INPUT_PULLUP);
  pinMode(COL4, INPUT_PULLUP);
  pinMode(COL5, INPUT_PULLUP);
  pinMode(COL6, INPUT_PULLUP);
  pinMode(EN_PIN, INPUT_PULLUP);
  // Debug enabled stuff
  #if DEBUG_MODE == 1
  Serial.begin(9600);
  #endif
}

void loop() {
  if(Serial1.available()) {
    Serial.println(Serial1.readString());
  }
  delay(1000);
  Serial1.println("Hi!");
}
