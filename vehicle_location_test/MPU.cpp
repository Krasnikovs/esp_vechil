#include<Arduino.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

class MPU {
    private:
        MPU6050 mpu;

        
        #define EARTH_GRAVITY_MS2 9.80665  //m/s2
        #define DEG_TO_RAD        0.017453292519943295769236907684886
        #define RAD_TO_DEG        57.295779513082320876798154814105

        bool DMPReady = false;  // Set true if DMP init was successful
        uint8_t MPUIntStatus;   // Holds actual interrupt status byte from MPU
        uint8_t devStatus;      // Return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // Expected DMP packet size (default is 42 bytes)
        uint8_t FIFOBuffer[64]; // FIFO storage buffer

        Quaternion q;           // [w, x, y, z]         Quaternion container
        VectorInt16 aa;         // [x, y, z]            Accel sensor measurements
        VectorInt16 gg;         // [x, y, z]            Gyro sensor measurements
        VectorInt16 aaWorld;    // [x, y, z]            World-frame accel sensor measurements
        VectorInt16 ggWorld;    // [x, y, z]            World-frame gyro sensor measurements
        VectorFloat gravity;    // [x, y, z]            Gravity vector
        float euler[3];         // [psi, theta, phi]    Euler angle container
        float ypr[3];
    public:
        void mpuConnect() {

            mpu_connect:

            mpu.initialize();
            Serial.println("Testing MPU6050 connection...");
            if (mpu.testConnection()) {
                Serial.println("MPU6050 connection failed");
                goto mpu_connect;
            } else {
                Serial.println("Connection successful");
            }

            Serial.println(F("Initializing DMP..."));
            devStatus = mpu.dmpInitialize();

            mpu.setXGyroOffset(0);
            mpu.setYGyroOffset(0);
            mpu.setZGyroOffset(0);
            mpu.setXAccelOffset(0);
            mpu.setYAccelOffset(0);
            mpu.setZAccelOffset(0);

            if (devStatus == 0) {
                mpu.CalibrateAccel(6);  // Calibration Time: generate offsets and calibrate our MPU6050
                mpu.CalibrateGyro(6);
                Serial.println("These are the Active offsets: ");
                mpu.PrintActiveOffsets();
                Serial.println(F("Enabling DMP..."));   //Turning ON DMP
                mpu.setDMPEnabled(true);

                MPUIntStatus = mpu.getIntStatus();

                /* Set the DMP Ready flag so the main loop() function knows it is okay to use it */
                Serial.println(F("DMP ready! Waiting for first interrupt..."));
                DMPReady = true;
                packetSize = mpu.dmpGetFIFOPacketSize(); //Get expected DMP packet size for later comparison
            }   
        }

        void printQuaternion() {
            mpu.dmpGetQuaternion(&q, FIFOBuffer);
            Serial.println("Quat:");
            Serial.println(q.w);
            Serial.println(q.x);
            Serial.println(q.y);
            Serial.println(q.z);
        }

        void getQuaternion(int &qw_, int &qx_, int &qy_, int &qz_) {
            mpu.dmpGetQuaternion(&q, FIFOBuffer);
            qw_ = q.w;
            qx_ = q.x;
            qy_ = q.y;
            qz_ = q.z;
        }

        void printAccel() {
            mpu.dmpGetAccel(&aa, FIFOBuffer);
            mpu.dmpConvertToWorldFrame(&aaWorld, &aa, &q);
            Serial.print("aworld\t");
            Serial.println(aaWorld.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);
            Serial.println(aaWorld.y * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);
            Serial.println(aaWorld.z * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);
        }

        void getAccel(int &ax_, int &ay_, int &az_) {
            // mpu.dmpGetQuaternion(&q, FIFOBuffer);
            mpu.dmpGetAccel(&aa, FIFOBuffer);

            // mpu.dmpGetQuantizedAccel(&qa, FIFOBuffer);

            mpu.dmpConvertToWorldFrame(&aaWorld, &aa, &q);
            
            ax_ = aaWorld.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
            ay_ = aaWorld.y * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
            az_ = aaWorld.z * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
        }


};
