#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
#include "WProgram.h"
#include "SerialController.h"
#include "CommonFunctions.h"
#include "Servo.h"


#define WATCHDOG_LOOP_TIME_MS   100
#define BLUETOOTH_LOOP_TME_MS   100
#define I2C_LOOP_TIME_MS        100

#define ROTUNDA_LOOP_TIME_MS    100
#define SHOULDER_LOOP_TIME_MS   100
#define ELBOW_LOOP_TIME_MS      100
#define WRIST_LOOP_TIME_MS      100
#define CLAW_LOOP_TIME_MS       100
#define ANGLE_MAP_SIZE          41

#define ELBOW_RIGHT_TO_LEFT(x)  (1.054*x)+26.5
#define AVERAGE_SIZE            256

int16_t AngleToElbowPotentiometerMap[ANGLE_MAP_SIZE] = 
{
    950, 928, 905, 883, 860, 838, 815, 793, 770, 748,
    725, 703, 680, 658, 635, 613, 590, 568, 545, 523,
    500, 478, 455, 433, 410, 388, 365, 343, 320, 298,
    275, 253, 230, 208, 185, 163, 140, 118, 95, 73, 50
};

/////////////////////////////////////////////////////////////////////////////
//                             Definitions                                 //
/////////////////////////////////////////////////////////////////////////////
Commands_t MC_Commands;
Feedback_t Feedback;
Current_t Current;
// bool I2C_Saftey_Flag = 1;

void vHeartBeatTask(void *pvParameters)
{

    // Hardware Configuration
    pinMode(13, OUTPUT);

    // Constants
    const TickType_t xDelay = DELAY_MS(1000);
    uint8_t Seq_1[4] = {1, 2, 1, 3};

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
        //Serial.println("ALIVE!");
    }
}

