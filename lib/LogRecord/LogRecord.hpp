#pragma once
#include "I2CSensors.hpp"
#include "HumidityS.hpp"

struct LogRecord {
    unsigned long timestamp_ms; 
    IMUData imu; 
    BMPdata bmp; 
    HumidityData hum;
public:
    LogRecord(){}
    LogRecord(unsigned long t, IMUData i, BMPdata b, HumidityData h);
    int toCSV(char* buffer, const size_t bufferSize) const;
};



