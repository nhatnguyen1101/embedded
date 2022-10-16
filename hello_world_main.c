<<<<<<< HEAD
#include "hello_world.h"
=======
>>>>>>> db9badf6751372784c2c585ebbd19af563c28617
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BTN_NUM GPIO_NUM_25
#define STUDENT_ID 1914371

int state = 0;
int counter = 0;

void checkButton(void *pvParameter)
{
    while (1)
    {
        state = gpio_get_level(BTN_NUM);
        if (state == 0) // deboucing
            counter++;
        else
            counter = 0;

        if (counter == 1)
            printf("ESP32\n");

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void printStudentID(void *pvParameter)
{
    while (1)
    {
        printf("%d\n", STUDENT_ID);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    gpio_pad_select_gpio(BTN_NUM);
    gpio_set_direction(BTN_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_NUM, GPIO_PULLUP_ONLY);
    xTaskCreate(&checkButton, "button", 7000, NULL, 0, NULL);
    xTaskCreate(&printStudentID, "studentID", 7000, NULL, 1, NULL);
}