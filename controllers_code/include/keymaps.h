/*
* Here keymaps are somehow defined
*/

#ifndef KEYMAP_H
#define KEYMAP_H

// TODO: replace those with compiler definitions
const int n_rows = 4;	  // Number of rows
const int n_cols = 7;	  // Number of columns
const int nLayers = 2; // number of modifiers

// This is the only way I managed to use those macros
// for some miserious reason, using them inside the map
// result in incorrect keystrokes
char cBS = KEY_BACKSPACE;
char cDEL = KEY_DELETE;
char cENTER = KEY_RETURN;
char cESC = KEY_ESC;
char cTAB = KEY_TAB;
char cALT = KEY_LEFT_ALT;
char cSHIFT = KEY_LEFT_SHIFT;
char cWIN = KEY_LEFT_GUI;
char cCTRL = KEY_LEFT_CTRL;
char cUP = KEY_UP_ARROW;
char cDOWN = KEY_DOWN_ARROW;
char cLEFT = KEY_LEFT_ARROW;
char cRIGHT = KEY_RIGHT_ARROW;
char cHOME = KEY_HOME;
char cEND = KEY_END;
char cPAGEDOWN = KEY_PAGE_DOWN;
char cPAGEUP = KEY_UP_ARROW;

#if SIDE == 1	// right side
const int nModifiers = 2;
int modifiers[2][nModifiers] = {{1, 2}, {0, 0}}; 	// Address of the modifiers
char keyMap[nLayers + 1][n_rows][n_cols] = {	// Keymap for each possible layer
	{	// Layer 0
		{'=',  cBS,    '0', '9', '8', '7', '6'},
		{'\\', '/',    'p', 'o', 'i', 'u', 'y'},
		{0,    cENTER, ';', 'l', 'k', 'j', 'h'},
		{0,    '\'',   '-', '.', ',', 'm', 'n'}
	},
	{	// Layer 1
		{'=', cDEL,   '0',  '9',    '8',     '7',       '6'},
		{0,   '/',    ']',  '[',    '}',     '{',       '#'},
		{0,   cENTER, '\\', cRIGHT, cUP,     cDOWN,     cLEFT},
		{0,   '\'',   '-',  cEND,   cPAGEUP, cPAGEDOWN, cHOME}
	},
	{	// Layer 2
		{'=', cBS,    '0', '9', '8', '7', '6'},
		{0,   '/',    'p', 'o', 'i', 'u', 'y'},
		{0,   cENTER, ';', 'l', 'k', 'j', 'h'},
		{0,   '\'',   '-', '.', ',', 'm', 'n'}
	}
};

#else	// left side
const int nModifiers = 0;
int modifiers[2][nModifiers]; 	// Address of the modifiers
char keyMap[nLayers + 1][n_rows][n_cols] = {	// Keymap for each possible layer
	{	// Layer 0
		{'`',  cESC,   '1', '2', '3', '4', '5'},
		{' ',  cTAB,   'q', 'w', 'e', 'r', 't'},
		{cALT, cSHIFT, 'a', 's', 'd', 'f', 'g'},
		{cWIN, cCTRL,  'z', 'x', 'c', 'v', 'b'}
	},
	{	// Layer 1
		{'`',  cESC,   '1', '2', '3', '4', '5'},
		{' ',  cTAB,   'e', '7', '8', '9', 'e'},
		{cALT, cSHIFT, '.', '4', '5', '6', '.'},
		{cWIN, cCTRL,  '0', '1', '2', '3', '0'}
	},
	{	// Layer 2
		{'`',  cESC,   '1', '2', '3', '4', '5'},
		{' ',  cTAB,   'q', 'w', 'e', 'r', 't'},
		{cALT, cSHIFT, 'a', 's', 'd', 'f', 'g'},
		{cWIN, cCTRL,  'z', 'x', 'c', 'v', 'b'}
	}
};

#endif

#endif
