#include "CommonFunctions.h"
#include <math.h> 
#include "stdbool.h"
#include "stdint.h"
#include <math.h>
#include "stdbool.h"
#include "stdint.h"
#include <stdlib.h>
#include "WProgram.h"

int16_t dutyCycleVoltageTransfer(double batV, double desiredV) {
 /*
 batV: battery voltage (input voltage)
 desiredV: desired voltage (output voltage)
 */
 uint16_t MAX_PWM = pow(2, analogWriteResVal()) - 1;
 double voltageRatio = (batV > desiredV) ? (desiredV / batV) : 1;
 uint16_t dutyCycle = MAX_PWM * voltageRatio; 
 return dutyCycle;
}

/*
 *  batV: battery voltage
 *  maxV: max motor voltage
 *  motorSpeed: motor speed from -1.0 to 1.0
 *  mode: drive, coast, or brake
 *  setting mode to brake is the same as setting speed to 0
 */
motorControl_t drv8870MotorControl(double batV, double maxV, double motorSpeed)
{
    motorControl_t motorOutput;
    uint16_t MAX_PWM = pow(2, analogWriteResVal()) - 1;
    double speedAbs = abs(motorSpeed);
    speedAbs = speedAbs > 1.0 ? 1.0 : speedAbs;
    double desiredV = speedAbs * maxV;
    int16_t motorPWM = dutyCycleVoltageTransfer(batV, desiredV);
    motorPWM = MAX_PWM - motorPWM; //Invert the duty cycle
    if(motorSpeed >= 0)
    {
        motorOutput.pwm1 = MAX_PWM;
        motorOutput.pwm2 = motorPWM;
    }
    else
    {
        motorOutput.pwm1 = motorPWM;
        motorOutput.pwm2 = MAX_PWM;
    }
    return motorOutput;
}

motorControl_t drv8870MotorControl(bool dir, uint16_t PWM)
{
    motorControl_t result;
    uint16_t MAX_PWM = pow(2, analogWriteResVal()) - 1;
    PWM = PWM > MAX_PWM? MAX_PWM : PWM;
    result.pwm1 = dir? MAX_PWM - PWM : MAX_PWM;
    result.pwm2 = dir? MAX_PWM : MAX_PWM - PWM;
    return result;
}


motorControl_t drv8870MotorControl(int Input, bool Pol = 1)
{
    bool dir = (Input > 0) ? Pol : !Pol;
    int PWM = abs(Input);

    motorControl_t result;
    uint16_t MAX_PWM = pow(2, analogWriteResVal()) - 1;
    PWM = PWM > MAX_PWM? MAX_PWM : PWM;
    result.pwm1 = dir? MAX_PWM - PWM : MAX_PWM;
    result.pwm2 = dir? MAX_PWM : MAX_PWM - PWM;
    return result;
}