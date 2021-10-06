#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
#include "Methods.h"
//#include "WProgram.h"

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////

#define LOOP_TIME           100
#define LOOPS_TIL_UPDATE    60 //10 = 1second; 60 = 6seconds; 600 = 1min

feedback_t feedback;
flags_t flags;
commands_t commands;
SemaphoreHandle_t xSemaphore;

void vCurrentSense(void *pvParameters) 
{
    const TickType_t xDelay = DELAY_MS(LOOP_TIME);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    openCircuitVoltage(&feedback);
    closeModuleRelays(&feedback, &flags, &commands);
    // feedback.mAhRemaining = MAX_MAH;
    for (uint8_t delay_loop = ZERO; delay_loop < FIVE; delay_loop++) //half-second delay before lowering relay voltage
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
    updatePWM(&feedback, &flags);
   
    uint16_t loopsSinceLastUpdate = ZERO;

    //task loop
    while(FOREVER) {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        currentRead(&feedback);

        coulombCount(&feedback);

        currentCheck(&feedback, &flags, &commands);

        if (loopsSinceLastUpdate >= LOOPS_TIL_UPDATE) {
            updatePWM(&feedback, &flags);
            loopsSinceLastUpdate = ZERO;
        }

        loopsSinceLastUpdate++;
    }
}

void vTempSense(void *pvParameters)
{
    // Serial.println("got here 0");
    WireSetup();

    const TickType_t xDelay = DELAY_MS(LOOP_TIME);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //task loop
    while(FOREVER) {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        tempRead(&feedback);
        tempCheck(&feedback);
    }
}


void vHeartBeatTask(void *pvParameters)
{
    // Hardware Configuration
    pinMode(LED_PIN, OUTPUT);

    // Constants
    const TickType_t xDelay = DELAY_MS(LOOP_TIME);
    const uint8_t Seq_1[] = {1, 2, 1, 2, 1, 1, 1, 1, 3};

    // Variables
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8_t state = ZERO;

    // Task Loop
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //HeartBeat State Machine
        switch(Seq_1[state])
        {
            case 1:
                digitalWrite(LED_PIN, HIGH);
                state++;
                break;
            case 2:
                digitalWrite(LED_PIN, LOW);
                state++;
                break;
            default:
                state = 0;
                digitalWrite(LED_PIN, LOW);
                // Serial.println("Alive!");
                break;
        }
    }
}

void vBluetoothController(void *pvParameters)
{
    //// Initalization //// 
    const TickType_t xDelay = DELAY_MS(LOOP_TIME);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    xSemaphore = xSemaphoreCreateBinary(); //create mutex handel for shared objects

    //// Attached Variables to be Sent/Received through Bluetooth////
    //Incoming Commands from Mission Control
    Serial1.SetToReceive('a', &commands.batRelay1);
    Serial1.SetToReceive('b', &commands.batRelay2);
    Serial1.SetToReceive('c', &commands.batRelay3);
    Serial1.SetToReceive('d', &commands.driveBackupRelay);
    Serial1.SetToReceive('f', &commands.armRelay);
    Serial1.SetToReceive('g', &commands.driveFrontRelay);
    Serial1.SetToReceive('h', &commands.driveBackRelay);
    Serial1.SetToReceive('i', &commands.allPower);

    //feedback sent to Rovercore-s lobe
    Serial1.SetToSend('0', &feedback.realTimeVoltage);
    Serial1.SetToSend('1', &feedback.mAhRemaining);
    // Serial1.SetToSend('2', &feedback.currentDriveBackup);
    Serial1.SetToSend('3', &feedback.currentSteer);
    Serial1.SetToSend('4', &feedback.currentArm);
    Serial1.SetToSend('5', &feedback.currentDriveFront);
    Serial1.SetToSend('6', &feedback.currentDriveBack);
    Serial1.SetToSend('7', &feedback.temp1); 
    Serial1.SetToSend('8', &feedback.temp2); 
    Serial1.SetToSend('9', &feedback.temp3); 
    Serial1.SetToSend('A', &feedback.errorCode);

    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //Collect Incomming Serial and assign to the set variables
        // Serial.CollectIncomming();
        // feedback.currentArm = feedback.currentArm +2;
        Serial1.CollectIncomming();
        // Serial.print("Feedback:");
        // Serial.println(feedback.currentArm);

        //may need mutex here
        commandResponse(&feedback, &flags, &commands, &xSemaphore);

        //Send out changed set values over seial
        // Serial.SerialSendAll();
        // Serial1.println("Hello.");
        // Serial1.SerialSend('7');
        // Serial1.SerialSend('8');
        // Serial1.SerialSend('9');
        // Serial1.SerialSend('A');
        Serial1.SerialSendAll();
    }
}

//Collects and sends Serial Data
// void vSerialController(void *pvParameters)
// {
//     // Variables
//     const TickType_t xDelay = DELAY_MS(2000);
//     TickType_t xLastWakeTime = xTaskGetTickCount();

//     Serial.SetToSend('0', &feedback.realTimeVoltage);
//     Serial.SetToSend('1', &feedback.mAhRemaining);
//     Serial.SetToSend('2', &feedback.currentDrive);
//     Serial.SetToSend('3', &feedback.currentSteer);
//     Serial.SetToSend('4', &feedback.currentArm);
//     Serial.SetToSend('5', &feedback.currentIntel);
//     Serial.SetToSend('6', &feedback.currentMast);
//     Serial.SetToSend('7', &feedback.temp1); 
//     Serial.SetToSend('8', &feedback.temp2); 
//     Serial.SetToSend('9', &feedback.temp3); 

//     // Task Loop
//     while (FOREVER)
//     {
//         //Absolute Delay
//         vTaskDelayUntil(&xLastWakeTime, xDelay);

//         //Collect Incomminbg Serial and assign to the set variables
//         Serial.CollectIncomming();

//         //Send out changed set values over serial
//         Serial.SerialSendAll();
//     }
// }

//Controls the Teensy's LED in a sequence
