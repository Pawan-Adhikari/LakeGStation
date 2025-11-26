#include <Arduino.h>
#include <Wire.h>
#include "process.hpp"
#include "I2CSensors.hpp"

// Temporary record object for the sensor thread to use
LogRecord sensorThreadRecord; 

void setup() {
  Serial.begin(115200);
  while(!Serial && millis() < 4000); // Wait for serial monitor

  Serial.println("--------------------------------");
  Serial.println("GStation Threads Initializing...");

  // Initialize I2C busses
  Wire1.begin();

  // Initialize Sensors
  if(!beginMPU()){
    Serial.println("Failed to init MPU6050!");
  } else {
    Serial.println("MPU6050 Initialized.");
  }

  if(!beginBMP()){
    Serial.println("Failed to init BMP280!");
  } else {
    Serial.println("BMP280 Initialized.");
  }
  
  // Initialize SD
  if(!sdManager.begin()){
    Serial.println("Failed to init SD Card!");
  } else {
    Serial.println("SD Card Initialized.");
  }

  // Increase buffer size to prevent blocking (4KB is plenty)
  static uint8_t serial2_tx_buffer[4096];
  Serial2.addMemoryForWrite(serial2_tx_buffer, sizeof(serial2_tx_buffer));
  
  Serial2.begin(115200); 
  Serial.println("Writing test...");
  Serial2.println("HELLO_FROM_TEENSY");

  Serial.println("Starting Threads...");

  
  threads.addThread(vSensorThread, 8192);
  threads.addThread(vLogThread, 8192);
  threads.addThread(vSerialOutThread, 8192); 
  
  Serial.println("Threads Running.");
}

void loop() {
  threads.delay(1000);
}
