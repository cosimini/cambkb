#define DEBUG_MODE 1

#include "Arduino.h"
#include "Keyboard.h"
// project specific libraries in ../include
#include "pinout.h"   // The microcontroller pinout
#include "keymaps.h"   // The map between keys and sent codes

/*
void setup() {
  // Initialize the keyboard object
  Keyboard.begin();
  delay(400);  // The keyboard object takes some time to initialize
  // Initialize the UART
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
  // Enable the USB serial port in debug mode
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
*/

int pinv[] = {5, 6, 7, 8};
bool state[] = {false, false, false, false};
char up = KEY_UP_ARROW;
char down = KEY_DOWN_ARROW;
char left = KEY_TAB;
char right = KEY_RETURN;
char keymap[] = { up, down, left, right };

bool prev_state[] = {false, false, false, false};

void setup() {
  Keyboard.begin();
  delay(400);
  for(int k = 0; k < 4; k++) {
    pinMode(pinv[k], INPUT_PULLUP);
  }
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(9, LOW);
  for(int k = 0; k < 4; k++) {
    state[k] = !digitalRead(pinv[k]);
  }
  for(int k = 0; k < 4; k++) {
    if(state[k] != prev_state[k]){
      if(state[k]) {
        Keyboard.press(keymap[k]);
      }
      else {
        Keyboard.release(keymap[k]);
      }
    }
  }
  for(int k = 0; k < 4; k++){
    prev_state[k] = state[k];
  }
  digitalWrite(9, HIGH);
  delay(50);
}
