#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
#include "Methods.h"
#include "SerialController.h"

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////

 Command_S A [] =
    {
      [BASE] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 19, .PWM = 0, .mPin = 3, .feedback = 0},
      [SHOULDER] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 16, .PWM = 0, .mPin = 4, .feedback = 0},
      [ELBOW] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 15, .PWM = 0, .mPin = 5, .feedback = 0},
      [WRIST_PITCH] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 14, .PWM = 0, .mPin = 6, .feedback = 0},
      [ROTUNDA_CAM] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 17, .PWM = 0, .mPin = 9, .feedback = 0},
      [CLAW_TORQUE] = {.angle = 0, .joy = 0, .raw = 0, .smooth = 0, .pin = 18, .PWM = 0, .mPin = 24, .feedback = 0}
    };

void vJoystickInput(void *pvParameters)
{
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //task 1
    while(1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        joystickInput(A);
    }
}

void vCurrentIndicator(void *pvParamters)
{
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //task 1
    while(1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        currentIndicator(A);
    }
}

void vFeedbackMotor(void *pvParamters)
{
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //task 1
    while(1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        feedbackMotor(A);
    }
}

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

        Serial.SetToReceive('b', &A[BASE].feedback);
        Serial.SetToReceive('s', &A[SHOULDER].feedback);
        Serial.SetToReceive('e', &A[ELBOW].feedback);
        Serial.SetToReceive('r', &A[ROTUNDA_CAM].feedback);
        Serial.SetToReceive('p', &A[WRIST_PITCH].feedback);
        //Serial.SetToReceive('c', &(A[CLAW_TORQUE].feedback));

    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //Collect Incomminbg Serial and assign to the set variables
        Serial.CollectIncomming();

        //Send out changed set values over seial
        Serial.SerialSendAll();
        Serial.print("base "); 
        Serial.print(A[BASE].feedback); 
        Serial.print(" shoulder "); 
        Serial.print(A[SHOULDER].feedback); 
        Serial.print(" elbow "); 
        Serial.print(A[ELBOW].feedback); 
        Serial.print(" rotate "); 
        Serial.print(A[ROTUNDA_CAM].feedback);
        Serial.print(" pitch "); 
        Serial.println(A[WRIST_PITCH].feedback);
    }
}

//Controls the Teensy's LED in a sequence