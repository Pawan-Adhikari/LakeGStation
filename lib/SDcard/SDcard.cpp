
#include"SDcard.hpp"

void SDManager::createNewFileName(){
    int n = 0;
    do {
        snprintf(fileName, sizeof(fileName), "LOG_%d.csv", n);
        n++;
    }while(sd.exists(fileName));
}

bool SDManager::begin(){
    if (!sd.begin(SdioConfig(FIFO_SDIO))){
        return false;
    }
    createNewFileName();
    if (!logFile.open(fileName, O_CREAT | O_WRITE | O_TRUNC)) {
        Serial.println("Failed to open file!");
        return false;
    }
    logFile.println("Timestamp_ms,Temp_C,Press_Pa,Alt_m,AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,Humidity_%,IsWet");

    Serial.print("Logging to: ");
    Serial.println(fileName);
    return true;
}

bool SDManager::writeRecord(const std::vector<LogRecord> records){
    if (!logFile.isOpen()) return false;
    char writeBuffer[12800];
    int n = 0;
    size_t len = 0;
    int currentOffset =0;
    auto it = records.begin();
    while(it != records.end() && n<50){
        char lineBuffer[256];
        size_t lineLen = records[n].toCSV(lineBuffer, sizeof(lineBuffer));

        if (currentOffset + lineLen > sizeof(writeBuffer)) {
            break; 
        }

        memcpy(writeBuffer + currentOffset, lineBuffer, lineLen);
        
        currentOffset += lineLen;
        len += lineLen;
        n++;
        it++;
    }
    
    bool success = (logFile.write(writeBuffer, len) == len);
    
    return success;
}

void SDManager::flush() {
    if (!logFile.isOpen()) return;
    
    // Disable interrupts during sync to prevent corruption
    logFile.sync(); // Forces data from RAM buffer to physical SD card
}

