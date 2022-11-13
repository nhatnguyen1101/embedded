#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include <time.h>

void task1(void *pvParameters) {
    int processing_count = 500;
    //  char * pcTaskName ;
    //  pcTaskName = ( char * ) pvParameters ;
    //int task1=0;
    for(; ;) {
        //printf("[");
        for(int i = 0; i < processing_count; i++) {
            printf("x");
        }
        // printf("%d" ,task1);
        //printf("]");
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void task2(void * pvParameters) {
    int processing_count = 500;
    //char * pcTaskName ;
    //pcTaskName = ( char * ) pvParameters ;
    for(; ;) {
        //printf("{");
        for(int i = 0; i < processing_count; i++) {
            printf("y");
        }
        //printf("}");
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void task3(void* pvParameters) {
    int processing_count = 100;
    //char * pcTaskName ;
    ///pcTaskName = ( char * ) pvParameters ;
    // int task3=0;
    for(; ;) {
        //printf("(");
        for(int i = 0; i < processing_count; i++) {
            printf("z");
        }
        // printf("%d", task3);
        // printf(")");
        vTaskDelay(200 /portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    //for preemtive
    // configUSE_PREEMPTION    1   Preemptive
    // configUSE_TIME_SLICING    1 With TimeSlicing || configUSE_TIME_SLICING    0 WithoutTimeSlicing
    xTaskCreatePinnedToCore(&task1, "task1", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(&task2, "task2", 2048, NULL, 1, NULL, 0);
    /// xTaskCreatePinnedToCore(&task2, "task2", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(&task3, "task3", 2048, NULL, 3, NULL, 0);

    //for cooperative
    // xTaskCreatePinnedToCore(&task1, "task1", 2048, NULL, 1, NULL, 0);
    // xTaskCreatePinnedToCore(&task2, "task2", 2048, NULL, 2, NULL, 0);
    // xTaskCreatePinnedToCore(&task3, "task3", 2048, NULL, 3, NULL, 0);

}

