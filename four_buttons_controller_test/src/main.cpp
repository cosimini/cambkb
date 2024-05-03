/*
* This really stupic code is used to test ideas
* on how to implement the controller logic.
*
* Four keys are available, a modifier and 3 normal ones.
*
* TODO: implement timer to poll the keys 
*
* TODO: implement the modifier key the home-row mode.
* (i.e. it is a modifier if kept pressed otherwise it acts as a normal key on release)
*/

#include "Arduino.h"
#include "Keyboard.h"

// Some useful keys
// NOTE: Apparently I can not use directly the macros and pass them as argument to the methods
char up = KEY_UP_ARROW;
char down = KEY_DOWN_ARROW;
char tab = KEY_TAB;
char enter = KEY_RETURN;
char esc = KEY_ESC;
char right = KEY_RIGHT_ARROW;
// A dummy varialbe used as bookmark in the keymaps
char mod = (char) 0;
int mod_key = 2;

char keymap[2][4] = {{tab, esc, mod, enter}, {down, up, mod, right}};

int pinv[] = {5, 6, 7, 8};
bool state[] = {false, false, false, false};
bool prev_state[] = {false, false, false, false};

/*
* The callback function scanning and sending keystrokes.
*/
void kb_scan_callback() {
  // Read buttons state
  digitalWrite(9, LOW);
  for(int k = 0; k < 4; k++) {
    state[k] = !digitalRead(pinv[k]);
  }
  digitalWrite(9, HIGH);

  // Check if mod is pressed
  int map_index = 0;
  if(state[mod_key] == true) map_index++;
  // release all keys when the modifier is released
  if(state[mod_key] == false && prev_state[mod_key] == true) Keyboard.releaseAll();

  // Parse state and send key strokes
  for(int k = 0; k < 4; k++) {
    if(k != mod_key && state[k] != prev_state[k]){
      if(state[k]) {
        Keyboard.press(keymap[map_index][k]);
      }
      else {
        Keyboard.release(keymap[map_index][k]);
      }
    }
  }

  // Save button state in a vector (really inefficient)
  for(int k = 0; k < 4; k++) prev_state[k] = state[k];
}


void setup() {
  Keyboard.begin();
  delay(400);
  for(int k = 0; k < 4; k++) {
    pinMode(pinv[k], INPUT_PULLUP);
  }
  pinMode(9, OUTPUT);
}

void loop() {
  // This is ugly at various layers.
  // I will implement the call using timers.
  kb_scan_callback();
  delay(50);
}
