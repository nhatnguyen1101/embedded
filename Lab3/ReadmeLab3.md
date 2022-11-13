##### Welcome to Lab3.
## **Goal**: In this lab, we are expected to
• Have a deeper look in FreeRTOS tasks.\
• Understand the task scheduling algorithm in the FreeRTOS.\
• Be able to configure the FreeRTOS scheduling algorithm.
## **Content**
• The idle task and idle task hook.\
• FreeRTOS scheduling algorithm and the FreeRTOSConfig.h header.\
• Preemptive scheduling versus Co-operative scheduling.
## **Prerequisite Requirement**
• Have basic knowledge of OS and micro-controller programming.
## **Implementation process**
• Step 1: Prepare components (NodeMCU ESP32 board). \
• Step 2: Set up the environment to connect. \
    For the ESP32, a framework has been developed by Espressif called the IoT Development Framework which has become commonly known as "ESP-IDF". It can be found at https://github.com/espressif/esp-idf \
• Step 3: Reconfigure configUSE_PREEMPTION in
esp-idf\components\freertos\include\esp_additions\freertos to choose how the shedule is Pre-emtive.
• Step 4: Reconfigure configUSE_TIME_SLICING in
esp-idf\components\freertos\include\freertos to choose whether Preemtive has TimeSlicing or not
are not.
• Step 4: Implement the function that supports creating tasks.
• Step 5: Implement main function.
  – Choose how to create Task to check the system's timing.\
  – Create Tasks with xTaskCreatePinnedToCore.\
• Step 6: Save the output to Excel file and perform statistics to check the schedule process of the system.
## **Result**
