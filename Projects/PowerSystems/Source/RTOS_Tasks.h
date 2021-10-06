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


#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s
// #define OPEN_CIRCUIT(x) 2837.0633692842(x)^4 - 44529.3543750085(x)^3 + 261684.711540345(x)^2 - 682233.295008619(x) + 665646.210814841


/////////////////////////////////////////////////////////////////////////////
//                             Declarations                                //
/////////////////////////////////////////////////////////////////////////////


//reads from current sensors
void vCurrentSense(void *pvParameters);

//read from temperature sensors
void vTempSense(void *pvParameters);

//Controls the Teensy's LED in a sequence
void vHeartBeatTask(void *pvParameters);

//Bluetooth Communication
void vBluetoothController(void *pvParameters);

//Collects and sends Serial Data
// void vSerialController(void *pvParameters);

#endif // TASKS_H