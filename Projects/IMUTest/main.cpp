/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include "WProgram.h"
#include "FreeRTOS_ARM.h"
#include <stdbool.h>
#include <stdio.h>
#include "i2c_t3.h"
#include <SPI.h> 

//// User Libraries ////
#include "RTOS_Tasks.h"
#include "Common_Methods.h"
#include "CommonFunctions.h"

/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define BAUDRATE 38400

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Handels                               //
/////////////////////////////////////////////////////////////////////////////

TaskHandle_t IMUTask_Handel;
TaskHandle_t EncoderTask_Handel;
TaskHandle_t HeartBeatTask_Handel;

/////////////////////////////////////////////////////////////////////////////
//                              Startup                                    //
/////////////////////////////////////////////////////////////////////////////

extern "C" int main(void)
{
    // Initializing USB Serial Communication
    Serial.begin(BAUDRATE);
    
	delay(5000);
    Serial.println("Teensy is Alive!");
	
    // Initializing UART Serial Communication
    // Serial1.begin(38400);
    
    Serial2.begin(115200);
    
/////////////////////////////////////////////////////////////////////////////
//                              RTOS Task Initalization                    //
/////////////////////////////////////////////////////////////////////////////

//// Heart Beat Task ////

    xTaskCreate(
        vHeartBeatTask,         //Function that implements the task
        "Heart",                //Test name for the task
        STACK(128),             //Stack size in words, no bytes
        NULL,                   //Parameter passes into the task
        PRIORITY_CRITICAL,      //Priority at which the task is created
        &HeartBeatTask_Handel   //Used to pass out the created task's handle
    );

    xTaskCreate(
        vIMUTask,               //Function that implements the task
        "Heart",                //Test name for the task
        STACK(256),             //Stack size in words, no bytes
        NULL,                   //Parameter passes into the task
        PRIORITY_HIGH,          //Priority at which the task is created
        &IMUTask_Handel         //Used to pass out the created task's handle
    );
    // Start FreeRTOS
    vTaskStartScheduler();

    // should never return
    while(1);
}


/////////////////////////////////////////////////////////////////////////////
//                              Usful RTOS FUNCTIONS                    //
/////////////////////////////////////////////////////////////////////////////

// #define taskENTER_CRITICAL()             portENTER_CRITICAL()
// #define taskENTER_CRITICAL_FROM_ISR()    portSET_INTERRUPT_MASK_FROM_ISR()
// #define taskEXIT_CRITICAL()              portEXIT_CRITICAL()
// #define taskEXIT_CRITICAL_FROM_ISR( x )  portCLEAR_INTERRUPT_MASK_FROM_ISR( x )