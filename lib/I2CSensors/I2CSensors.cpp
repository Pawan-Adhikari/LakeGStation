#include "I2CSensors.hpp"
#include <Wire.h>

bool beginBMP(uint8_t address){
    if (bmp.sensorID() == BMP280_CHIPID) return true;
    if (!bmp.begin(address, BMP280_CHIPID)) {
        return false;
    }
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED,      // Forced mode
                    Adafruit_BMP280::SAMPLING_X1,      // Temp sampling
                    Adafruit_BMP280::SAMPLING_X1,      // Pressure sampling
                    Adafruit_BMP280::FILTER_OFF, 
                    Adafruit_BMP280::STANDBY_MS_500);
    return true;
}

bool beginMPU(TwoWire *myWire, uint8_t address){
    if(!mpu.begin(address, myWire)){
        Serial.println("Failed to initialize MPU6050!");
        return false;
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); 
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);       
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);     
    return true;
}

BMPdata measBMP(){
    BMPdata bmpReadings;
    if (bmp.sensorID() != BMP280_CHIPID) beginBMP();
    if (bmp.takeForcedMeasurement()) {
        bmpReadings.temperature = bmp.readTemperature();
        bmpReadings.pressure = bmp.readPressure();
        bmpReadings.altitude = bmp.readAltitude(1013.25);
    }
    return bmpReadings;
}

IMUData readMPU(){
    IMUData imuReadings;
    sensors_event_t a, g, temp;
    
    if(!mpu.getEvent(&a, &g, &temp)){
        if(!beginMPU(&Wire1)){
            Serial.println("MPU6050 couldn't initialise.");
            return imuReadings;
        }
        else {
            Serial.println("MPU is initialized and I'm now taking data!");
            mpu.getEvent(&a, &g, &temp);
        }
    }
    
    imuReadings.accelX = a.acceleration.x;
    imuReadings.accelY = a.acceleration.y;
    imuReadings.accelZ = a.acceleration.z;
    
    imuReadings.gyroX = g.gyro.x;
    imuReadings.gyroY = g.gyro.y;
    imuReadings.gyroZ = g.gyro.z;
    
    return imuReadings; 
}




