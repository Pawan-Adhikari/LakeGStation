#include <Arduino.h>
#include <Wire.h>
#include "I2CSensors.hpp"
#include "process.hpp"
#include "Globals.hpp"

Adafruit_MPU6050 mpu;
Adafruit_MMC5883 mmc;
Adafruit_BMP280 bmp(&Wire1);

void setup() {
  // Initialize USB Serial for output
  Serial.begin(9600);
  while (!Serial && millis() < 4000); // Wait for Serial Monitor
  
  Serial.println("Starting GStation...");

  // Initialize Wire1 (Pins 17 SDA, 16 SCL)
  Wire1.begin();
  
  // Initialize Sensors
  if (!beginBMP()) {
    Serial.println("Failed to initialize BMP280");
  }
  if (!beginMPU()) {
    Serial.println("Failed to initialize MPU6050");
  }
  // if (!beginMMC()) ...

  // Create RTOS Tasks
  createTasks();

  Serial.println("Starting Scheduler...");
  vTaskStartScheduler();
}

void loop() {
  // Should not be reached
}
void loops(){
while (1)
{
  /* code */
}



}