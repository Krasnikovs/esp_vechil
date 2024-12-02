#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

int Pina = 8;
int Pinb = 9;

void FW(int pin);
void BW(int pin);
void left(int pin);
void right(int pin);
void FRight(int pin);
void FLeft(int pin);
void BRight(int pin);
void BLeft(int pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(Pina, OUTPUT);
  pinMode(Pinb, OUTPUT);
  
}

void loop() {

	digitalWrite(Pina, LOW);
	digitalWrite(Pinb, HIGH);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
void FW(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 16; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void BW(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 40; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void left(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 58; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void right(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 64; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void FRight(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 34; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void FLeft(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 28; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void BRight(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 46; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}

void BLeft(int pin) {
	for (int i = 0; i < 4; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(1500);
	}
	
	for (int i = 0; i < 52; i++) {
		digitalWrite(pin, LOW);
		delayMicroseconds(500);
		digitalWrite(pin, HIGH);
		delayMicroseconds(500);
	}
}