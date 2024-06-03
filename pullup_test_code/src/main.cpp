#include <Arduino.h>

const int nport = 8;
bool status[nport];

void setup() {
	Serial.begin(9600);
	// pinMode(10, OUTPUT);
	// pinMode(14, OUTPUT);
	// pinMode(15, OUTPUT);
	// pinMode(16, OUTPUT);
	// digitalWrite(10, LOW);
	// digitalWrite(14, LOW);
	// digitalWrite(15, LOW);
	// digitalWrite(16, LOW);
	// for(int k = 2; k <= 9; k++) pinMode(k, INPUT_PULLUP);
	// for(int k = 0; k < nport; k++) status[k] = false;
	Serial1.begin(115200);
}

void loop() {
	Serial1.write('s');
	Serial1.write('m');
	Serial1.write((char) 0);
	// delay(100);
	while(Serial1.available()) {
		char data = (char) Serial1.read();
		if(data != 0 && data != 'k' &data != 'm') {
			Serial.print(data);
		}
	}
	// digitalWrite(10, HIGH);
	// digitalWrite(14, HIGH);
	// digitalWrite(15, HIGH);
	// digitalWrite(16, HIGH);
	// for(int k = 2; k <= 9; k++) {
	// 	if(digitalRead(k) && !status[k-2]) {
	// 		Serial.print(k, DEC);
	// 		Serial.print(" up");
	// 		Serial.println();
	// 	}
	// 	if(!digitalRead(k) && status[k-2]) {
	// 		Serial.print(k, DEC);
	// 		Serial.print(" down");
	// 		Serial.println();
	// 	}
	// 	status[k-2] = digitalRead(k);
	// }
	// digitalWrite(10, LOW);
	// digitalWrite(14, LOW);
	// digitalWrite(15, LOW);
	// digitalWrite(16, LOW);
	delay(50);
}
