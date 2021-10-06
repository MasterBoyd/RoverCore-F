#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
#include <math.h>
//#include "WProgram.h"

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////
char buffer[300] = {0};
int32_t TrajectoryAngle = 0;
uint8_t Mode = 'D';

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

        ////USB SERIAL////

        //Collect Incomminbg Serial and assign to the set variables


        ////UART 1 SERIAL////


    }
}

//Tachometer Code
#define INTERRUPT_PIN 28
#define RPM_F_RATIO 1.98125
uint32_t tacho[] = {0, 0, 0, 0};

inline void TACHOInterruptHandler(uint8_t tachoPin) {
    tacho[tachoPin]++;
}
void ISR0(void) { TACHOInterruptHandler(0); }
void ISR1(void) { TACHOInterruptHandler(1); }
void ISR2(void) { TACHOInterruptHandler(2); }
void ISR3(void) { TACHOInterruptHandler(3); }
// ISR Function array for easy iteration
void (*ISR[4])( void ) = { ISR0, ISR1, ISR2, ISR3 };

void vTachometer(void *pvParameters)
{

    //char buffer[150] = {0};
    uint32_t Frequency = 0;
    uint32_t RPM = 0;
    uint32_t tachold = 0;
    //Setting up TACHOMETER interrupt pins
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(
        digitalPinToInterrupt(INTERRUPT_PIN),
        ISR[0],
        CHANGE
    );
    // Constants
    const TickType_t xDelay = DELAY_MS(100);
    // Variables
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        //Tachometer Calculation
        Frequency = (tacho[0] - tachold)/.2;
        tachold = tacho[0];
        RPM = RPM_F_RATIO * Frequency;
    }
}

void vPropulsionController(void *ptvParameters)
{
    //Variables
    uint32_t MotorPWM[4] = {0};
    uint8_t MotorDirectionPins[4] = {15, 31,11,2};
    uint8_t MotorPWMPins[4] = {23,20,6,3};
    uint32_t MaxPWM = 255/2;
    double WEIGHT = .15;
    int32_t DesiredSpeed[4] = {0};
    double PWMScalor[4] = {0};
    Serial.SetToReceive('S',&DesiredSpeed[0]);
    Serial1.SetToReceive('S',&DesiredSpeed[0]);
        for(int i=0; i<4;i++)
        {
            pinMode(MotorPWMPins[i],OUTPUT);
            analogWriteFrequency(MotorPWMPins[i],22000);
            pinMode(MotorDirectionPins[i],OUTPUT);
        }

    enum MotorControlStates_E
    {
        STATE0 = 1,
        STATE1 = 2,
        TOZERO = 0
    };
    MotorControlStates_E state[4] = {TOZERO};

    enum DriveStates_E
    {
        FORWARD_d = 0,
        TURN_d = 1
    };
    DriveStates_E DriveState = FORWARD_d;

    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int increment = 0;
    //Task Loop
    while(1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        for(int i=0; i<4; i++)
        {
            DesiredSpeed[i] = DesiredSpeed[0];
            switch(state[i]){
                case STATE0:
                    digitalWrite(MotorDirectionPins[i],HIGH);
                    if(DesiredSpeed[i]<0)
                    {
                        state[i] = TOZERO;
                    }
                    break;
                case STATE1:
                    digitalWrite(MotorDirectionPins[i],LOW);
                    if(DesiredSpeed[i]>0)
                    {
                        state[i] = TOZERO;
                    }
                    break;
                case TOZERO:
                    PWMScalor[i] = 0;
                    if(MotorPWM[i] <= 0.2 && MotorPWM[i] >= -0.2)
                    {
                        if(DriveState == FORWARD_d)
                        {
                            DesiredSpeed[2] = DesiredSpeed[0]*-1;
                            DesiredSpeed[3] = DesiredSpeed[0]*-1;
                        }
                        if(DesiredSpeed[i]>0){
                            state[i] = STATE0;
                        }
                        else if(DesiredSpeed[i]<0)
                        {
                            state[i] = STATE1;
                        }
                    }
            }

            MotorPWM[i] = (WEIGHT*PWMScalor[i]) + (1-WEIGHT)*MotorPWM[i];
            analogWrite(MotorPWMPins[i], MotorPWM[i]);
            PWMScalor[i] = (abs(DesiredSpeed[i])*MaxPWM)/100;
        }

        increment++;


    }
}

//Controls the Teensy's LED in a sequence

void vTrajectoryController(void *pvParameters)
{
    // Variables
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();


    for (int i = 0; i < 4; ++i)
    {
        pinMode(TRAJECTORY_PWM_PIN[i], OUTPUT);
        pinMode(TRAJECTORY_DIRECTION_PIN[i], OUTPUT);
    }
    for (int i = 0; i < 3; ++i)
    {
        pinMode(SELECT_PINS[i], OUTPUT);
    }

    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        TrajectoryController(Mode, TrajectoryAngle);
    }
}

void vDriveController(void *pvParameters)
{
        // Variables
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    // Serial1.SetToReceive('M', &Mode);
    // Serial1.SetToReceive('A', &TrajectoryAngle);
    Serial.SetToReceive('M', &Mode);
    Serial.SetToReceive('A', &TrajectoryAngle);
    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        Serial.CollectIncomming();

        //Send out changed set values over seial
        Serial.SerialSendAll();

         //Collect Incomminbg Serial and assign to the set variables
        // Serial1.CollectIncomming();

        // //Send out changed set values over seial
        // Serial1.SerialSendAll();
    }
}