/*
* The code running in the two controllers.
* The two communicate via UART.
* As all the code I write it ended up being a pile of crap.
*/

// TODO: Refactor the mechanism in a more maintenable code
// TODO: Implement the tap-hold logic for modifiers (hold -> modifier, tap (whith no other key) -> char (e.g. space)
// TODO: Implement the tap-hold logic for characters (tap -> a ; hold > threshold -> A)
// TODO: Implement the tap-sequence logic (a,b -> arrow, a,a -> a)

#define SIDE 1        // Select the keymap to save in the device memory
#define MOD_CHAR 'm'  // Char sent by both parties before sending the modifier sum value
#define LOOP_DELAY 5

#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

int col_pins[N_COLS] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 };  // Map between columns number and pin
int row_pins[N_ROWS] = { ROW0, ROW1, ROW2, ROW3 };                    // Map between rows number and pin
bool status[2][N_ROWS][N_COLS]; // Status vector. It contains the status of each individial switch.
int statusPointer = 0;          // The value toggle between 0 and 1 to select the status matrix
bool isMaster;                  // Only one side is sending kewystrokes, the selection is done with a jumper

// Scan the switches matrix and update status[]
void matrix_scan() {
  statusPointer = (statusPointer == 1) ? 0 : 1;  // Toggle the status pointer.
  for(int k = 0; k < N_ROWS; k++) digitalWrite(row_pins[k], HIGH); // Set all to HIGH as the electronics works with inverted logic
  for(int k = 0; k < N_ROWS; k++) {
    digitalWrite(row_pins[k], LOW);
    for(int i = 0; i < N_COLS; i++) status[statusPointer][k][i] = !digitalRead(col_pins[i]); // Scan the column
    digitalWrite(row_pins[k], HIGH);
  }
  for(int k = 0; k < N_ROWS; k++) digitalWrite(row_pins[k], LOW); // Disable the outputs.
}

// Arduino setup method
void setup() {
  pinMode(EN_PIN, INPUT_PULLUP);
  for(int k = 0; k < N_ROWS; k++) pinMode(row_pins[k], OUTPUT);
  for(int k = 0; k < N_COLS; k++) pinMode(col_pins[k], INPUT_PULLUP);
  Serial1.begin(115200);
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < N_ROWS; j++) {
      for(int k = 0; k < N_COLS; k++) {
        status[i][j][k] = false;
      }
    }
  }
  isMaster = digitalRead(EN_PIN); // Master is selected with a jumper
  if(isMaster) Keyboard.begin();
}

// Main loop
void loop() {
  // TODO: The logic needs to be moved entirely in the master side to easily implement the new hold-tap stuff.
}
