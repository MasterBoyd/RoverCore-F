#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
#include "WProgram.h"
#include "CommonFunctions.h"
#include "SerialController.h"
#include "BNO055-Serial.h"
#include "quaternion.hpp"
#include "AS5048A-Magnetic-Encoder.h"


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
                Serial.println("Alive");
                digitalWrite(13, LOW);
                break;
        }
    }
}


void vIMUTask(void *pvParameters)
{
    // Constants
    const TickType_t xDelay = DELAY_MS(100);

    // Variables
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // IMU
    BNO055 IMU(&Serial2);
    IMU.init();
    Euler IMU_Data;
    
    // Encoder
    Encoder_Init();
    uint16_t Encoder_Data;
    uint16_t Encoder_Magnetude;

    //Data = IMU.getEuler(); 
    
    // Task Loop
    while (1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        // Encoder_Get_Data(&Encoder_Data);
        // Encoder_Get_Magnetude(&Encoder_Magnetude);
        // Quat = IMU.getQuaternion();
        // Data2 = Quat.toEuler();
        double  Pitch = 0;

        if(Encoder_Get_Data(&Encoder_Data, 25))
        {
            double Encoder_Ang = map(Encoder_Data, 0, 16383, 0, 360);
            double Encoder_Ang_adj = SoftwareaAdjust(Encoder_Ang, 0, 360, 0);
            Serial.print("Encoder Ang: ");
            Serial.print(Encoder_Ang);
            Serial.print(" Adj:");
            Serial.print(Encoder_Ang_adj);
        }    
        if(IMU.getEuler(&IMU_Data))
        {
            Serial.print(" Pitch:");
            Pitch = map(IMU_Data.Y/16, -180, 180, 0, 360);
            Pitch = SoftwareaAdjust(Pitch, 0, 360, 90);
            Serial.print(Pitch);
            Serial.println("  ");
        }
            
    }
}


void vEncoderTask(void *pvParameters)
{
    // Constants
    const TickType_t xDelay = DELAY_MS(200);

    // Variables
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Encoder_Init();
    
    // Task Loop
    while (1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        //Encoder_Get_Data();

    }
}
