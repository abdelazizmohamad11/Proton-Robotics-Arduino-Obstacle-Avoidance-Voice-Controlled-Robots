#include <Arduino_LSM9DS1.h>
float integratedGyroZ = 0.0;

void setup() {
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  delay(1000); // Allow time for sensor initialization
}

void loop() {
  float gyroZ;
  float dummyX, dummyY;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(dummyX, dummyY, gyroZ);
    integratedGyroZ += gyroZ * 0.01; // Assuming 100Hz sampling rate (0.01 seconds per sample)
    if (abs(integratedGyroZ) >= 90.0) {
      if (integratedGyroZ > 0) {
        Serial.println("90 degrees rotation counterclockwise!");
      } else {
        Serial.println("90 degrees rotation clockwise!");
      }
      integratedGyroZ = 0.0;
    }
  }
}
