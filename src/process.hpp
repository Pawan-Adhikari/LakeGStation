#pragma once
#include <Arduino.h>
#include "Globals.hpp"
#include "SDcard.hpp"
#include <TeensyThreads.h>
#include <vector>

//#include <mu

#define TARGET_SENSOR_PERIOD 20000
#define TARGET_LOG_PERIOD 200000

void vSensorThread();
void vLogThread();
