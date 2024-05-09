#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

// This section of the code can be done with some automation with macros
const int n_rows = 4;
const int n_cols = 7;
int col_pins[n_cols] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 };
int row_pins[n_rows] = { ROW0, ROW1, ROW2, ROW3 };

// The routine scanning the switches matrix
int matrix_scan() {
  int c = 0;
  // Set all to HIGH as the electronics works with inverted logic
  // for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], HIGH);
  // Select the row 'k' by setting to LOW the relative line
  for(int k = 0; k < n_rows; k++) {
    // digitalWrite(row_pins[k], LOW);
    // Scan the column
    Serial.print('<');
    for(int i = 0; i < n_cols; i++) {
      if(digitalRead(col_pins[i])) {
        c++;
        Serial.print('_');
      }
      else Serial.print('*');
    }
    Serial.println('>');
    digitalWrite(row_pins[k], HIGH);
  }
  // Disable the outputs.
  // for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], LOW);
  // Toggle the status pointer.
  return c;
}

void setup() {
  // Set up pins
  // for(int k = 0; k < n_rows; k++) pinMode(row_pins[k], OUTPUT);
  for(int k = 0; k < n_rows; k++) pinMode(col_pins[k], INPUT_PULLUP);
  Serial.begin(9600);
}


void loop() {
  int c = matrix_scan();
  Serial.println(c, DEC);
  delay(250);
}
