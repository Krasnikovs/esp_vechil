#include <Arduino.h>

#define pinin1 9
#define pinin2 10

// put function declarations here:
int myFunction(int, int);

void setup() {
	pinMode(pinin1, OUTPUT);
	pinMode(pinin2, OUTPUT);

	digitalWrite(pinin1, LOW);
	digitalWrite(pinin2, HIGH);
}

void loop() {
	digitalWrite(pinin1, LOW);
	digitalWrite(pinin2, HIGH);
	// delay(20);
}

// put function definitions here:
int myFunction(int x, int y) {
	return x + y;
}