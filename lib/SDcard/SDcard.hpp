#pragma once
#include<SdFat.h>
#include<SD.h>
#include<SPI.h>
#include<Arduino.h>
#include"I2CSensors.hpp"
#include"HumidityS.hpp"
#include"LogRecord.hpp"

#define SD_CS_PIN BUILTIN_SDCARD
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16))

class SDManager{
    SdFs sd;
    FsFile logFile;
    char fileName[32];
    void createNewFileName();

public:
    bool sd_begin();
    bool sd_writeRecord(const LogRecord& record);
    void flush();
};


