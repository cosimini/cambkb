/*
* Here keymaps are somehow defined
*/

// TODO: Define a decent set of layers

#ifndef KEYMAP_H
#define KEYMAP_H

#define N_ROWS 4
#define N_COLS 7
#define N_LAYERS 3

// TODO: investigate the issue with the keys macro
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
char cPAGEUP = KEY_PAGE_UP;
char cF1 = KEY_F1;
char cF2 = KEY_F2;
char cF3 = KEY_F3;
char cF4 = KEY_F4;
char cF5 = KEY_F5;
char cF6 = KEY_F6;
char cF7 = KEY_F7;
char cF8 = KEY_F8;
char cF9 = KEY_F9;
char cF10 = KEY_F10;
char cF11 = KEY_F11;
char cF12 = KEY_F12;

#if SIDE == 1	// right side
const int nModifiers = 1;
int modifiers[2][nModifiers] = {{2}, {0}};  // Address of the modifiers
char keyMap[N_LAYERS][N_ROWS][N_COLS] = {	// Keymap for each possible layer
	{	// Layer 0
		{'=',    cBS,    '0', '9', '8', '7', '6'},
		{cCTRL,  '/',    'p', 'o', 'i', 'u', 'y'},
		{0,      cENTER, ';', 'l', 'k', 'j', 'h'},
		{cSHIFT, '\'',   '-', '.', ',', 'm', 'n'}
	},
	{	// Layer 1
		{cF11,   cDEL,   cF10, cF9,    cF8,     cF7,       cF6},
		{cCTRL,  '\\',   '\'', '-',    ']',     '[',       '~'},
		{0,      cENTER, '\\', cRIGHT, cUP,     cDOWN,     cLEFT},
		{cSHIFT, '\'',   '-',  cEND,   cPAGEUP, cPAGEDOWN, cHOME}
	}
};

#else	// left side
const int nModifiers = 0;
int modifiers[2][nModifiers]; 	// Address of the modifiers
char keyMap[N_LAYERS][N_ROWS][N_COLS] = {	// Keymap for each possible layer
	{	// Layer 0
		{'`',  cESC,   '1', '2', '3', '4', '5'},
		{' ',  cTAB,   'q', 'w', 'e', 'r', 't'},
		{cALT, cSHIFT, 'a', 's', 'd', 'f', 'g'},
		{cWIN, cCTRL,  'z', 'x', 'c', 'v', 'b'}
	},
	{	// Layer 1
		{cF12, cESC,   cF1, cF2, cF3, cF4, cF5},
		{' ',    cTAB,   '*',   '7', '8', '9', '+'},
		{cALT, cSHIFT, '-',   '4', '5', '6', '.'},
		{cWIN, cCTRL,  '/',   '1', '2', '3', '0'}
	},
};

#endif

#endif
