#include "process.hpp"

void vSensorThread(){
    uint8_t bmp_count = 0;
    uint8_t hum_count = 0;
    uint8_t serial_count = 0;
    LogRecord currentRecord;
    while (1){
        currentRecord.timestamp_ms = millis();
        currentRecord.imu = readMPU();
        bmp_count++;
        hum_count++;
        serial_count++;

        if (bmp_count >= 50){
            currentRecord.bmp = measBMP();
            bmp_count = 0;
        }
        if (hum_count >= 50){
            currentRecord.hum = getHumidity();
            hum_count = 0;
        }
        
        logBufferMutex.lock();
        if (logBuffer.full()){
            logBuffer.pop_front();
        }
        logBuffer.push_back(currentRecord);
        logBufferMutex.unlock();
        
        if (serial_count >= 100){
            serialBufferMutex.lock();
            if(serialBuffer.full()){
                serialBuffer.pop_front();
            }
            serialBuffer.push_back(currentRecord);
            serialBufferMutex.unlock();
            serial_count = 0;
        }

        //Serial.println("Completed this sensor thread cycle, its now sleeping.");
        threads.delay(TARGET_SENSOR_PERIOD/1000); //20ms wait time
    }
}

void vLogThread(){
    std::vector<LogRecord> recordsBuffer;
    recordsBuffer.reserve(50); //TO ensure 50 record space is allocated rather than starting small aand adding space

    while (1){
        logBufferMutex.lock();
        while (!logBuffer.empty() && recordsBuffer.size() < 50){
            recordsBuffer.push_back(logBuffer.front());
            logBuffer.pop_front();
        }
        logBufferMutex.unlock();

        if (!recordsBuffer.empty()){
            if(sdManager.writeRecord(recordsBuffer)){
                //Serial.println("Wrote record to SD card");
            }
            sdManager.flush();
            recordsBuffer.clear();
        }
        //Serial.println("Completed this log thread cycle, its now sleeping.");
        threads.delay(TARGET_LOG_PERIOD/1000); //200ms wait time

        }

    }

void vSerialOutThread() {
  Serial.println("vSerialOutThread: STARTED");

  LogRecord record;
  bool hasData = false;
  unsigned long lastHeartbeat = 0;

  while (1) {

    if (millis() - lastHeartbeat > 5000) {
      size_t s = 0;
      serialBufferMutex.lock();
      s = serialBuffer.size();
      serialBufferMutex.unlock();

      Serial.print("vSerialOutThread ALIVE. Buffer size: ");
      Serial.println(s);
      lastHeartbeat = millis();
    }

    if (!hasData) {
      serialBufferMutex.lock();
      if (!serialBuffer.empty()) {
        record = serialBuffer.front();     
        serialBuffer.pop_front();
        hasData = true;
      }
      serialBufferMutex.unlock();
    }


    if (hasData) {

        PackedRecord pkt = packRecord(record);
        sendRecord(pkt);
        
        hasData = false;
    } 
      threads.delay(1000);
  }
}

void vlistenCommandsFromESP(){
    //this thread will listen to commands in Serial2 sent by ESP in format "$COMMAND\0\n". High priority.
}