#include"LogRecord.hpp"

LogRecord::LogRecord(unsigned long t, IMUData i, BMPdata b, HumidityData h){
    timestamp_ms = t;
    imu = i;
    bmp = b;
    hum = h;
}

int LogRecord::toCSV(char* buffer, const size_t bufferSize) const{
// Format: Timestamp, T, P, A, aX, aY, aZ, gX, gY, gZ, RH, WetStatus
    int len = snprintf(
        buffer, 
        bufferSize, 
        "%lu,%.2f,%.2f,%.2f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.2f,%d\n",
        
        timestamp_ms,
        
        // BMP Data
        bmp.temperature,
        bmp.pressure,
        bmp.altitude,
        
        // MPU Data
        imu.accelX,
        imu.accelY,
        imu.accelZ,
        
        imu.gyroX,
        imu.gyroY,
        imu.gyroZ,
        
        // Humidity Data
        hum.moisture,
        (int)hum.isDry 
    );
    //Serial.println("Currently converting the following reading to csv:");
    //Serial.println(buffer);
return len;
}

void LogRecord::display() const {
    Serial.println("TimeStamp: ");
    Serial.println(timestamp_ms);
    imu.display();
    bmp.display();
    hum.display();

}