#ifndef TASKS_H
#define TASKS_H

//// Core Libraries ////
#include "WProgram.h"
#include <stdint.h>
#include <stdio.h>
#include "Methods.h"
#include "FreeRTOS_ARM.h"

//// User Libraries ////
// #include "UserInterrupts.h"
#include "Methods.h"

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s

/////////////////////////////////////////////////////////////////////////////
//                             Declarations                                //
/////////////////////////////////////////////////////////////////////////////

//Controls the Teensy's LED in a sequence
void vHeartBeatTask(void *pvParameters);

//Collects and sends Serial Data
void vBluetoothController(void *pvParameters);

//In charge of I2C Data Collection	 
void vI2CControlLoop(void *pvParameters);

//Control Loops
void vTransferTestTask(void *pvParameters);
void vControlLoopRotunda(void *pvParameters);
void vControlLoopShoulder(void *pvParameters);
void vControlLoopElbow(void *pvParameters);
void vControlLoopWrist(void *pvParameters);
void vControlLoopClaw(void *pvParameters);

#endif // TASKS_H