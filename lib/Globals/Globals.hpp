#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MMC5883.h>
#include <TeensyThreads.h>
#include "CBuffer.hpp"
#include "LogRecord.hpp"

#define  LOG_BUFFER_CAPACITY 256

class SDManager; 
extern Adafruit_MPU6050 mpu;
extern Adafruit_BMP280 bmp;
extern Adafruit_MMC5883 mmc;
extern SDManager sdManager;
extern Threads::Mutex logBufferMutex;
extern ouroboros::cyclic_deque<LogRecord> logBuffer;

