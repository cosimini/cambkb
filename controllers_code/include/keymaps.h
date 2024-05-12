/*
* Here keymaps are somehow defined
*/

#ifndef KEYMAP_H
#define KEYMAP_H

// TODO: replace those with compiler definitions
const int n_rows = 4;	  // Number of rows
const int n_cols = 7;	  // Number of columns
const int nModifiers = 2; // number of modifiers

#if SIDE == 1 
char keyMap[nModifiers][4][7];	// Keymap for each possible layer
int modifiers[2][nModifiers]; 	// Address of the modifiers
#else
char keyMap[nModifiers][4][7];	// Keymap for each possible layer
int modifiers[2][nModifiers]; 	// Address of the modifiers
#endif

#endif
