#ifndef METHODS_H
#define METHODS_H

/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include <stdint.h>
#include <stdio.h>

//// User Libraries ////
#include "UserInterrupts.h"
#include "RTOS_Tasks.h"
#include "mpu9250.h"
/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define YAW_MIN -200
#define YAW_MAX 200
#define PITCH_MIN -45
#define PITCH_MAX 45
#define MOTOR_MAX_VOLTAGE 6

#define MOTOR_PWM_1 6
#define MOTOR_PWM_2 5
#define MOTOR_DIR_1 8
#define MOTOR_DIR_2 7
#define CAMERA_MUX 9
#define CURRENT_SENS_1 17
#define CURRENT_SENS_2 16


typedef enum
{
	SPEED = 1,
	POSITION = 2
} Motion_Mode_t;

typedef enum
{
    CAMERA_FRONT = 1,
    CAMERA_REAR = 2
} Camera_t;

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitionss                     //
/////////////////////////////////////////////////////////////////////////////


typedef struct
{
    double_3D_t local_Orientation;
    double_3D_t global_Orientation;
    uint32_t lidar_Reading;
    float yaw_Current;
    float pitch_Current;
} feedback_t;

typedef struct
{
    uint8_t motion_Mode;
    float yaw;
    float pitch;
} command_t;

/////////////////////////////////////////////////////////////////////////////
//                              Global Variables                           //
/////////////////////////////////////////////////////////////////////////////



//Pins

/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////
double_3D_t calculateOrientation(const double_3D_t & staticIMU, const double_3D_t & trackerIMU);

command_t constrainBoundsPosition(const command_t & command);

command_t constrainBoundsSpeed(const command_t & command, const double_3D_t & currentPos);

bool controlLoopSpeed(const command_t & speed);

bool controlLoopPosition(const command_t & position);

void sendMotorCommand(float yaw, float pitch);

#endif // METHODS_H
