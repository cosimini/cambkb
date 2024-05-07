/*
* The code running in the two controllers.
* The two communicate via UART.
*/

// Define which side of the keyboard acts as USB device.
// Side 1 is right, 0 is left
#define MASTER_SIDE 1

#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

// This section of the code can be done with some automation with macros
const int n_rows = 4;
const int n_cols = 7;
int col_pins[n_cols] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 };
int row_pins[n_rows] = { ROW0, ROW1, ROW2, ROW3 };
// Status vector. It contains the status of each individial switch.
// It has dimension 2 as I need to compare the status with the preious scan.
bool status[2][n_rows][n_cols];
// Initialize the matrix to false
for(int i = 0; i < 2; i++) {
  for(int j = 0; j < n_rows; j++) {
    for(int k = 0; k < n_cols; k++) {
      status[i][j][k] = false;
    }
  }
}
// The value toggle between 0 and 1 to select the status matrix
int statusPointer = 0;
// The side is either 0 (left) or 1 (right)
int side = 0;
// true if the controller acts as a master 
// (i.e. actually sends the keystrokes to the PC)
bool isMaster = false;

// The routine scanning the switches matrix
void matrix_scan() {
  // Set all to HIGH as the electronics works with inverted logic
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], HIGH);
  // Select the row 'k' by setting to LOW the relative line
  for(int k = 0; k < n_rows; k++) {
    digitalWrite(row_pins[k], LOW);
    // Scan the column
    for(int i = 0; i < n_cols; i++) {
      status[statusPointer][k][i] = digitalRead(col_pins[i]);
    }
    digitalWrite(row_pins[k], HIGH);
  }
  // Disable the outputs.
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], LOW);
  // Toggle the status pointer.
  if(statusPointer == 1) statusPointer = 0;
  else statusPointer = 1;
}

void setup() {
  // Set up pins
  for(int k = 0; k < n_rows; k++) pinMode(row_pins[k], OUTPUT);
  for(int k = 0; k < n_rows; k++) pinMode(col_pins[k], INPUT_PULLUP);
  pinMode(EN_PIN, INPUT_PULLUP);
  // The side is speicified by the EN jumper
  if(digitalRead(EN_PIN)) side = 1;
  if(side == MASTER_SIDE) {
    Keyboard.begin();
    isMaster= true;
  }
  // Initialize the UART
  Serial1.begin(115200);
}

void loop() {
  if(isMaster) {
    // Tell slave to start scanning
    Serial1.write('1');
    matrix_scan();
    if(Serial1.available()) {
      // read data from UART
    }
    // All this should be inside a timer callback.
    // For the time being I use a simple delay in the loop.
    delay(20);
  }
  else{
    if(Serial1.available()) { }
  }
}
