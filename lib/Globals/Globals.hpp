#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MMC5883.h>
class SDManager; // forward declare since Globals shouldn't include SDcard.hpp to avoid include loops

extern Adafruit_MPU6050 mpu;
extern Adafruit_BMP280 bmp;
extern Adafruit_MMC5883 mmc;
extern SDManager sdManager;

