/*
* Here keymaps are somehow defined
*/

#ifndef KEYMAP_H
#define KEYMAP_H

// TODO: replace those with compiler definitions
const int n_rows = 4;	  // Number of rows
const int n_cols = 7;	  // Number of columns

char cBS = KEY_BACKSPACE;
char cENTER = KEY_RETURN;
char cESC = KEY_ESC;
char cTAB = KEY_TAB;
char cALT = KEY_LEFT_ALT;
char cSHIFT = KEY_LEFT_SHIFT;
char cWIN = KEY_LEFT_GUI;
char cCTRL = KEY_LEFT_CTRL;

#if SIDE == 1 
const int nModifiers = 2; // number of modifiers
int modifiers[2][nModifiers] = {{1, 2}, {0, 0}}; 	// Address of the modifiers
char keyMap[nModifiers + 1][4][7] = {	// Keymap for each possible layer
	{
		{'=', cBS, '0', '9', '8', '7', '6'},
		{0, '/', 'p', 'o', 'i', 'u', 'y'},
		{0, cENTER, ';', 'l', 'k', 'j', 'h'},
		{0, '\'', '-', '.', ',', 'm', 'n'}
	},
	{
		{'=', cBS, '0', '9', '8', '7', '6'},
		{0, '/', 'p', 'o', 'i', 'u', 'y'},
		{0, cENTER, ';', 'l', 'k', 'j', 'h'},
		{0, '\'', '-', '.', ',', 'm', 'n'}
	},
	{
		{'=', cBS, '0', '9', '8', '7', '6'},
		{0, '/', 'p', 'o', 'i', 'u', 'y'},
		{0, cENTER, ';', 'l', 'k', 'j', 'h'},
		{0, '\'', '-', '.', ',', 'm', 'n'}
	}
};

#else
const int nModifiers = 0; // number of modifiers
int modifiers[2][nModifiers]; 	// Address of the modifiers
char keyMap[nModifiers + 1][4][7] = {	// Keymap for each possible layer
	{
		{'=', cBS, '0', '9', '8', '7', '6'},
		{0, '/', 'p', 'o', 'i', 'u', 'y'},
		{0, cENTER, ';', 'l', 'k', 'j', 'h'},
		{0, '\'', '-', '.', ',', 'm', 'n'}
	}
};

#endif

#endif
