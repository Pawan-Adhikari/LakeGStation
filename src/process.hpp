/*
#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <Arduino.h>
//#include <FreeRTOS.h>
//#include <queue.h>
#include "LogRecord.hpp"
// Task priorities
#define HEALTH_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define SENSOR_TASK_PRIORITY  (tskIDLE_PRIORITY + 2)
#define SD_TASK_PRIORITY      (tskIDLE_PRIORITY + 1)
#define ESP_SERIAL_TASK_PRIORITY (tskIDLE_PRIORITY)

// Queue size
#define LOG_QUEUE_SIZE 20

// Global Queue Handle
//extern QueueHandle_t logQueue;

// Function to create tasks
void createTasks();

// Task functions
void sensorTask(void* pvParameters);
void sdTask(void* pvParameters);

#endif
*/