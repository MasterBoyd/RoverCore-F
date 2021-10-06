#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
//#include "WProgram.h"

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////


void vHeartBeatTask(void *pvParameters)
{

    // Hardware Configuration
    pinMode(13, OUTPUT);

    // Constants
    const TickType_t xDelay = DELAY_MS(500);
    const uint8_t Seq_1[4] = {1, 2, 1, 3};

    // Variables
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8_t state = 0;

    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //HeartBeat State Machine
        switch(Seq_1[state])
        {
            case 1:
                digitalWrite(13, HIGH);
                state++;
                break;
            case 2:
                digitalWrite(13, LOW);
                state++;
                break;
            default:
                state = 0;
                digitalWrite(13, LOW);
                break;
        }
    }
}

//Collects and sends Serial Data
void vSerialController(void *pvParameters)
{
    // Variables
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();


    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //Collect Incomminbg Serial and assign to the set variables
        Serial.CollectIncomming();

        //Send out changed set values over seial
        Serial.SerialSendAll();
    }
}

//Controls the Teensy's LED in a sequence
