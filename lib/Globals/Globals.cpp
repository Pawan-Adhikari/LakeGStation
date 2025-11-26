#include "Globals.hpp"
#include "SDcard.hpp"

Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp(&Wire1);
Adafruit_MMC5883 mmc;
SDManager sdManager;
Threads::Mutex logBufferMutex;
Threads::Mutex serialBufferMutex;
Threads::Mutex serial2Mutex;
ouroboros::cyclic_deque<LogRecord> logBuffer(LOG_BUFFER_CAPACITY);
ouroboros::cyclic_deque<LogRecord> serialBuffer(SERIAL_BUFFER_CAPACITY);

PackedRecord packRecord(const LogRecord &r) {
    PackedRecord p;
    p.timestamp_ms = r.timestamp_ms;

    p.accelX = r.imu.accelX;
    p.accelY = r.imu.accelY;
    p.accelZ = r.imu.accelZ;

    p.gyroX = r.imu.gyroX;
    p.gyroY = r.imu.gyroY;
    p.gyroZ = r.imu.gyroZ;

    p.temperature = r.bmp.temperature;
    p.pressure = r.bmp.pressure;
    p.altitude = r.bmp.altitude;

    p.isWet = r.hum.isWet ? 1 : 0;
    p.moisture = r.hum.moisture;

    return p;
}

void sendRecord(const PackedRecord &r) {
    Serial2.write(0xAA);                  // Start byte
    Serial2.write((const uint8_t*)&r, sizeof(PackedRecord));  // Raw bytes
}
