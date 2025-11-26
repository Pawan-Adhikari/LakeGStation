#pragma once
#include <Arduino.h>
#include "Globals.hpp"
#include "SDcard.hpp"
#include <TeensyThreads.h>
#include <vector>
#define RX2_PIN 15
#define TX2_PIN 14


#define TARGET_SENSOR_PERIOD 20000
#define TARGET_LOG_PERIOD 200000

void vSensorThread();
void vLogThread();
void vSerialOutThread();