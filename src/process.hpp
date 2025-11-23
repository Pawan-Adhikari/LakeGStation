#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "LogRecord.hpp"

// Task priorities
#define SENSOR_TASK_PRIORITY  (tskIDLE_PRIORITY + 2)
#define SD_TASK_PRIORITY      (tskIDLE_PRIORITY + 1)

// Queue size
#define LOG_QUEUE_SIZE 20

// Global Queue Handle
extern QueueHandle_t logQueue;

// Function to create tasks
void createTasks();

// Task functions
void sensorTask(void* pvParameters);
void sdTask(void* pvParameters);

#endif
