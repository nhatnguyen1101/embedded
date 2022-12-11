#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/queue.h"

/* Tasks Queues.*/
xQueueHandle myQueue;

/* The structure is stored on a queue.*/
typedef struct
{
    uint8_t eDataID;    // The source of the data contained
    int32_t lDataValue; // The value of the data contained
} Data_t;

#define MAX_NUM_REQUEST 3
uint8_t request[MAX_NUM_REQUEST] = { 0, 0, 0 };
bool flag_HaveRequest = false;

/* Requests sent from somewhere will only be of 3 types:*/
#define TYPE_A 0
#define TYPE_B 1
#define TYPE_C 2

/* Create requests with different types.*/
void CreateRequest(void)
{
    uint8_t typeRandom = 0;

    while (1)
    {
        /* Create 3 requests.*/
        request[0] = (typeRandom + 0) % 4;
        request[1] = (typeRandom + 1) % 4;
        request[2] = (typeRandom + 2) % 4;
        typeRandom = typeRandom + 3;
        
        flag_HaveRequest = true;

        printf("\n\nRequests: { %d, %d, %d}\n",request[0],request[1],request[2]);

        /* Keep sending requests after waiting 3 seconds.*/
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
/*  The reception task is designed to:
        + receive requests from somewhere
        + and classify these tasks and send them to a queue.*/
void ReceptionTask(void)
{
    /* xTicksToWait: The maximum amount of time the task should remain in the Blocked state to wait.*/
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    /* Data of tasks sent to the queue (including the value and source of the data).*/
    Data_t taskData;

    /*Order of requested tasks.*/
    uint8_t idx;

    while (1)
    {
        /* Check if the request is sent from somewhere.*/
        if (flag_HaveRequest)
        {
            /*Classify these tasks and send them to a queue.*/            
            for (idx = 0; idx < MAX_NUM_REQUEST; idx++)
            {
                switch (request[idx])
                {
                case TYPE_A:
                    taskData.eDataID = 0;
                    taskData.lDataValue = 0;
                    printf("Reception: task type A.\n");
                    break;
                case TYPE_B:
                    taskData.eDataID = 1;
                    taskData.lDataValue = 10;
                    printf("Reception: task type B.\n");
                    break;
                case TYPE_C:
                    taskData.eDataID = 1;
                    taskData.lDataValue = 100;
                    printf("Reception: task type C.\n");
                    break;
                default:
                    taskData.eDataID = request[idx];
                    taskData.lDataValue = 0;
                    flag_HaveRequest = false;
                    printf("Receiving Error: Can't classify task %d\n", request[idx]);
                    break;
                }

                if (flag_HaveRequest)
                {
                    /* Send Data of Task to a queue.*/
                    if (xQueueSendToFront(myQueue, &taskData, xTicksToWait) == pdPASS)
                    {
                        printf("Request: Send data to queue successfully\n");
                    }
                    else
                    {
                        printf("Request: Send data to the queue failed\n");
                    }
                }
            }
            flag_HaveRequest = false;
        }
        vTaskDelay(50 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
/*  The functional task would check if the next request is for it or not.
        + If yes, it will receive the request and handle it.
        + Vice versa, it does nothing.*/
void FuncTask_1(void)
{
    /*xTicksToWait: The maximum amount of time the task should remain in the Blocked state to wait.*/
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    /* Data of tasks sent to the queue (including the value and source of the data).*/
    Data_t taskData;

    /*FuncTask_1 only accepts requests of type A.*/
    uint8_t task_eDataID = TYPE_A;

    while (1)
    {
        /*Peek data from queue and check if this request is for this functional task.*/
        if (xQueuePeek(myQueue, &taskData, xTicksToWait) == pdPASS)
        {
            if (taskData.eDataID == task_eDataID)
            {
                /*Pop data from queue.*/
                if (xQueueReceive(myQueue, &taskData, xTicksToWait) == pdPASS)
                {
                    printf("Response: FuncTask_1 handle data(s: %d, v: %d)\n", taskData.eDataID, taskData.lDataValue);
                }
                else
                {
                    printf("Response: FuncTask_1 cound not recieve data(s: %d, v: %d)\n", taskData.eDataID, taskData.lDataValue);
                }
            }
        }
        vTaskDelay(50 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}
/*  The functional task would check if the next request is for it or not.
        + If yes, it will receive the request and handle it.
        + Vice versa, it does nothing.*/
void FuncTask_2(void* parameter)
{
    /*xTicksToWait: The maximum amount of time the task should remain in the Blocked state to wait.*/
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    /* Data of tasks sent to the queue (including the value and source of the data).*/
    Data_t taskData;

    /*FuncTask_1 only accepts requests of type B.*/
    uint8_t task_eDataID = TYPE_B;

    while (1)
    {
        /*Peek data from queue and check if this request is for this functional task.*/
        if (xQueuePeek(myQueue, &taskData, xTicksToWait) == pdPASS)
        {
            if (taskData.eDataID == task_eDataID)
            {
                /*Pop data from queue.*/
                if (xQueueReceive(myQueue, &taskData, xTicksToWait) == pdPASS)
                {
                    printf("Response: FuncTask_2 handle data(s: %d, v: %d)\n", taskData.eDataID, taskData.lDataValue);
                }
                else
                {
                    printf("Response: FuncTask_2 cound not recieve data(s: %d, v: %d)\n", taskData.eDataID, taskData.lDataValue);
                }
            }
        }

        vTaskDelay(50 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}
void app_main()
{
   /* Create a myQueues queue that can hold up to 5 elements Data_t.*/
    myQueue = xQueueCreate(5, sizeof(Data_t));

    if (myQueue == NULL)
        printf("The queue cannot be created: %p \n", myQueue);

    xTaskCreate(CreateRequest,  "CreateRequest", 2048, NULL, 2, NULL);
    xTaskCreate(ReceptionTask,  "ReceptionTask", 2048, NULL, 1, NULL);
    xTaskCreate(FuncTask_1,     "FuncTask_1",    2048, NULL, 1, NULL);
    xTaskCreate(FuncTask_2,     "FuncTask_2",    2048, NULL, 1, NULL);
}