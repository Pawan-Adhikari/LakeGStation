
#include"SDcard.hpp"

void SDManager::createNewFileName(){
    int n = 0;
    do {
        snprintf(fileName, sizeof(fileName), "LOG_%d.csv", n);
    }while(sd.exists(fileName));
}

bool SDManager::sd_begin(){
    if (!sd.begin(SdioConfig(FIFO_SDIO))){
        Serial.println("SD hard initialisation failed!");
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

bool SDManager::sd_writeRecord(const LogRecord& record){
    if (!logFile.isOpen()) return false;
    char lineBuffer[200];
    size_t len = record.toCSV(lineBuffer, sizeof(lineBuffer));
    if (logFile.write(lineBuffer, len) != len) {
        return false; // Write error
    }
    return true;
}

void SDManager::flush() {
    if (logFile.isOpen()) {
        logFile.sync(); // Forces data from RAM buffer to physical SD card
    }   
}

