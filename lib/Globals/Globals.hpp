#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MMC5883.h>
#include <TeensyThreads.h>
#include "CBuffer.hpp"
#include "LogRecord.hpp"

#define  LOG_BUFFER_CAPACITY 256
#define  SERIAL_BUFFER_CAPACITY 256

class SDManager; 
extern Adafruit_MPU6050 mpu;
extern Adafruit_BMP280 bmp;
extern Adafruit_MMC5883 mmc;
extern SDManager sdManager;
extern Threads::Mutex logBufferMutex;
extern Threads::Mutex serialBufferMutex;
extern Threads::Mutex serial2Mutex;
extern ouroboros::cyclic_deque<LogRecord> logBuffer;
extern ouroboros::cyclic_deque<LogRecord> serialBuffer;

#pragma once
#include <stdint.h>

#pragma pack(push, 1)  // No padding
struct PackedRecord {
    uint32_t timestamp_ms;

    // IMUData
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;

    // BMPdata
    float temperature;
    float pressure;
    float altitude;

    // HumidityData
    uint8_t isDry;      // bool stored as 1 byte
    float moisture;
};
#pragma pack(pop)

PackedRecord packRecord(const LogRecord &r);
void sendRecord(const PackedRecord &r);