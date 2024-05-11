#include <Arduino.h>

const int nport = 8;
bool status[nport];

void setup() {
	Serial.begin(9600);
	pinMode(10, OUTPUT);
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	for(int k = 2; k <= 9; k++) pinMode(k, INPUT_PULLUP);
	for(int k = 0; k < nport; k++) status[k] = false;
}

void loop() {
	digitalWrite(10, HIGH);
	digitalWrite(14, HIGH);
	digitalWrite(15, HIGH);
	digitalWrite(16, HIGH);
	for(int k = 2; k <= 9; k++) {
		if(digitalRead(k) && !status[k-2]) {
			Serial.print(k, DEC);
			Serial.print(" up");
			Serial.println();
		}
		if(!digitalRead(k) && status[k-2]) {
			Serial.print(k, DEC);
			Serial.print(" down");
			Serial.println();
		}
		status[k-2] = digitalRead(k);
	}
	digitalWrite(10, LOW);
	digitalWrite(14, LOW);
	digitalWrite(15, LOW);
	digitalWrite(16, LOW);
	delay(25);
}
