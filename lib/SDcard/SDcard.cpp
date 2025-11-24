
#include"SDcard.hpp"

void SDManager::createNewFileName(){
    int n = 0;
    do {
        snprintf(fileName, sizeof(fileName), "LOG_%d.csv", n);
        n++;
    }while(sd.exists(fileName));
}

bool SDManager::sd_begin(){
    // Give SD card time to power up (critical for ACMD41 errors)
    delay(1000);
    
    Serial.println("SDManager::sd_begin - trying SDIO modes...");
    
    // Try FIFO SDIO with retries
    for (int retry = 0; retry < 3; retry++) {
        if (retry > 0) {
            Serial.print("FIFO retry ");
            Serial.println(retry);
            delay(300);
        }
        if (sd.begin(SdioConfig(FIFO_SDIO))) {
            Serial.println("SD OK: FIFO_SDIO");
            goto sd_success;
        }
    }
    
    // Try DMA SDIO
    Serial.println("FIFO failed, trying DMA_SDIO...");
    delay(200);
    if (sd.begin(SdioConfig(DMA_SDIO))) {
        Serial.println("SD OK: DMA_SDIO");
        goto sd_success;
    }
    
    // Last resort: SPI mode (slower but more compatible)
    Serial.println("SDIO failed, trying SPI...");
    Serial.print("Error was: 0x");
    Serial.println(sd.sdErrorCode(), HEX);
    delay(200);
    if (sd.begin(SD_CONFIG)) {
        Serial.println("SD OK: SPI mode");
        goto sd_success;
    }
    
    Serial.println("All SD modes failed!");
    return false;
    
sd_success:
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
    if (!logFile.isOpen()) {
        Serial.println("sd_writeRecord: logFile not open");
        return false;
    }
    char lineBuffer[256];
    size_t len = record.toCSV(lineBuffer, sizeof(lineBuffer));
    if (len == 0) {
        Serial.println("sd_writeRecord: zero length CSV");
        return false;
    }
    int written = logFile.write(lineBuffer, len);
    if (written != (int)len) {
        Serial.print("sd_writeRecord: wrote ");
        Serial.print(written);
        Serial.print(" expected ");
        Serial.println(len);
        return false;
    }
    return true;
}

void SDManager::flush() {
    if (logFile.isOpen()) {
        logFile.sync(); // Forces data from RAM buffer to physical SD card
    }   
}

