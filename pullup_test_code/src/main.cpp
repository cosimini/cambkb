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

void debugLoop() {
  Serial.begin(9600);
  while(true) {
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
}

