#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
//#include "WProgram.h"

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////


extern double_3D_t imu_A_Orientation;
extern double_3D_t imu_B_Orientation;
 //Feedback
extern feedback_t feedback;
 //Commands
extern command_t motion_Command;
extern uint8_t active_Camera;
extern float battery_Voltage;

uint32_t test = 0;
uint32_t test2 = 0;

void vHeartBeatTask(void *pvParameters)
{
// Hardware Configuration
    pinMode(13, OUTPUT);

    // Constants
    const TickType_t xDelay = DELAY_MS(50);
    const uint8_t Seq_1[] = {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2};

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
            case 0:
                digitalWrite(13, LOW);
                state++;
                break;
            case 1:
                digitalWrite(13, HIGH);
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

    Serial1.SetToSend(97, (int16_t*)&feedback.local_Orientation.X);
    Serial1.SetToSend(98, (int16_t*)&feedback.local_Orientation.Y);
    Serial1.SetToSend(99, (int16_t*)&feedback.local_Orientation.Z);
    Serial1.SetToSend(100, (int16_t*)&feedback.global_Orientation.X);
    Serial1.SetToSend(101, (int16_t*)&feedback.global_Orientation.Y);
    Serial1.SetToSend(102, (int16_t*)&feedback.global_Orientation.Z);
    Serial1.SetToSend(103, &feedback.lidar_Reading);
    Serial1.SetToSend(104, (int16_t*)&feedback.yaw_Current);
    Serial1.SetToSend(105, (int16_t*)&feedback.pitch_Current);
    Serial1.SetToSend(106, &test);
    Serial1.SetToSend(107, &test2);

    Serial1.SetToReceive(65, &motion_Command.motion_Mode);
    Serial1.SetToReceive(66, &motion_Command.yaw);
    Serial1.SetToReceive(67, &motion_Command.pitch);
    Serial1.SetToReceive(68, &active_Camera);
    Serial1.SetToReceive(69, &battery_Voltage);


    // Task Loop
    while (1)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        //Collect Incomminbg Serial and assign to the set variables
        Serial.CollectIncomming();

        //Send out changed set values over seial
        Serial.SerialSendAll();

            //Collect Incomminbg Serial and assign to the set variables
        Serial1.CollectIncomming();

        //Send out changed set values over seial
        Serial1.SerialSendAll();
    }
}

void vSensorsIMUTask(void *pvParameters)
{
    const TickType_t xDelay = DELAY_MS(10);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Wire.begin();
    bool errorStatus;
    taskENTER_CRITICAL();
    mpu9250 imu_A(MPU9250_A, {1.02, .97, 1.01, 52, 113.5, 142});
    mpu9250 imu_B(MPU9250_B, {1.10, 1.04, .86, 37, 18.5, -147.5});
    errorStatus = imu_A.init();
    if(errorStatus) {
        errorStatus = imu_B.init();
    }
    taskEXIT_CRITICAL();
    while(1)
    {
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        if(errorStatus)
        {
            taskENTER_CRITICAL();
            imu_A_Orientation = imu_A.getOrientation();
            imu_B_Orientation = imu_B.getOrientation();
            taskEXIT_CRITICAL();

        }
        else
        {
            taskENTER_CRITICAL();
            errorStatus = imu_A.init();
            if(errorStatus) {
                errorStatus = imu_B.init();
            }
            taskEXIT_CRITICAL();
        }
    }
}

void vMotionControlTask(void *pvParameters) {
   const TickType_t xDelay = DELAY_MS(50);
   TickType_t xLastWakeTime = xTaskGetTickCount();

   static command_t command;

   while(1) {
       vTaskDelayUntil(&xLastWakeTime, xDelay);

       if(active_Camera == 0)
       {
           digitalWrite(CAMERA_MUX, LOW);
       }
       else
       {
           digitalWrite(CAMERA_MUX, HIGH);
       }

        motion_Command.motion_Mode = SPEED; //Hardcode speed mode for now

        feedback.global_Orientation = imu_A_Orientation;
        feedback.local_Orientation = calculateOrientation(imu_B_Orientation, imu_A_Orientation);
        if(motion_Command.motion_Mode == POSITION) {
            command = motion_Command;
        }
        //motion_Command.yaw = 0.2;
        if(motion_Command.motion_Mode == SPEED) {
            command = motion_Command;
            controlLoopSpeed(command);
            /*
            Serial1.print("X ");
            Serial1.print(imu_A_Orientation.X);
            Serial1.print(" Y: ");
            Serial1.print(imu_A_Orientation.Y);
            Serial1.print(" Z: ");
            Serial1.println(imu_A_Orientation.Z);
            Serial1.print("X ");
            Serial1.print(imu_B_Orientation.X);
            Serial1.print(" Y: ");
            Serial1.print(imu_B_Orientation.Y);
            Serial1.print(" Z: ");
            Serial1.println(imu_B_Orientation.Z);
            Serial1.print("X ");
            Serial1.print(feedback.local_Orientation.X);
            Serial1.print(" Y: ");
            Serial1.print(feedback.local_Orientation.Y);
            Serial1.print(" Z: ");
            Serial1.println(feedback.local_Orientation.Z);
            Serial1.println("\n");
            */

        } else {
            if(controlLoopPosition(command)) {
                command.motion_Mode = SPEED;
                command.pitch = 0.0;
                command.yaw = 0.0;
            }
        }
   }
}

//Controls the Teensy's LED in a sequence
