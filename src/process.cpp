#include "process.hpp"

void vSensorThread(){
    unsigned int bmp_count = 0;
    unsigned int hum_count = 0;
    LogRecord currentRecord;
    //uint32_t start_time, finish_time, task_time, next_wake_time = micros();
    while (1){
        //start_time = micros();
        Serial.println("Starting Sensor Thread");
        currentRecord.timestamp_ms = millis();
        currentRecord.imu = readMPU();
        bmp_count++;
        hum_count++;

        if (bmp_count >= 50){
            currentRecord.bmp = measBMP();
            bmp_count = 0;
        }
        if (hum_count >= 500){
            currentRecord.hum = getHumidity();
            hum_count = 0;
        }
        
        logBufferMutex.lock();
        if (logBuffer.full()){
            logBuffer.pop_front();
        }
        logBuffer.push_back(currentRecord);
        currentRecord.display();
        logBufferMutex.unlock();

        Serial.println("Completed this sensor thread cycle, its now sleeping.");
        threads.delay(TARGET_SENSOR_PERIOD/1000); //20ms wait time
    }
}

void vLogThread(){
    std::vector<LogRecord> recordsBuffer;
    recordsBuffer.reserve(50); //TO ensure 50 record space is allocated rather than starting small aand adding space

    while (1){
        Serial.println("Starting Log Thread");
        logBufferMutex.lock();
        while (!logBuffer.empty() && recordsBuffer.size() < 50){
            recordsBuffer.push_back(logBuffer.front());
            logBuffer.pop_front();
        }
        logBufferMutex.unlock();

        if (!recordsBuffer.empty()){
            if(sdManager.writeRecord(recordsBuffer)){
                Serial.printf("Wrote record to SD card");
            }
            sdManager.flush();
            recordsBuffer.clear();
        }
        Serial.println("Completed this log thread cycle, its now sleeping.");
        threads.delay(TARGET_LOG_PERIOD/1000); //200ms wait time

        }

    }





