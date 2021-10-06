/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include "WProgram.h"
#include "FreeRTOS_ARM.h"
#include <stdbool.h>
#include <stdio.h>

//// User Libraries ////
#include "Methods.h"
#include "RTOS_Tasks.h"
#include "UserInterrupts.h"
#include "Common_Methods.h"
#include "CommonFunctions.h"
/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define BAUDRATE 9600

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Handels                               //
/////////////////////////////////////////////////////////////////////////////

TaskHandle_t Heart;
TaskHandle_t Serial_Task;
TaskHandle_t Current_Indicator_Task;
TaskHandle_t Feedback_Motor_Task;
TaskHandle_t Joystick_Task;

/////////////////////////////////////////////////////////////////////////////
//                              Startup                                    //
/////////////////////////////////////////////////////////////////////////////
extern "C" int main(void)
{

    // Initializing USB Serial Communication
    Serial.begin(BAUDRATE);
     // while(!Serial) {
     //    pinMode(13, OUTPUT);
     //    digitalWrite(13, HIGH);}
    Serial.println("Teensy is Alive!");

    // Initializing UART Serial Communication
    //Serial1.begin(BAUDRATE);
    //while(!Serial1) {}
    //Serial2.begin(BAUDRATE);
    //while(!Serial2) {}

    initialize();

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Task Initalization                    //
/////////////////////////////////////////////////////////////////////////////

//// Heart Beat Task ////
    xTaskCreate(
        vHeartBeatTask, //Function that implements the task
        "Heart",        //Test name for the task
        STACK(128),     //Stack size in words, no bytes
        NULL,           //Parameter passes into the task
        PRIORITY(0),    //Priority at which the task is created
        &Heart          //Used to pass out the created task's handel
    );

//// SerialController Task ////
     xTaskCreate(
         vSerialController,   //Function that implements the task
         "Serial",      //Test name for the task
         STACK(128),    //Stack size in words, not bytes
         NULL,          //Parameter that is passed into the task
         PRIORITY(1),   //Priority at which the task is created
         &Serial_Task   //Used to pass out the created task's handel
     );

     xTaskCreate(
     	vJoystickInput,
     	"joystickInput",
     	STACK(128),
     	NULL,
     	PRIORITY(1),
     	&Joystick_Task
     );

      xTaskCreate(
        vCurrentIndicator,
        "Current",
        STACK(128),
        NULL,
        PRIORITY(2),
        &Current_Indicator_Task
     );

    xTaskCreate(
        vFeedbackMotor,
        "Motor",
        STACK(128),
        NULL,
        PRIORITY(2),
        &Feedback_Motor_Task
     );

    // Start FreeRTOS
    vTaskStartScheduler();

    // should never return
    while(1);
}