//Collects and sends Serial therough UART
void vBluetoothController(void *pvParameters)
{
    //// Initalization //// 
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //// Attached Variables to be Sent/Received through Bluetooth////
    //Incoming Commands from Mission Control

    Serial1.SetToReceive('a', &(MC_Commands.Rotunda));
    Serial1.SetToReceive('b', &(MC_Commands.Shoulder));
    Serial1.SetToReceive('c', &(MC_Commands.Elbow));
    Serial1.SetToReceive('d', &(MC_Commands.Wrist_Pitch));
    Serial1.SetToReceive('e', &(MC_Commands.Wrist_Roll));
    Serial1.SetToReceive('f', &(MC_Commands.Claw));
    Serial1.SetToReceive('g', &(MC_Commands.Claw_Torque));
    Serial1.SetToReceive('h', &(MC_Commands.Camera_Select));
    Serial1.SetToReceive('i', &(MC_Commands.Rotunda_Camera));

    // Serial.SetToReceive('a', &MC_Commands.Rotunda);
    // Serial.SetToReceive('b', &MC_Commands.Shoulder);
    // Serial.SetToReceive('c', &MC_Commands.Elbow);
    // Serial.SetToReceive('d', &MC_Commands.Wrist_Pitch);
    // Serial.SetToReceive('e', &MC_Commands.Wrist_Roll);
    // Serial.SetToReceive('f', &MC_Commands.Claw);
    // Serial.SetToReceive('g', &MC_Commands.Camera_Select);
    // Serial.SetToReceive('h', &MC_Commands.Rotunda_Camera);



    //Sending out Positional Feedback to Mission Control
    // Serial1.SetToSend(9 , &Feedback.Rotunda);
    // Serial1.SetToSend(10, &Feedback.Shoulder);
    // Serial1.SetToSend(11, &Feedback.Elbow_L);
    // Serial1.SetToSend(12, &Feedback.Elbow_R);
    // Serial1.SetToSend(13, &Feedback.Wrist_Pitch);
    // Serial1.SetToSend(14, &Feedback.Wrist_Roll);
    // Serial1.SetToSend(15, &Feedback.Teensy_Temp);

    // //Sending out Current Feedback to Mission Control.
    // Serial1.SetToSend(16, &Current.Rotunda);
    // Serial1.SetToSend(17, &Current.Shoulder);
    // Serial1.SetToSend(18, &Current.Elbow_L);
    // Serial1.SetToSend(19, &Current.Elbow_R);
    // Serial1.SetToSend(20, &Current.Wrist_L);
    // Serial1.SetToSend(21, &Current.Wrist_R);
    // Serial1.SetToSend(22, &Current.Claw);


    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        ////SensorCheck////
        // Serial.print((int)MC_Commands.Mux);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Rotunda);
        // Serial.print(" ");
        // Serial.print((int)MC_Commands.Rotunda_Camera);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Shoulder);
        // Serial.print(" ");
        // Serial.print((int)Feedback.Shoulder);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Elbow);
        // Serial.print(" ");
        // Serial.print((int)Feedback.Elbow_L);
        // Serial.print(" ");
        // Serial.print((int)Feedback.Elbow_R);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Wrist_Pitch);
        // Serial.print(" ");
        // Serial.print((int)Feedback.Wrist_Pitch);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Wrist_Roll);
        // Serial.print("  ");
        // Serial.print((int)Feedback.Wrist_Roll);
        // Serial.print("|");
        // Serial.print((int)MC_Commands.Claw);
        // Serial.print("  ");
        // Serial.println((int)MC_Commands.Claw_Torque);

        // Serial1.print((int)MC_Commands.Rotunda);
        // Serial1.print(" ");
        // Serial1.print((int)MC_Commands.Rotunda_Camera);
        // Serial1.print("|");
        // Serial1.print((int)MC_Commands.Shoulder);
        // Serial1.print(" ");
        // Serial1.print((int)Feedback.Shoulder);
        // Serial1.print("|");
        // Serial1.print((int)MC_Commands.Elbow);
        // Serial1.print(" ");
        // Serial1.print((int)Feedback.Elbow_L);
        // Serial1.print(" ");
        // Serial1.print((int)Feedback.Elbow_R);
        // Serial1.print("|");
        // Serial1.print((int)MC_Commands.Wrist_Pitch);
        // Serial1.print(" ");
        // Serial1.print((int)Feedback.Wrist_Pitch);
        // Serial1.print("|");
        // Serial1.print((int)MC_Commands.Wrist_Roll);
        // Serial1.print(" ");
        // Serial1.print((int)Feedback.Wrist_Roll);
        // Serial1.print("|");
        // Serial1.print((int)MC_Commands.Claw);
        // Serial1.print(" ");
        // Serial1.println((int)MC_Commands.Claw_Torque);

        
        


        //Collect Incomminbg Serial and assign to the set variables
        //Serial.println(Serial1.GetIt());
        Serial.CollectIncomming();

        Serial1.CollectIncomming();

        //Send out changed set values over seial
        Serial.SerialSendAll();

        Serial1.SerialSendAll();
    }
}


