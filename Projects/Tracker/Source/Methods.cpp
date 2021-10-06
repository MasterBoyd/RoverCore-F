#include "Methods.h"

/////////////////////////////////////////////////////////////////////////////
//                              Function Definitions                       //
/////////////////////////////////////////////////////////////////////////////


double_3D_t imu_A_Orientation;
double_3D_t imu_B_Orientation;
//Feedback
feedback_t feedback;
//Commands
command_t motion_Command = {SPEED, 0.0, 0.0};
uint8_t active_Camera = CAMERA_FRONT;
float battery_Voltage = 30.0;

double_3D_t calculateOrientation(const double_3D_t & staticIMU, const double_3D_t & trackerIMU)
{
    static double_3D_t prev_Orientation = {0,0,0};

    double_3D_t new_Orientation = trackerIMU - staticIMU;

    if(prev_Orientation.Z <= -90 && new_Orientation.Z >= 90)
    {
        new_Orientation.Z += -180;
    }
    else if(prev_Orientation.Z >= 90 && new_Orientation.Z <= -90)
    {
        new_Orientation.Z += 180;
    }

    prev_Orientation = new_Orientation;

    return new_Orientation;
}

command_t constrainBoundsPosition(const command_t & command)
{
    command_t new_Command = command;

    if(new_Command.yaw >= YAW_MAX)
    {
        new_Command.yaw = YAW_MAX;
    }
    else if(new_Command.yaw <= YAW_MIN)
    {
        new_Command.yaw = YAW_MIN;
    }

    if(new_Command.pitch >= PITCH_MAX)
    {
        new_Command.pitch = PITCH_MAX;
    }
    else if(new_Command.pitch <= PITCH_MIN)
    {
        new_Command.pitch = PITCH_MIN;
    }

    return new_Command;
}

command_t constrainBoundsSpeed(const command_t & command, const double_3D_t & currentPos)
{
    command_t new_Command = command;
    if((new_Command.yaw > 0 && currentPos.Z >= YAW_MAX) || (new_Command.yaw < 0 && currentPos.Z <= YAW_MIN))
    {
           new_Command.yaw = 0;
    }

    if((new_Command.pitch < 0 && currentPos.X >= PITCH_MAX) || (new_Command.pitch > 0 && currentPos.X <= PITCH_MIN))
    {
           new_Command.pitch = 0;
    }

    return new_Command;
}

bool controlLoopSpeed(const command_t & speed)
{
    command_t newSpeed = constrainBoundsSpeed(speed, feedback.local_Orientation);
    sendMotorCommand(newSpeed.yaw, newSpeed.pitch);
    return true;
}

bool controlLoopPosition(const command_t & position)
{
    return true; //Return true when finished
}

void sendMotorCommand(float yaw, float pitch)
{
    uint8_t yaw_PWM = abs(yaw) * (MOTOR_MAX_VOLTAGE / battery_Voltage) * 255;
    uint8_t pitch_PWM = abs(pitch) * (MOTOR_MAX_VOLTAGE / battery_Voltage) * 255;
    digitalWrite(MOTOR_DIR_1,(yaw >= 0 ? HIGH : LOW));
    analogWrite(MOTOR_PWM_1, yaw_PWM);
    digitalWrite(MOTOR_DIR_2,(pitch >= 0 ? HIGH : LOW));
    analogWrite(MOTOR_PWM_2, pitch_PWM);

}









