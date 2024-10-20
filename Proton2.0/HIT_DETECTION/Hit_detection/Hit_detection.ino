#include <Arduino_LSM9DS1.h>
//#include <Keyboard.h>

// Define the threshold for detecting a hit
const float HIT_THRESHOLD = 2.5; // Adjust this threshold as needed

void setup() {
  Serial.begin(9600);
  //Keyboard.begin();
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // Read accelerometer data
  float accelX, accelY, accelZ;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accelX, accelY, accelZ);
    
    // Calculate magnitude of acceleration
    float acceleration = sqrt(sq(accelX) + sq(accelY) + sq(accelZ));
    
    // Check if acceleration exceeds the threshold
    if (acceleration > HIT_THRESHOLD) {
      Serial.println("Ouch");
      //Keyboard.print("Ouch"); // Send "Ouch" to the computer as keyboard input
      delay(1000); // Delay to prevent repeated detection of the same hit
    }
  }
}
