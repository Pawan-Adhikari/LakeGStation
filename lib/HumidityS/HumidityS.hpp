#pragma once
#include <Arduino.h>
const float RAW_MAX_DRY = 4095.0; 
const float RAW_MIN_WET = 1500.0;

struct HumidityData{
    bool isWet = false;
    float moisture = -1.0; 
};

HumidityData getHumidity(int aPin = 27, int dPin = 28, bool scale = true);