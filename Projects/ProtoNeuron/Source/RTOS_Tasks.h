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

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s
#define MAX_MESSAGE_QUEUE_LENGTH 100

/////////////////////////////////////////////////////////////////////////////
//                             Declarations                                //
/////////////////////////////////////////////////////////////////////////////


//Controls the Teensy's LED in a sequence
void vHeartBeatTask(void *pvParameters);

//Collects and sends Serial Data
void vSerialController(void *pvParameters);

// tests basic functions of the PODS board
void vBoardTestTask(void *pvParameters);

#endif // TASKS_H