//In charge of I2C Data Collection   
void vI2CControlLoop(void *pvParameters)
{
    //// Initalization ////
    const TickType_t xDelay = DELAY_MS(I2C_LOOP_TIME_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}



int volatile Rotunda_pulse_time = 1500;
void RotundaHandler(void) {
    const int MAX_PERIOD = 20000;
    static int volatile timer_count = 0;
    static bool volatile switch_flag = false;
    timer_count += 4;
    if(timer_count >= MAX_PERIOD)
    {
        timer_count = 0;
        switch_flag = false;
        digitalWrite(ROTUNDA_SERVO, HIGH);
    }
    else if(!switch_flag)
    {
        if(timer_count >= Rotunda_pulse_time)
        {
            digitalWrite(ROTUNDA_SERVO, LOW);
            switch_flag = true;
        }
    }
}


int volatile Camera_pulse_time = 1500;
void CameraHandler(void) {
    const int MAX_PERIOD = 20000;
    static int volatile timer_count = 0;
    static bool volatile switch_flag = false;
    timer_count += 4;
    if(timer_count >= MAX_PERIOD)
    {
        timer_count = 0;
        switch_flag = false;
        digitalWrite(ROTUNDA_CAMERA_PWM, HIGH);
    }
    else if(!switch_flag)
    {
        if(timer_count >= Camera_pulse_time)
        {
            digitalWrite(ROTUNDA_CAMERA_PWM, LOW);
            switch_flag = true;
        }
    }
}
////Rotunda////
#define ROT_Offset -85
#define ROT_LOWER_LIMIT 1000
#define ROT_UPPER_LIMIT 2080

////Camera////
#define CAM_Offset 0
#define CAM_LOWER_LIMIT 800
#define CAM_UPPER_LIMIT 2200

void vControlLoopRotunda(void *pvParameters)
{
    //// Initalization ////
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    pinMode(CAMERA_MUX_1, OUTPUT);
    pinMode(CAMERA_MUX_2, OUTPUT);
    pinMode(ROTUNDA_SERVO, OUTPUT);
    pinMode(ROTUNDA_CAMERA_PWM, OUTPUT);
    MC_Commands.Rotunda = 1500;
    MC_Commands.Rotunda_Camera = 180;
    uint16_t Cam_Command_Transformed = 1500;
    
    // digitalWrite(ROTUNDA_SERVO, HIGH);
    IntervalTimer RotundaTimer;
    RotundaTimer.begin(RotundaHandler, 4);
    
    IntervalTimer CameraTimer;
    CameraTimer.begin(CameraHandler, 4);
    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);

        ////Rotunda Control////
        static int Rot_Command_Transformed = 1500;
        if(((MC_Commands.Rotunda > 999) && MC_Commands.Rotunda < 2081))
        {
            Rot_Command_Transformed = (int)MC_Commands.Rotunda + ROT_Offset;
        }

        if(Rot_Command_Transformed > ROT_LOWER_LIMIT && Rot_Command_Transformed < ROT_UPPER_LIMIT)
        {
            Rotunda_pulse_time = Rot_Command_Transformed;
        }

        ////Camera Control////
        // Need to DEFINE magic numbers: map (mc_cmd, mc_min, mc_max, min pulse, max pulse)
        static int Cam_Command_Transformed = 180;
        if((MC_Commands.Rotunda_Camera > 89) && (MC_Commands.Rotunda_Camera < 271))
        {
            Cam_Command_Transformed = map(MC_Commands.Rotunda_Camera + CAM_Offset, 90, 270, CAM_UPPER_LIMIT, CAM_LOWER_LIMIT);
        }
        
        if(Cam_Command_Transformed > CAM_LOWER_LIMIT && Cam_Command_Transformed < CAM_UPPER_LIMIT)
        {
            Camera_pulse_time = Cam_Command_Transformed;
        }

        // Serial.print("");  Serial.print((int)MC_Commands.Rotunda);
        // Serial.print(" ");  Serial.print((int)Rotunda_pulse_time);

        // Serial.print(" | "); Serial.print((int)MC_Commands.Rotunda_Camera);
        // Serial.print(" ");  Serial.println((int)Camera_pulse_time);
        
        ////Multiplexor Control////
        if(MC_Commands.Camera_Select == 0)
        {
            digitalWrite(CAMERA_MUX_1, LOW);
            digitalWrite(CAMERA_MUX_2, LOW);
        }
        if(MC_Commands.Camera_Select == 1)
        {
            digitalWrite(CAMERA_MUX_1, LOW);
            digitalWrite(CAMERA_MUX_2, HIGH);
        }
        if(MC_Commands.Camera_Select == 2)
        {
            digitalWrite(CAMERA_MUX_1, HIGH);
            digitalWrite(CAMERA_MUX_2, LOW);
        }
        if(MC_Commands.Camera_Select == 3)
        {
            digitalWrite(CAMERA_MUX_1, HIGH);
            digitalWrite(CAMERA_MUX_2, HIGH);
        }
    }
}

void vControlLoopShoulder(void *pvParameters)
{
    //// Initalization ////
    const TickType_t xDelay = DELAY_MS(5);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Encoder_Init();
    pinMode(SHOULDER_DIR, OUTPUT);
    pinMode(SHOULDER_PWM, OUTPUT);
    analogWriteFrequency(SHOULDER_PWM, 30000);
    analogWrite(SHOULDER_PWM, 0);
    

    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);   

        uint32_t Shoulder = MC_Commands.Shoulder;
        ShoulderControlSystem(Shoulder, &Feedback);

    }
}

