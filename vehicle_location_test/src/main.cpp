#include <Arduino.h>

#include <esp_now.h>
#include <WiFi.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


#define MPU_SDA 5
#define MPU_SCL 4

Adafruit_MPU6050 mpu;

// REPLACE WITH YOUR RECEIVER MAC Address
// f0:f5:bd:c9:66:50
// f0:f5:bd:c9:59:b0
uint8_t broadcastAddress[] = {0xf0, 0xf5, 0xbd, 0xc9, 0x59, 0xb0};
// uint8_t broadcastAddress[] = {0xf0, 0xf5, 0xbd, 0xc9, 0x66, 0x50};

// #include "MPU.cpp"
// #define Pin_8 8

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  float aX;
  float aY;
  float aZ;
  bool d;
} struct_message;

struct_message mpuData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

#define pinin1 9
#define pinin2 10

#define pintrig 2
#define pinecho 3
        
#define EARTH_GRAVITY_MS2 9.80665  //m/s2
#define DEG_TO_RAD        0.017453292519943295769236907684886
#define RAD_TO_DEG        57.295779513082320876798154814105

bool DMPReady = false;  // Set true if DMP init was successful
uint8_t MPUIntStatus;   // Holds actual interrupt status byte from MPU
uint8_t devStatus;      // Return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // Expected DMP packet size (default is 42 bytes)
uint8_t FIFOBuffer[64]; // FIFO storage buffer

// Quaternion q;           // [w, x, y, z]         Quaternion container
// VectorInt16 aa;         // [x, y, z]            Accel sensor measurements
// VectorInt16 gg;         // [x, y, z]            Gyro sensor measurements
// VectorInt16 aaWorld;    // [x, y, z]            World-frame accel sensor measurements
// VectorInt16 ggWorld;    // [x, y, z]            World-frame gyro sensor measurements
// VectorFloat gravity;    // [x, y, z]            Gravity vector
// float euler[3];         // [psi, theta, phi]    Euler angle container
// float ypr[3];

int Power_pin = 3;
float xa, ya, za;
float x = 0, y = 0, z = 0; 
float xq, yq, zq, wq;
float qx = 0, qy = 0, qz = 0, qw = 0;
// // MPU mpu6050;
long duration;
int distance;

void FW(int pin);
void BW(int pin);
void left(int pin);
void right(int pin);
void FRight(int pin);
void FLeft(int pin);
void BRight(int pin);
void BLeft(int pin);

void mpuConnect();
void printQuaternion();
void getQuaternion(float &qw_, float &qx_, float &qy_, float &qz_);
void printAccel();
void getAccel(float &ax_, float &ay_, float &az_);

void setup() {
	Serial.begin(115200);

	Wire.begin(MPU_SDA, MPU_SCL, 400000U);
	// Wire.setClock(400000);
	
	// pinMode(Power_pin, OUTPUT);

	pinMode(pinin1, OUTPUT);
	pinMode(pinin2, OUTPUT);

	pinMode(pintrig, OUTPUT);
	pinMode(pinecho, INPUT); 

	

	while (!Serial) {
		delay(10);
	}

	mpuConnect();
	Serial.println("Ready.");
}

void loop() {
	
	printAccel();
	printQuaternion();
	// getQuaternion(wq, xq, yq, zq);
	// getAccel(xa, ya, za);

	// x += xa;
	// y += ya;

	// qw += wq;
	// qx += xq;
	// qy += yq;
	// qz += zq;

	// Serial.println(x);

	
	Serial.println("Run");
	digitalWrite(pinin1, LOW);
	digitalWrite(pinin2, HIGH);

	digitalWrite(pintrig, LOW);
	duration = pulseIn(pinecho, HIGH);
	distance = duration * 0.034 / 2;
	Serial.print("Distance: ");
	Serial.println(distance);

	// if (x >= 120) {
	// 	for (int i = 0; i < 3; i++) {
	// 		FLeft(Power_pin);
	// 	}
	// 	x = 0;
	// 	y = 0;
	// } else {
	// 	for (int i = 0; i < 1; i++) {
	// 		FW(Power_pin);
	// 	}
	// }

	
	
	// for(int i = 0; i < 4; i++) {
	// 	digitalWrite(Power_pin, LOW);
	// 	delayMicroseconds(500);
	// 	digitalWrite(Power_pin, HIGH);
	// 	delayMicroseconds(1500);

	// }

	// for (int i = 0; i < 40; i++) {
	// 	digitalWrite(Power_pin, LOW);
	// 	delayMicroseconds(500);
	// 	digitalWrite(Power_pin, HIGH);
	// 	delayMicroseconds(500);
	// }

	delay(2000);
}

