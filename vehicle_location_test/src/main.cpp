#include <Arduino.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "MPU.cpp"
// #define Pin_8 8

#define MPU_SDA 9
#define MPU_SCL 10



int Power_pin = 8;

MPU mpu6050;

void setup() {
	Serial.begin(115200);

	Wire.begin(MPU_SDA, MPU_SCL, 400000U);
	Wire.setClock(400000);
	
	pinMode(Power_pin, OUTPUT);

	

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
		delayMicroseconds(500);
		digitalWrite(Power_pin, HIGH);
		delayMicroseconds(1500);

	}

	for (int i = 0; i < 40; i++) {
		digitalWrite(Power_pin, LOW);
		delayMicroseconds(500);
		digitalWrite(Power_pin, HIGH);
		delayMicroseconds(500);
	}

	// delay(2000);
}