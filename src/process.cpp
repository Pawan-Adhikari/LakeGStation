#include "process.hpp"
#include "I2CSensors.hpp"
#include "SDcard.hpp"
#include "HumidityS.hpp"
/*
QueueHandle_t logQueue;
SDManager sdManager;

void createTasks() {
    // Create Queue
    logQueue = xQueueCreate(LOG_QUEUE_SIZE, sizeof(LogRecord));
    if (logQueue == NULL) {
        Serial.println("Failed to create queue");
        while(1);
    }

    // Initialize SD Card here or in main setup? 
    // Better to do it in main setup to catch errors early, 
    // but we need the object. sdManager is global here.
    if (!sdManager.sd_begin()) {
        Serial.println("SD Begin Failed!");
    }

    // Create Tasks
    xTaskCreate(sensorTask, "SensorTask", 2048, NULL, SENSOR_TASK_PRIORITY, NULL);
    xTaskCreate(sdTask, "SDTask", 4096, NULL, SD_TASK_PRIORITY, NULL);
}

void sensorTask(void* pvParameters) {
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // 10Hz

    xLastWakeTime = xTaskGetTickCount();

    for (;;) {
        LogRecord record;
        record.timestamp_ms = millis();

        // Read Sensors
        record.bmp = measBMP();
        record.imu = readMPU();
        record.hum = getHumidity();

        // Send to Queue
        if (xQueueSend(logQueue, &record, 0) != pdPASS) {
            Serial.println("Queue Full!");
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void sdTask(void* pvParameters) {
    LogRecord record;

    for (;;) {
        if (xQueueReceive(logQueue, &record, portMAX_DELAY) == pdPASS) {
            if (!sdManager.sd_writeRecord(record)) {
                Serial.println("SD Write Failed");
            }
            
            // Optional: Flush periodically or after every write
            // sdManager.flush(); 
        }
    }
}
*/