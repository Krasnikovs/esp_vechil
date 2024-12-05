class MPU {
    private:
        #define MPU_SDA 9;
        #define MPU_SCL 10;

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
        MPU();
}