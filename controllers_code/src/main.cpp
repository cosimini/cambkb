/*
* The code running in the two controllers.
* The two communicate via UART.
*/

// Define which side of the keyboard acts as USB device.
// Side 1 is right, 0 is left
#define DEBUG_MODE 1
#define SIDE 1
#define MASTER_SIDE 1
#define START_CHAR s    // Char sent by master to trigger scan on slave
#define MOD_CHAR m      // Char sent by both parties before sending the modifier sum value
#define KEYS_CHAR k     // Char sent by slave before sending the Chars to be sent via USB

#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

// TODO: Rname those vectors and move the definition somewhere else
int col_pins[n_cols] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 }; // Map between column number an pin number
int row_pins[n_rows] = { ROW0, ROW1, ROW2, ROW3 }; // Map between row number and pin number

bool status[2][n_rows][n_cols]; // Status vector. It contains the status of each individial switch.
int statusPointer = 0; // The value toggle between 0 and 1 to select the status matrix

// The routine scanning the switches matrix
void matrix_scan() {
  statusPointer = (statusPointer == 1) ? 0 : 1;  // Toggle the status pointer.
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], HIGH); // Set all to HIGH as the electronics works with inverted logic
  for(int k = 0; k < n_rows; k++) {
    digitalWrite(row_pins[k], LOW); // Enable the row
    for(int i = 0; i < n_cols; i++) status[statusPointer][k][i] = digitalRead(col_pins[i]); // Scan the column
    digitalWrite(row_pins[k], HIGH); // Turn off the row
  }
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], LOW); // Disable the outputs.
}

void sendModifiers() {
  // Send the modifier value (0, 1, ..., nModifiers)
  char modValue = 0;
  for(int k = 0; k < nModifiers; k++) {
    if(status[statusPointer][modifiers[0][k]][modifiers[1][k]]) modValue += (int) k+1;
  }
  Serial1.write(MOD_CHAR);
  Serial1.write(modValue);
}

// Master and slave are sitting in a different infinite loops
void slaveLoop() {
  while(true) {
    if(Serial1.available()) {
      char comChar = Serial1.read();
      if(comChar == START_CHAR) {
          matrix_scan();
          sendModifiers();
      }
      if(comChar == MOD_CHAR) {
        // Map keystrokes and send them to master
      }
    }
  }
}


void masterLoop() {
  while(true) {
    Serial1.write(START_CHAR); // I exploit the fact that bidirectional communication is available to sync the scan
    matrix_scan();
    sendModifiers();
    delay(20);
  }
}

void setup() {
  // Set up pins
  pinMode(EN_PIN, INPUT_PULLUP);
  for(int k = 0; k < n_rows; k++) pinMode(row_pins[k], OUTPUT);
  for(int k = 0; k < n_cols; k++) pinMode(col_pins[k], INPUT_PULLUP);
  Serial1.begin(115200); // Initialize the UART
  // Initialize the status matrix
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < n_rows; j++) {
      for(int k = 0; k < n_cols; k++) {
        status[i][j][k] = false;
      }
    }
  }
  // Execute the proper loop
#if DEBUG_MODE == 0
  if(digitalRead(EN_PIN)) {
    if(SIDE == MASTER_SIDE) {
      masterLoop();
      Keyboard.begin();
    }
    else slaveLoop();
  }
#else
  Serial.begin(9600);
#endif
}

// The default loop is the debug loop now.
void loop() {
  matrix_scan();
  for(int r = 0; r < n_rows; r++) {
    for(int c = 0; c < n_cols; c++) {
      if(status[0][r][c] != status[1][r][c]) {
        if(status[statusPointer][r][c] == true) Serial.print("*+* (");
        else Serial.print("_-_ (");
        Serial.print(r, DEC);
        Serial.print(", ");
        Serial.print(c, DEC);
        Serial.print(") -> pins : ");
        Serial.print(row_pins[r], DEC);
        Serial.print(' ');
        Serial.print(col_pins[c], DEC);
        Serial.println();
      }
    }
  }
  delay(50);
}
