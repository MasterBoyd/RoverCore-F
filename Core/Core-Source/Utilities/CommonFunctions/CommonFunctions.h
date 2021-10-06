#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <math.h> 
#include "stdbool.h"
#include "stdint.h"
#include "WProgram.h"

int16_t dutyCycleVoltageTransfer(double, double);
typedef struct
{
    uint16_t pwm1;
    uint16_t pwm2;
} motorControl_t;

// Returns pwm values for IN1 and IN2 for drv8870 motor driver
motorControl_t drv8870MotorControl(double batV, double maxV, double motorSpeed);

// Returns pwm values for IN1 and IN2 for drv8870 motor driver (using dir and PWM)
motorControl_t drv8870MotorControl(bool dir, uint16_t PWM);

motorControl_t drv8870MotorControl(int Input, bool Pol);

int16_t dutyCycleVoltageTransfer(double batV, double desiredV);

#endif /* COMMON_FUNCTION_H */