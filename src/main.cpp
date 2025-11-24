
#include <Arduino.h>
#include <Wire.h>

#include "I2CSensors.hpp"
#include "SDcard.hpp"
#include "HumidityS.hpp"
#include "LogRecord.hpp"
SDManager sdManager;

// SD Manager is defined in 'process.cpp' as a single shared instance
void setup() {
  // Initialize USB Serial for output
  Serial.begin(115200);
  while (!Serial && millis() < 4000); // Wait for Serial Monitor
  Serial.println("Starting sensor + SD test...");

  // Initialize Wire1 (Pins 17 SDA, 16 SCL)
  Wire1.begin();
  delay(1000);

  

  // Initialize Sensors
  if (!beginBMP()) {
    Serial.println("Failed to initialize BMP280");
  } else {
    Serial.println("BMP280 initialized");
  }

  delay(1000);

  if (!beginMPU()) {
    Serial.println("Failed to initialize MPU6050");
  } else {
    Serial.println("MPU6050 initialized");
  }

  // Initialize SD Card
  if (!sdManager.sd_begin()) {
    Serial.println("SD Begin Failed!");
    //exit(1);
  } else {
    Serial.println("SD initialized");
  }
}

void loop() {
  // This loop polls sensors and writes a LogRecord to SD for testing
  LogRecord record;
  record.timestamp_ms = millis();

  // Read sensors using wrapper functions
  record.bmp = measBMP();
  record.imu = readMPU();
  record.hum = getHumidity(27, 28, true);

  // Print values for quick verification
  Serial.print("t=");
  Serial.print(record.timestamp_ms);
  Serial.print(" | BMP: ");
  Serial.print(record.bmp.temperature);
  Serial.print(" C, ");
  Serial.print(record.bmp.pressure);
  Serial.print(" Pa, alt=");
  Serial.print(record.bmp.altitude);
  Serial.print(" m | IMU: ");
  Serial.print(record.imu.accelX);
  Serial.print(", ");
  Serial.print(record.imu.accelY);
  Serial.print(", ");
  Serial.print(record.imu.accelZ);
  Serial.print(" | GYRO: ");
  Serial.print(record.imu.gyroX);
  Serial.print(", ");
  Serial.print(record.imu.gyroY);
  Serial.print(", ");
  Serial.print(record.imu.gyroZ);
  Serial.print(" | HUM: ");
  Serial.print(record.hum.moisture);
  Serial.print(" %, wet=");
  Serial.print(record.hum.isWet ? "yes" : "no");
  Serial.println();

  // Write to SD
  if (!sdManager.sd_writeRecord(record)) {
    Serial.println("SD Write Failed");
  }

  delay(10000); // 10 Hz
}