void vControlLoopElbow(void *pvParameters)
{
    //// Initalization ////
    const TickType_t xDelay = DELAY_MS(10);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // Index + 105 = input angle

    // Limitations: DesiredPosition needs to be mapped to Command angle
    //              Only RIGHT ELBOW implemented
    //              Both RIGHT and LEFT must have the same DIR
    // May not need 32-bit integers. 16-bits may suffice

    // HIGH = Rod out, LOW = Rod in
    bool ElbowDirection = HIGH; 

    int32_t ElbowRightFeedback;
    int32_t ElbowLeftFeedback;
    int32_t ElbowRightCurrent;
    int32_t ElbowLeftCurrent;
    int32_t DesiredPosition = 500;
    MC_Commands.Elbow = 500;
    int32_t FilteredMCCommand = 20;
    MC_Commands.Elbow = 125;

    int32_t inputVoltage = 25.6;
    int32_t outputVoltage = 12;
    motorControl_t PWM_Left;
    motorControl_t PWM_Right;
    uint16_t OutputPWM;
    int32_t OutputPID;
    int32_t MaxPWM = dutyCycleVoltageTransfer(inputVoltage, outputVoltage);
    int32_t MinPWM = MaxPWM / 5;    // actuator should not go slower than 20% of max speed
    int32_t Epsilon = 5;
    
    double Kp = 1;
    double Ki = 0.005;
    double dt = 10;
    double Error = 0;
    double SyncError;
    double Integral = 0;

    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        // FilteredMCCommand = MC_Commands.Elbow-105;
        // if (FilteredMCCommand < 0)  FilteredMCCommand = 0;
        // if (FilteredMCCommand > 40) FilteredMCCommand = 40;

        // DesiredPosition = AngleToElbowPotentiometerMap[FilteredMCCommand];

         ////DO NOT REMOVE EVER !!!THIS IS A PATCH FOR WEIRD INCOMMING COMMANDS
        static uint32_t Input_Command = 500;
        if((MC_Commands.Elbow < 1001) && (MC_Commands.Elbow > 199))
        {
            Input_Command = MC_Commands.Elbow;
        }


        DesiredPosition = Input_Command;
        DesiredPosition = DesiredPosition < 250 ? 250 : DesiredPosition;
        DesiredPosition = DesiredPosition > 1000 ? 1000 : DesiredPosition;
        ElbowRightFeedback = 0;
        ElbowLeftFeedback = 0;
        ElbowRightCurrent = 0;
        ElbowLeftCurrent = 0;
        for (int i = 0; i < AVERAGE_SIZE; i++)
        {
            ElbowRightFeedback += analogRead(ELBOW_POT_RIGHT);
            ElbowLeftFeedback += analogRead(ELBOW_POT_LEFT);
            ElbowRightCurrent += analogRead(ELBOW_CURRENT_RIGHT);
            ElbowLeftCurrent += analogRead(ELBOW_CURRENT_LEFT);
        }
        ElbowRightFeedback /= AVERAGE_SIZE;
        ElbowLeftFeedback /= AVERAGE_SIZE;
        ElbowRightCurrent /= AVERAGE_SIZE;
        ElbowLeftCurrent /= AVERAGE_SIZE;

        SyncError = ELBOW_RIGHT_TO_LEFT(ElbowRightFeedback) - ElbowLeftFeedback;

        Feedback.Elbow_L = ElbowLeftFeedback;
        Feedback.Elbow_R = ElbowRightFeedback;

        // Sync Eblow Right (2) to Elbow Left (1)'s position
        if (abs(SyncError) > 15)
        {
            while (abs(ELBOW_RIGHT_TO_LEFT(ElbowRightFeedback) - ElbowLeftFeedback) > 3)
            {
                ElbowDirection = SyncError > 0 ? LOW : HIGH;
                PWM_Left = drv8870MotorControl(ElbowDirection, 0);
                PWM_Right = drv8870MotorControl(ElbowDirection, MinPWM*3);
                analogWrite(ELBOW_PWM_1_LEFT, PWM_Left.pwm1);
                analogWrite(ELBOW_PWM_2_LEFT, PWM_Left.pwm2);
                analogWrite(ELBOW_PWM_1_RIGHT, PWM_Right.pwm1);
                analogWrite(ELBOW_PWM_2_RIGHT, PWM_Right.pwm2);
                ElbowRightFeedback = 0;
                ElbowLeftFeedback = 0;
                ElbowRightCurrent = 0;
                ElbowLeftCurrent = 0;
                for (int i = 0; i < AVERAGE_SIZE; i++)
                {
                    ElbowRightFeedback += analogRead(ELBOW_POT_RIGHT);
                    ElbowLeftFeedback += analogRead(ELBOW_POT_LEFT);
                    ElbowRightCurrent += analogRead(ELBOW_CURRENT_RIGHT);
                    ElbowLeftCurrent += analogRead(ELBOW_CURRENT_LEFT);
                }
                ElbowRightFeedback /= AVERAGE_SIZE;
                ElbowLeftFeedback /= AVERAGE_SIZE;
                ElbowRightCurrent /= AVERAGE_SIZE;
                ElbowLeftCurrent /= AVERAGE_SIZE;


        // //Feedback////
        // static int count = 0;
        //     if(count > 10)
        //     {
        //          Serial1.print("Syncing Left: ");
        //         Serial1.print(ElbowLeftCurrent);
        //         Serial1.print(" Syncing Right: ");
        //         Serial1.print(ElbowRightCurrent);
        //         Serial1.print(" DesiredPosition: ");
        //         Serial1.print(DesiredPosition);
        //         Serial1.print("\n");
        //         count = 0;
        //     }
        //     count ++;
              
            }
            PWM_Right = drv8870MotorControl(ElbowDirection, 0);
            analogWrite(ELBOW_PWM_1_RIGHT, PWM_Right.pwm1);
            analogWrite(ELBOW_PWM_2_RIGHT, PWM_Right.pwm2);
        }

        Error = DesiredPosition - ElbowLeftFeedback;
        if (abs(Error) > Epsilon)
        {
            Integral = Integral + Error*dt;
            OutputPID = Kp*Error + Ki*Integral;
            if (OutputPID < 0) 
            {
                ElbowDirection = LOW;
                OutputPWM = -OutputPID;
            }
            else 
            {
                ElbowDirection = HIGH;
                OutputPWM = OutputPID;
            } 
            if (OutputPWM > MaxPWM)
            {
                OutputPWM = MaxPWM;
            }
            else if (OutputPWM < MinPWM)
            {
                OutputPWM = MinPWM;
            }
            PWM_Left = drv8870MotorControl(ElbowDirection, OutputPWM);
            PWM_Right = drv8870MotorControl(ElbowDirection, OutputPWM);
            analogWrite(ELBOW_PWM_1_LEFT, PWM_Left.pwm1);
            analogWrite(ELBOW_PWM_2_LEFT, PWM_Left.pwm2);
            analogWrite(ELBOW_PWM_1_RIGHT, PWM_Right.pwm1);
            analogWrite(ELBOW_PWM_2_RIGHT, PWM_Right.pwm2);
        }
        else
        {
            PWM_Left = drv8870MotorControl(ElbowDirection, 0);
            PWM_Right = drv8870MotorControl(ElbowDirection, 0);
            analogWrite(ELBOW_PWM_1_LEFT, PWM_Left.pwm1);
            analogWrite(ELBOW_PWM_2_LEFT, PWM_Left.pwm2);
            analogWrite(ELBOW_PWM_1_RIGHT, PWM_Right.pwm1);
            analogWrite(ELBOW_PWM_2_RIGHT, PWM_Right.pwm2);
            Integral = 0;            
        }
        // Serial1.print("Left: ");
        // Serial1.print(ElbowLeftCurrent);
        // Serial1.print(" Right: ");
        // Serial1.print(ElbowRightCurrent);
        // Serial1.print(" DesiredPosition: ");
        // Serial1.print(DesiredPosition);
        // Serial1.print("\n");
    }
}


