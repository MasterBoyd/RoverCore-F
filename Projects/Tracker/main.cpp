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

/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define BAUDRATE 38400

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Handels                               //
/////////////////////////////////////////////////////////////////////////////

TaskHandle_t Heart;
TaskHandle_t Serial_Task;
TaskHandle_t Sensors_IMU_Task;
TaskHandle_t Motion_Control_Task;

/////////////////////////////////////////////////////////////////////////////
//                             Global Variables                            //
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//                              Startup                                    //
/////////////////////////////////////////////////////////////////////////////

extern "C" int main(void)
{

    // Initializing USB Serial Communication
    Serial.begin(BAUDRATE);
    // while(!Serial) {}
    Serial1.println("Teensy is Alive!");

    // Initializing UART Serial Communication
    Serial1.begin(BAUDRATE);
    Serial1.println("Teensy is Alive!");
    // while(!Serial1) {}
    Serial2.begin(BAUDRATE);
    // while(!Serial2) {}


     analogWriteFrequency(MOTOR_PWM_1, 22000);
     analogWriteFrequency(MOTOR_PWM_2, 22000);
     pinMode(MOTOR_PWM_1, OUTPUT);
     pinMode(MOTOR_PWM_2, OUTPUT);
     pinMode(MOTOR_DIR_1, OUTPUT);
     pinMode(MOTOR_DIR_2, OUTPUT);
     pinMode(CAMERA_MUX, OUTPUT);
     pinMode(CURRENT_SENS_1, INPUT);
     pinMode(CURRENT_SENS_2, INPUT);
/////////////////////////////////////////////////////////////////////////////
//                              RTOS Task Initalization                    //
/////////////////////////////////////////////////////////////////////////////
//// Heart Beat Task ////
    xTaskCreate(
        vHeartBeatTask, //Function that implements the task
        "Heart",        //Test name for the task
        STACK(1024),     //Stack size in words, no bytes
        NULL,           //Parameter passes into the task
        PRIORITY(0),    //Priority at which the task is created
        &Heart          //Used to pass out the created task's handel
    );

//// SerialController Task ////
     xTaskCreate(
         vSerialController,   //Function that implements the task
         "Serial",      //Test name for the task
         STACK(1024),    //Stack size in words, not bytes
         NULL,          //Parameter that is passed into the task
         PRIORITY(1),   //Priority at which the task is created
         &Serial_Task   //Used to pass out the created task's handel
     );
//     PRIORITY_CRITICAL
// PRIORITY_HIGH
// PRIORITY_MEDIUM
// PRIORITY_LOW
     xTaskCreate(
        vSensorsIMUTask,
        "SensorsIMU",
        STACK(2048),
        NULL,
        PRIORITY_HIGH,
        &Sensors_IMU_Task
     );
     xTaskCreate(
        vMotionControlTask,
        "MotionControl",
        STACK(1024),
        NULL,
        PRIORITY(1),
        &Motion_Control_Task
     );
    // Start FreeRTOS
    vTaskStartScheduler();

    // should never return
    while(1);
}
