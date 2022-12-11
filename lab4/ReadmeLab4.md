### Embedded System Lab 04
## FreeRTOS Queue Management
# 1. Implementation process
  - Step 1: prepare components _ ESP32 board.  
  - Step 2: set up the environment to connect.  
  - Step 3: Declare the variables needed for the program.  
  - Step 4: Implement function void CreateRequest(void) according to different type.  
  - Step 5: Implement function void ReceptionTask(void) to receive request, classify them and send to queue.  
  - Step 6: Implement function void FuncTask_1(void) and void FuncTask_2(void). These function will check request from front queue is for me or not. If true, it will receive   request and processing.   
  - Step 7: Implement void app_mail() to create queue and tasks.  

# 2. Result
  - Requests: 0,1,2 -- There are 3 request send to queue which need to classify and store in  queue.  
  - Reception: task type A -- Request classified successfully. Request belong to one in TYPE_A, TYPE_B or TYPE_C. In this case, it's TYPE_C. Data of request ( eDataID and IDataValue) has stored in Data_t structure and ready send to queue. Otherwise, there will be a Receiving Error: Can't classify task 3 message with 3 being the type of that request.  
  - Request: Send data to queue successfully. -- The request's data saved into the existing Data_t structure has been successfully sent to the queue. Otherwise, there will be an announcement _Request: Send data to the queue failed._  
  - Response: FuncTask_1 handle data(s: 0, v: 0) -- The function function FuncTask_1() has taken the request at the beginning of the queue (which is the request with eDataID for FuncTask_1()) and processed them, with the source being eDataID ( displays as s: 0) and value as lDataValue (displays as v:0). Conversely, if FuncTask_1() checks the request at the top of the queue and it is not for FuncTask_1(), it will get the message _Response: FuncTask_1 cound not recieve data(s: 1, v: 0)_