#define WRIST_PITCH_OFFSET  -90


void vControlLoopWrist(void *pvParameters)
{
    //// Initalization ////
    const TickType_t xDelay = DELAY_MS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    BNO055 IMU(&Serial2);
    IMU.init();
    // Encoder_Init();

    MC_Commands.Wrist_Pitch = 180;
    pinMode(WRIST_PWM_1_LEFT, OUTPUT);
    pinMode(WRIST_PWM_2_LEFT, OUTPUT);
    pinMode(WRIST_PWM_1_RIGHT, OUTPUT);
    pinMode(WRIST_PWM_2_RIGHT, OUTPUT);
    analogWriteFrequency(WRIST_PWM_1_LEFT, 30000);
    analogWriteFrequency(WRIST_PWM_2_LEFT, 30000);
    analogWriteFrequency(WRIST_PWM_1_RIGHT, 30000);
    analogWriteFrequency(WRIST_PWM_2_RIGHT, 30000);
    

    //Wakes Up MPU6050
    // MPU_Initialize();
    // vTaskDelay(DELAY_MS(30));

    Euler IMU_Data;
    uint16_t Encoder_Data;
    double Pitch;
    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        
        if(IMU.getEuler(&IMU_Data))
        {
            Pitch = map(IMU_Data.Y/16, -180, 180, 0, 360);
            Feedback.Wrist_Pitch = SoftwareaAdjust(Pitch, 0, 360, WRIST_PITCH_OFFSET);
            WristControlSystem(&Feedback, &MC_Commands);
        }
        else
        {
            analogWrite(WRIST_PWM_1_LEFT,  0);
            analogWrite(WRIST_PWM_2_LEFT,  0);
            analogWrite(WRIST_PWM_1_RIGHT, 0);
            analogWrite(WRIST_PWM_2_RIGHT, 0);
        }
        
         

        //Control System
       
    }
}

