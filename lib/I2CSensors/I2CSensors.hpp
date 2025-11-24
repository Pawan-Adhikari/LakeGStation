#pragma once
#include <Arduino.h>
#include "Globals.hpp"
#include <Wire.h>

struct BMPdata {
    float temperature = -1;
    float pressure = -1;
    float altitude = -1; 
};

struct IMUData {
    float accelX = -1.0;
    float accelY = -1.0;
    float accelZ = -1.0;
    
    float gyroX = 0.0;
    float gyroY = 0.0;
    float gyroZ = 0.0;
};

bool beginBMP(uint8_t address = 0x76);
bool beginMPU(TwoWire *myWire = &Wire1, uint8_t address = 0x68);
BMPdata measBMP();
IMUData readMPU();