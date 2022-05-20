/*
CPE-555 Real-Time and Embedded Systems
Stevens Institute of Technology
Spring 2022
*/

// Implementing the program using FreeRTOS 

// Standard header file for c programming 
#include <stdio.h>

// FreeRTOS and Standard header files

#include "FreeRTOS.h" 
#include "task.h"
#include "queue.h“
#include "semphr.h"

/* Global variables used in my program */
TaskHandle_t DisplayHandle;
TaskHandle_t TimeHandle;
SemaphoreHandle_t xSemaphore = NULL; 
QueueHandle_t xQueue;


// Creating the function for Display task
void DisplayTask(){
// creating the variables
    int time, minutes, seconds = 0;
    for(;;){
        //check the condition for semaphore 
        if (xSemaphore != NULL){ 
            if (xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE){
                if(xQueue != 0){
                    xQueueReceive(xQueue, &time, 10);
                }
                // check for semaphore and receive from Queue

                // converting total seconds to minutes and seconds
                minutes = time/60;  // calculating minutes
                seconds = time - minutes*60; // calculating seconds

                // if time is up, print statement "Time is up!" 
                if(time == 0){ 
                printf("0:00\n");
                printf("Time is up!\n\n"); 
                vTaskDelete(DisplayHandle); //deleting the display task
                 }
                // Display the value of minutes and seconds as per the standard format given in the homework
                // if time is not completely zero.
                printf("%d:", minutes);
                if(seconds < 10){
                    printf("0%d\n", seconds);
                } 
                else{
                    printf("%d\n", seconds);
                }
            } 
        } 
    } 
}


// Function for Time Task
void TimeTask(int par){
    int time = par;

    //Parameter passing in the function will be tranferred to the queue 
    xQueueSend(xQueue, &time, 0);
    
    
    //Creating the binary semaphore to allow display task to display the initial time
    xSemaphore = xSemaphoreCreateBinary();
    
    //allowing the display task to run first
    xSemaphoreGive(xSemaphore);
    
    for (;;){

        if (time != 0){  
        time--;
        //Decreasing the time until it goes to 0
        }
        else {
        vTaskDelete(TimeHandle); // Deleting the task when time will be 0 
        }

        vTaskDelay(1000/portTICK_RATE_MS); // creating the delay of 1 second
   
        // sending the decremented counter to queue
        xQueueSend(xQueue, &time, 0);
   
        // sending the binary semaphore to display task
        xSemaphoreGive(xSemaphore);
  
    }
}


// main function to run the code

int main(void) {
    // creating the variables and initialize to zero
    int mins, secs, total = 0;  

    setvbuf(stdout, NULL, _IONBF , 0);
    //disabling the buffering for stream so that it allows the statement to print fast

    printf("Enter Minutes\n");
    scanf("%d", &mins);
    printf("Enter Seconds\n");
    scanf("%d", &secs);
    // input the value of minutes and seconds from users

    total = secs + mins*60;
    // calculating the total number of seconds

    xQueue = xQueueCreate(10, sizeof(int));
    // creating the queue for passing the variable from one function to another function

    xTaskCreate( TimeTask, "TimeTask", 1000, total, 2, &TimeHandle);
    xTaskCreate( DisplayTask, "DisplayTask", 1000, NULL, 1, &DisplayHandle);
    // In the above tasks, time task has the higher priority over displaytask

    vTaskStartScheduler();
    return 0;
}