void vControlLoopClaw(void *pvParameters)
{
    //// Initalization ////
    static double CurrentAvg = 0;
    const TickType_t xDelay = DELAY_MS(25);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    MC_Commands.Claw_Torque = 75;
    int32_t ClawPWM;
    uint32_t burstCounter = 0;
    uint32_t burstLimit = 20;
    uint32_t PWMDivider = 1;
    bool ClawDirection = LOW;
    uint32_t previousCommand = 0;

    int32_t inputVoltage = 25.6;
    int32_t outputVoltage = 12;
    motorControl_t PWM = drv8870MotorControl(ClawDirection, 0);
    int32_t MaxPWM = dutyCycleVoltageTransfer(inputVoltage, outputVoltage);
    int32_t Max_Enabled_PWM = MaxPWM;
    int32_t MinPWM = MaxPWM / 5;    // actuator should not go slower than 20% of max speed

    analogWriteFrequency(CLAW_PWM_1, 31000);
    analogWriteFrequency(CLAW_PWM_2, 31000);
    
    analogWrite(CLAW_PWM_1, PWM.pwm1);
    analogWrite(CLAW_PWM_2, PWM.pwm2);

    int Commanded_PWM = 0;
    //// Task Loop ////
    while (FOREVER)
    {
        //Absolute Delay
        vTaskDelayUntil(&xLastWakeTime, xDelay);
        
        if (previousCommand != MC_Commands.Claw)
        {
            burstCounter = 0;
            Commanded_PWM = MaxPWM;
            previousCommand = MC_Commands.Claw;
        }
        if(burstCounter < burstLimit)
        {
            burstCounter++;
        }
        else
        {
            Commanded_PWM = map(MC_Commands.Claw_Torque, 0, 100, 0, (double)Max_Enabled_PWM);
        }

        if (MC_Commands.Claw == 2)
        {
            ClawPWM = Commanded_PWM;
            ClawDirection = LOW;
        }
        else if (MC_Commands.Claw == 1)
        {
            ClawPWM = Commanded_PWM;
            ClawDirection = HIGH;
        }
        else // (MC_Commands.Claw == 0) 
        {
            ClawPWM = 0;
        }
        //Serial.println(ClawPWM);
        Current.Claw = analogRead(CLAW_CURRENT);
        PWM = drv8870MotorControl(ClawDirection, ClawPWM);
        analogWrite(CLAW_PWM_1, PWM.pwm1);
        analogWrite(CLAW_PWM_2, PWM.pwm2);
    }
}