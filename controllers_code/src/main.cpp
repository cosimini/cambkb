/*
* The code running in the two controllers.
* The two communicate via UART.
* As all the code I write it ended up being a pile of crap.
*/

// Define which side of the keyboard acts as USB device.
#define SIDE 1          // Compile for a specific side, 0 is left, 1 is right
#define DEBUG_MODE 0    // If enabled, send over serial information about keystrokes
// Those are the chars sent over the UART by the two controllers to communicate
#define START_CHAR 's'  // Char sent by master to trigger scan on slave
#define MOD_CHAR 'm'    // Char sent by both parties before sending the modifier sum value
#define KEYS_CHAR 'k'   // Char sent by slave before sending the Chars to be sent via USB

#include "Arduino.h"
#include "Keyboard.h"
#include "pinout.h"   // Microcontroller pinout
#include "keymaps.h"  // Map between keys and sent codes

// TODO: Rename those vectors and move the definition somewhere else
int col_pins[n_cols] = { COL0, COL1, COL2, COL3, COL4, COL5, COL6 }; // Map between column number an pin number
int row_pins[n_rows] = { ROW0, ROW1, ROW2, ROW3 }; // Map between row number and pin number

bool status[2][n_rows][n_cols]; // Status vector. It contains the status of each individial switch.
int statusPointer = 0; // The value toggle between 0 and 1 to select the status matrix
int mod_state = 0;  // Sum of the modifiers value
int local_mod;      // Value of the sum of modifiers at a specific time
bool isMaster;

// The routine scanning the switches matrix
void matrix_scan() {
  // statusPointer = (statusPointer == 1) ? 0 : 1;  // Toggle the status pointer.
  if(statusPointer == 1) statusPointer = 0;
  else statusPointer = 1;
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], HIGH); // Set all to HIGH as the electronics works with inverted logic
  for(int k = 0; k < n_rows; k++) {
    digitalWrite(row_pins[k], LOW); // Enable the row
    for(int i = 0; i < n_cols; i++) status[statusPointer][k][i] = !digitalRead(col_pins[i]); // Scan the column
    digitalWrite(row_pins[k], HIGH); // Turn off the row
  }
  for(int k = 0; k < n_rows; k++) digitalWrite(row_pins[k], LOW); // Disable the outputs.
}

int sendModifiers() {
  // Send the modifier value (0, 1, ..., nModifiers)
  char modValue = 0;
  for(int k = 0; k < nModifiers; k++) if(status[statusPointer][modifiers[0][k]][modifiers[1][k]]) modValue += (char) k+1;
  Serial1.write(MOD_CHAR);
  Serial1.write(modValue);
  return (int) modValue;
}

// Master and slave are sitting in a different infinite loops
void slaveLoop() {
  while(true) {
    if(Serial1.available()) {
      char comChar = Serial1.read();
      if(comChar == START_CHAR) {
          matrix_scan();
          local_mod = sendModifiers();
      }
      if(comChar == MOD_CHAR) {
        mod_state = local_mod + (int) Serial1.read();
        if(mod_state > nModifiers) mod_state = nModifiers;
        Serial1.write(KEYS_CHAR);
        for(int k = 0; k < n_rows; k++) {
          for(int i = 0; i < n_cols; i++) {
            if(status[0][k][i] != status[1][k][i] && keyMap[0][k][i] != (char) 0) {  // Fill position in the map to be considered modiriers with zeros
              if(status[statusPointer][k][i] == true) Serial1.write('p');
              else Serial1.write('r');
              Serial1.write((char) keyMap[mod_state][k][i]);
            }
          }
        }
      }
    }
  }
}

void masterLoop() {
  while(true) {
    Serial1.write(START_CHAR); // I exploit the fact that bidirectional communication is available to sync the scan
    matrix_scan();
    local_mod = sendModifiers();
    delay(20);  // TODO: Use an interrupt attached to a timer instead of this horrible patch
    if(Serial1.available() && (char) Serial1.read() == MOD_CHAR) { // TODO: Turn this into a "wait until available"
      local_mod += (int) Serial.read();
    }
    if(local_mod > nModifiers) local_mod = nModifiers;
    if(local_mod < mod_state) Keyboard.releaseAll();
    mod_state = local_mod;
    for(int r = 0; r < n_rows; r++) {
      for(int c = 0; c < n_cols; c++) {
        if(status[0][r][c] != status[1][r][c]) {
          if(status[statusPointer][r][c]) Keyboard.press(keyMap[mod_state][r][c]);
          else Keyboard.release(keyMap[mod_state][r][c]);
        }
      }
    }
    if(Serial1.available() && (char) Serial1.read() == KEYS_CHAR) {
      while(Serial1.available()) {
        if((char) Serial1.read() == 'p') Keyboard.press((char) Serial1.read());
        else if((char) Serial.read() == 'r') Keyboard.release((char) Serial1.read());
        else {}
      }
    }
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
    Keyboard.begin();
    masterLoop();
  }
  else slaveLoop();
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
        // Send to usb
        Serial.print("M: ");
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
        // Sent to Serial1
        Serial1.print("S: ");
        if(status[statusPointer][r][c] == true) Serial1.print("*+* (");
        else Serial1.print("_-_ (");
        Serial1.print(r, DEC);
        Serial1.print(", ");
        Serial1.print(c, DEC);
        Serial1.print(") -> pins : ");
        Serial1.print(row_pins[r], DEC);
        Serial1.print(' ');
        Serial1.print(col_pins[c], DEC);
        Serial1.println();
        // Read from Serial1
      }
    }
  }
  while(Serial1.available()) Serial.print((char) Serial1.read());
  delay(50);
}
