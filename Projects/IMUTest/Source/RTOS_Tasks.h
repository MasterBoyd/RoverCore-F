#ifndef TASKS_H
#define TASKS_H

//// Core Libraries ////
#include "WProgram.h"
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS_ARM.h"
#include "CommonFunctions.h"

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s

/////////////////////////////////////////////////////////////////////////////
//                             Declarations                                //
/////////////////////////////////////////////////////////////////////////////

//Controls the Teensy's LED in a sequence
void vHeartBeatTask(void *pvParameters);

//Collects and sends Serial Data
void vIMUTask(void *pvParameters);

void vEncoderTask(void *pvParameters);

#endif // TASKS_H