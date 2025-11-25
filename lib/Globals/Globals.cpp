#include "Globals.hpp"
#include "SDcard.hpp"

Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp(&Wire1);
Adafruit_MMC5883 mmc;
SDManager sdManager;
Threads::Mutex logBufferMutex;
ouroboros::cyclic_deque<LogRecord> logBuffer(LOG_BUFFER_CAPACITY);
