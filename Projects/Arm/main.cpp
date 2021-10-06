/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include "WProgram.h"
#include "FreeRTOS_ARM.h"
#include <stdbool.h>
#include <stdio.h>
#include "i2c_t3.h"

//// User Libraries ////
#include "Methods.h"
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

TaskHandle_t Heart;
TaskHandle_t Bluetooth;

TaskHandle_t Rotunda;
TaskHandle_t Shoulder;
TaskHandle_t Elbow;
TaskHandle_t Wrist;
TaskHandle_t Claw;


/////////////////////////////////////////////////////////////////////////////
//                              Startup                                    //
/////////////////////////////////////////////////////////////////////////////

extern "C" int main(void)
{
    // Initializing USB Serial Communication
    Serial.begin(BAUDRATE);
    
	//delay(2000);
    Serial.println("Teensy is Alive!");
	
    // // Initializing UART Serial Communication
    Serial1.begin(38400);
    
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
        &Heart                  //Used to pass out the created task's handle
    );

//// SerialController Task ////

     xTaskCreate(
        vBluetoothController,   
        "Bluetooth",               
        STACK(256),             
        NULL,                   
        PRIORITY_HIGH,          
        &Bluetooth                 
);

//// Control System Tasks ////

    // xTaskCreate(
    //     vTransferTestTask,
    //     "vTransferTestTask",
    //     STACK(256),
    //     NULL,
    //     PRIORITY_MEDIUM,
    //     NULL
    // );        


//Rotunda
    xTaskCreate(
        vControlLoopRotunda,
        "vControlLoopRotunda",
        STACK(256),
        NULL,
        PRIORITY_MEDIUM,
        &Rotunda
    );   
// Shoulder     
    xTaskCreate(
        vControlLoopShoulder,
        "vControlLoopShoulder",
        STACK(256),
        NULL,
        PRIORITY_HIGH,
        &Shoulder
    );    
// //// Elbow    
    xTaskCreate(
        vControlLoopElbow,
        "vControlLoopElbow",
        STACK(256),
        NULL,
        PRIORITY_MEDIUM,
        &Elbow
    );
//// Wrist        
    xTaskCreate(
        vControlLoopWrist,
        "vControlLoopWrist",
        STACK(256),
        NULL,
        PRIORITY_MEDIUM,
        &Wrist
    );
// Claw        
    xTaskCreate(
        vControlLoopClaw,
        "vControlLoopClaw",
        STACK(256),
        NULL,
        PRIORITY_MEDIUM,
        &Claw
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