#ifndef TASKS_H
#define TASKS_H

//// Core Libraries ////
#include "WProgram.h"
#include <stdint.h>
#include <stdio.h>
#include "Methods.h"
#include "FreeRTOS_ARM.h"

//// User Libraries ////
#include "UserInterrupts.h"
#include "Methods.h"
#include "mpu9250.h"

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s

/////////////////////////////////////////////////////////////////////////////
//                             Declarations                                //
/////////////////////////////////////////////////////////////////////////////


//Controls the Teensy's LED in a sequence
void vHeartBeatTask(void *pvParameters);

//Collects and sends Serial Data
void vSerialController(void *pvParameters);

void vSensorsIMUTask(void *pvParameters);

void vMotionControlTask(void *pvParameters);

#endif // TASKS_H