void mpuConnect() {

	mpustart:
	// Try to initialize!
	if (!mpu.begin(MPU6050_I2CADDR_DEFAULT, &Wire)) {
		Serial.println("Failed to find MPU6050 chip");
		goto mpustart;
	// while (1) {
	//   Serial.println("Failed to find MPU6050 chip tt");
	//   delay(100);
	// }
	}
	Serial.println("MPU6050 Found!");

	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	Serial.print("Accelerometer range set to: ");
	switch (mpu.getAccelerometerRange()) {
		case MPU6050_RANGE_2_G:
			Serial.println("+-2G");
			break;
		case MPU6050_RANGE_4_G:
			Serial.println("+-4G");
			break;
		case MPU6050_RANGE_8_G:
			Serial.println("+-8G");
			break;
		case MPU6050_RANGE_16_G:
			Serial.println("+-16G");
			break;
	}
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	Serial.print("Gyro range set to: ");
	switch (mpu.getGyroRange()) {
		case MPU6050_RANGE_250_DEG:
			Serial.println("+- 250 deg/s");
			break;
		case MPU6050_RANGE_500_DEG:
			Serial.println("+- 500 deg/s");
			break;
		case MPU6050_RANGE_1000_DEG:
			Serial.println("+- 1000 deg/s");
			break;
		case MPU6050_RANGE_2000_DEG:
			Serial.println("+- 2000 deg/s");
			break;
	}

	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	Serial.print("Filter bandwidth set to: ");
	switch (mpu.getFilterBandwidth()) {
		case MPU6050_BAND_260_HZ:
			Serial.println("260 Hz");
			break;
		case MPU6050_BAND_184_HZ:
			Serial.println("184 Hz");
			break;
		case MPU6050_BAND_94_HZ:
			Serial.println("94 Hz");
			break;
		case MPU6050_BAND_44_HZ:
			Serial.println("44 Hz");
			break;
		case MPU6050_BAND_21_HZ:
			Serial.println("21 Hz");
			break;
		case MPU6050_BAND_10_HZ:
			Serial.println("10 Hz");
			break;
		case MPU6050_BAND_5_HZ:
			Serial.println("5 Hz");
			break;
	}

	Serial.println("");
	delay(100);

	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);

	// Init ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Once ESPNow is successfully Init, we will register for Send CB to
	// get the status of Transmitted packet
	esp_now_register_send_cb(OnDataSent);

	// Register peer
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;  
	peerInfo.encrypt = false;

	// Add peer        
	if (esp_now_add_peer(&peerInfo) != ESP_OK){
		Serial.println("Failed to add peer");
		return;
	}
}

void printQuaternion() {
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	Serial.print("Rotation X: ");
	Serial.print(g.gyro.x);
	Serial.print(", Y: ");
	Serial.print(g.gyro.y);
	Serial.print(", Z: ");
	Serial.print(g.gyro.z);
	Serial.println(" rad/s");
}

void getQuaternion(float &qw_, float &qx_, float &qy_, float &qz_) {
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	// qw_ = g.gyro.w;
	qx_ = g.gyro.x;
	qy_ = g.gyro.y;
	qz_ = g.gyro.z;
}

void printAccel() {
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	Serial.print("Acceleration X: ");
	Serial.print(a.acceleration.x);
	Serial.print(", Y: ");
	Serial.print(a.acceleration.y);
	Serial.print(", Z: ");
	Serial.print(a.acceleration.z);
	Serial.println(" m/s^2");
}

void getAccel(float &ax_, float &ay_, float &az_) {
	
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

	ax_ = a.acceleration.x;
	ay_ = a.acceleration.y;
	az_ = a.acceleration.z;
}

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