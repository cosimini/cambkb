/*
* The code running in the two controllers.
* The two communicate via UART.
* As all the code I write it ended up being a pile of crap.
*/

#define SIDE 1        // Select the keymap to save in the device memory
#define MOD_CHAR 'm'  // Char sent by both parties before sending the modifier sum value

#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

int col_pins[n_cols] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 };  // Map between columns number and pin
int row_pins[n_rows] = { ROW0, ROW1, ROW2, ROW3 };                    // Map between rows number and pin
bool status[2][n_rows][n_cols]; // Status vector. It contains the status of each individial switch.
int statusPointer = 0;          // The value toggle between 0 and 1 to select the status matrix
int mod_state = 0;              // Sum of the modifiers value
int local_mod;                  // Value of the sum of modifiers at a specific time
bool isMaster;                  // Only one side is sending kewystrokes, the selection is done with a jumper

// Scan the switches matrix and update status[]
void matrix_scan() {
  statusPointer = (statusPointer == 1) ? 0 : 1;  // Toggle the status pointer.
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], HIGH); // Set all to HIGH as the electronics works with inverted logic
  for(int k = 0; k < n_rows; k++) {
    digitalWrite(row_pins[k], LOW);
    for(int i = 0; i < n_cols; i++) status[statusPointer][k][i] = !digitalRead(col_pins[i]); // Scan the column
    digitalWrite(row_pins[k], HIGH);
  }
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], LOW); // Disable the outputs.
}

// Check if modifiers are pressed
int sendModifiers() {
  char modValue = 0;
  for(int k = 0; k < nModifiers; k++) if(status[statusPointer][modifiers[0][k]][modifiers[1][k]]) modValue += (char) k+1;
  Serial1.write(MOD_CHAR);
  Serial1.write(modValue);
  return (int) modValue;
}

// Arduino setup method
void setup() {
  pinMode(EN_PIN, INPUT_PULLUP);
  for(int k = 0; k < n_rows; k++) pinMode(row_pins[k], OUTPUT);
  for(int k = 0; k < n_cols; k++) pinMode(col_pins[k], INPUT_PULLUP);
  Serial1.begin(115200);
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < n_rows; j++) {
      for(int k = 0; k < n_cols; k++) {
        status[i][j][k] = false;
      }
    }
  }
  isMaster = digitalRead(EN_PIN); // Master is selected with a jumper
  if(isMaster) Keyboard.begin();
}

// Main loop
void loop() {
  if(isMaster) {
    delay(20);
    matrix_scan();
    local_mod = sendModifiers();
    while(!Serial1.available());
  }
  else {
    while(!Serial1.available());
    matrix_scan();
    local_mod = sendModifiers();
  }
  if((char) Serial1.read() == MOD_CHAR) local_mod += (int) Serial1.read();
  if(local_mod > nLayers) local_mod = nLayers;
  if(isMaster && local_mod < mod_state) Keyboard.releaseAll();
  mod_state = local_mod;
  for(int r = 0; r < n_rows; r++) {
    for(int c = 0; c < n_cols; c++) {
      if(status[0][r][c] != status[1][r][c]) {
        if(isMaster) {
          if(status[statusPointer][r][c]) Keyboard.press(keyMap[mod_state][r][c]);
          else Keyboard.release(keyMap[mod_state][r][c]);
        }
        else {
          if(status[statusPointer][r][c]) Serial1.write('p');
          else Serial1.write('r');
          Serial1.write(keyMap[mod_state][r][c]);
        }
      }
    }
  }
  while(isMaster && Serial1.available()) {
    if((char) Serial1.read() == 'p') Keyboard.press((char) Serial1.read());
    else Keyboard.release((char) Serial1.read());
  }
}
