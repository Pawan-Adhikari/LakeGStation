#include <Arduino.h>
#include <Wire.h>
#include "process.hpp"
#include "I2CSensors.hpp"

// Temporary record object for the sensor thread to use
LogRecord sensorThreadRecord; 

void setup() {
  Serial.begin(9600);
  while(!Serial && millis() < 4000); // Wait for serial monitor

  Serial.println("--------------------------------");
  Serial.println("GStation Threads Initializing...");

  // Initialize I2C busses
  //Wire.begin();
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

  Serial.println("Starting Threads...");

  // Start Threads
  // Note: We pass sensorThreadRecord by value/copy to the thread
  threads.addThread(vSensorThread);
  threads.addThread(vLogThread);
  
  Serial.println("Threads Running.");
}

void loop() {
  threads.delay(1000); 
}
