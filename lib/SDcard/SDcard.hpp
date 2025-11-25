#pragma once
#include<SdFat.h>
#include<SD.h>
#include<SPI.h>
#include<Arduino.h>
#include"I2CSensors.hpp"
#include"HumidityS.hpp"
#include"LogRecord.hpp"

#define SD_CS_PIN 10

class SDManager{
    SdFs sd;
    FsFile logFile;
    char fileName[32];
    void createNewFileName();

public:
    bool begin();
    bool writeRecord(const std::vector<LogRecord> records);
    void flush();
};

