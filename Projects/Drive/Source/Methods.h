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

typedef enum
{
	DRIVE=1,
	SWERVE,
	TURN_IN_PLACE,
	TANK
} Drive_Mode_t;

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitionss                     //
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
	// Fans and Temperature
	uint16_t temp[4];
	// Propulsion
	uint64_t tacho[4];
	uint16_t current[4];
	// Trajectory
	uint16_t angle[4];
	// Calculated values
	float angular_velocity[4];
	float swervo_angle[4];
} feedback_t;

typedef struct
{
	uint8_t speed;
	uint16_t angle;
} reference_t;

typedef struct
{
	uint8_t speed[4];
	uint16_t angle[4];
} command_t;

typedef union
{
	unsigned char bitfield;
	struct {
        unsigned tacho:1;
        unsigned flag1:1;
        unsigned flag2:1;
        unsigned flag3:1;
        unsigned flag4:1;
        unsigned flag5:1;
        unsigned flag6:1;
        unsigned flag7:1;
    };
} flags_t;

/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////
void getTemperatures(feedback_t * feedback);

void controlFans(feedback_t * feedback);

void TAPfeedbackCapture(feedback_t * feedback);

// Handles transitions between modes and sets trajectory and propulsion commands accordingly
void ModeTransitionControlSequencer(
	reference_t * reference,
	feedback_t * feedback,
	command_t * commands
);

// Controls Rover Trajectory
void TrajectoryControlSystem(
	feedback_t * feedback,
	command_t * commands
);

// Controls Rover Propulsion
void PropulsionControlSystem(
	feedback_t * feedback,
	command_t * commands
);

// Check Fault Flags
void checkAndActionOnFaults(flags_t * flags);

#endif // METHODS_H