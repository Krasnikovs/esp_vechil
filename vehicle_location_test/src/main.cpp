#include <Arduino.h>

// #include "I2Cdev.h"
// #include "MPU6050_6Axis_MotionApps20.h"

#include "MPU.cpp"
// #define Pin_8 8


int Power_pin = 8;

MPU mpu6050;

void setup() {
	Serial.begin(115200);

	pinMode(Power_pin, OUTPUT);

	Wire.begin();
	Wire.setClock(400000);

	while (!Serial) {
		delay(10);
	}

	mpu6050.mpuConnect();

}

void loop() {
	mpu6050.printQuaternion();
	mpu6050.printAccel();
	
	for(int i = 0; i < 4; i++) {
		digitalWrite(Power_pin, LOW);
		delay(0.5);
		digitalWrite(Power_pin, HIGH);
		delay(1.5);

	}

	for (int i = 0; i < 40; i++) {
		digitalWrite(Power_pin, LOW);
		delay(0.5);
		digitalWrite(Power_pin, HIGH);
		delay(0.5);
	}

}