#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "freertos/timers.h"
#include <time.h>

#define LOOPTIME_1 10
#define LOOPTIME_2 5

#define TIMERID_1 0
#define TIMERID_2 1

#define TIMER_1_PERIOD 2000
#define TIMER_2_PERIOD 3000

#define TIMER_1_MSG "ahihi"
#define TIMER_2_MSG "ihaha"

#define NUM_TIMER 2

void ATimerCallback(TimerHandle_t pxTimer)
{
    // Create array to store the count of each timer
    static int loopCountArr[NUM_TIMER] = {};
    uint32_t timerID = (uint32_t)pvTimerGetTimerID(pxTimer);

    if (timerID == TIMERID_1)
    {
        printf("t = %d\t%s\t(%d)\n", xTaskGetTickCount() * portTICK_PERIOD_MS, TIMER_1_MSG, loopCountArr[0] + 1);
        loopCountArr[0]++;
        if (loopCountArr[0] == LOOPTIME_1)
        {
            if (xTimerStop(pxTimer, 0) == pdTRUE)
            {
                printf("TIMER 1 STOPPED\n");
            }
            xTimerDelete(pxTimer, 10);
        }
    }
    else if (timerID == TIMERID_2)
    {
        printf("t = %d\t%s\t(%d)\n", xTaskGetTickCount() * portTICK_PERIOD_MS, TIMER_2_MSG, loopCountArr[1] + 1);
        loopCountArr[1]++;
        if (loopCountArr[1] == LOOPTIME_2)
        {
            if (xTimerStop(pxTimer, 0) == pdTRUE)
            {
                printf("TIMER 2 STOPPED\n");
            }
            xTimerDelete(pxTimer, 10);
        }
    }
}

void app_main(void)
{
    TimerHandle_t timerHandle = xTimerCreate("timer1", pdMS_TO_TICKS(TIMER_1_PERIOD), pdTRUE, (void *)TIMERID_1, &ATimerCallback);
    TimerHandle_t timerHandle2 = xTimerCreate("timer2", pdMS_TO_TICKS(TIMER_2_PERIOD), pdTRUE, (void *)TIMERID_2, &ATimerCallback);
    if (timerHandle == NULL)
    {
        printf("Timer 1 create fail!\n");
    }
    else
    {
        if (xTimerStart(timerHandle, 0) == pdTRUE)
        {
            printf("TIMER 1 START\n");
        }
    }
    if (timerHandle2 == NULL)
    {
        printf("Timer 2 create fail!\n");
    }
    else
    {
        if (xTimerStart(timerHandle2, 0) == pdTRUE)
        {
            printf("TIMER 2 START\n");
        }
    }
}
