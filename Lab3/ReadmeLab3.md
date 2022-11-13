##### Welcome to Lab3.
## **Goal**: In this lab, we are expected to
    • Have a deeper look in FreeRTOS tasks.
    • Understand the task scheduling algorithm in the FreeRTOS.
    • Be able to configure the FreeRTOS scheduling algorithm.
## **Content**
    • The idle task and idle task hook.
    • FreeRTOS scheduling algorithm and the FreeRTOSConfig.h header.
    • Preemptive scheduling versus Co-operative scheduling.
## **Prerequisite Requirement**
    • Have basic knowledge of OS and micro-controller programming.
## **Implementation process**
    • Step 1: Prepare components (NodeMCU ESP32 board). 
    • Step 2: Set up the environment to connect. 
        For the ESP32, a framework has been developed by Espressif called the IoT Development Framework which has become commonly known as "ESP-IDF". It can be found at https://github.com/espressif/esp-idf 
    • Step 3: Reconfigure configUSE_PREEMPTION in esp-idf\components\freertos\include\esp_additions\freertos to choose how the shedule is Pre-emtive.
    • Step 4: Reconfigure configUSE_TIME_SLICING in esp-idf\components\freertos\include\freertos to choose whether Preemtive has TimeSlicing or not.
    • Step 4: Implement the function that supports creating tasks.
    • Step 5: Implement main function.
        – Choose how to create Task to check the system's timing.
        – Create Tasks with xTaskCreatePinnedToCore.
    • Step 6: Save the output to text file and perform statistics by python to check the schedule process of the system.
## **Result**
    The result of the test is placed in the Result folder. I've named the character "x" for task 1, "y" for task 2, and "z" for task 3. After running I save the result in the text file to analyze. Since we only PIN these tasks to core 0 (NOT CORE 1), it runs as expected from the document from FreeRTOS, which is designed to run on MCU with a single core.
