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

/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define EXP 80                                                                                                                                                                                             
#define NUM_POTENTS 6
#define NUM_LEDS 8
#define MAX_ANALOG 1023
#define MAX_CURRENT 1023
#define MAX_PWM 255
#define DATA_PIN 0
#define CLOCK_PIN 1

#define BATTERY_CHARGE 23
#define TRUE 1

#define OPEN_CLAW 22
#define CLOSE_CLAW 21
#define POSITION_ONE 10
#define POSITION_TWO 12
#define POSITION_THREE 7

#define WRIST_LEFT 8      //7,8,10,11,12,21,22
#define WRIST_RIGHT 11

#define BASE_LOW  -0.61
#define BASE_HIGH 0.59

#define SHOULDER_LOW -0.366
#define SHOULDER_HIGH  0.85

#define ELBOW_LOW -1
#define ELBOW_HIGH -0.42

#define PITCH_LOW -0.925                                                                                                                                                                                                                                                                                                                                                                                                                                    // -0.929899
#define PITCH_HIGH 1          // 1

#define ROTATION_LOW -1
#define ROTATION_HIGH 1

#define TORQUE_LOW -1
#define TORQUE_HIGH 1

enum Command_t
{
  BASE = 0,
  SHOULDER = 1,
  ELBOW = 2,
  WRIST_PITCH = 3,
  ROTUNDA_CAM = 4,
  CLAW_TORQUE = 5
};

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitionss                     //
/////////////////////////////////////////////////////////////////////////////

typedef struct {
  uint16_t angle;
  double joy;
  uint16_t raw;
  uint16_t smooth;
  uint8_t pin;
  uint16_t PWM;
  uint8_t mPin;
  int32_t feedback;
} Command_S;

/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////

void initialize();

int EMA(uint16_t measurement, uint16_t prev, uint8_t alpha);

void joystickInput(Command_S A[]);

void currentIndicator(Command_S A[]); // repurposed to indicate raw base rotation

void feedbackMotor(Command_S A[]);

double boundaries(double angle, double low, double high);

double JoyMap(double x, double in_min, double in_max, double out_min, double out_max);

#endif // METHODS_H