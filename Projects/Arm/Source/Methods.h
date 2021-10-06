#ifndef METHODS_H
#define METHODS_H

/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include <stdint.h>
#include <stdio.h>
#include "WProgram.h"

//// User Libraries ////
// #include "UserInterrupts.h"
#include "RTOS_Tasks.h"
#include "BNO055-Serial.h"
#include "AS5048A-Magnetic-Encoder.h"


/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
	BLUETOOTH_SERIAL_RX 	= 0,  //Bluetooth Module Serial RX Pin.
	BLUETOOTH_SERIAL_TX 	= 1,  //Bluetooth Module Serial TX Pin.
	ROTUNDA_SERVO 			= 2,  //Rotunda Servo PWM position control Pin.
	SHOULDER_PWM 			= 3,  //Shoulder Motor PWM Speed control pin.
	ELBOW_PWM_1_LEFT		= 4,  //Elbow (Left) Linear Actuator 1 H1 (PWM)
	ELBOW_PWM_2_LEFT		= 5,  //Elbow (Left) Linear Actuator 1 H2 (PWM)
	ELBOW_PWM_1_RIGHT		= 6,  //Elbow (Right) Linear Actuator 2 H1 (PWM)
	ELBOW_PWM_2_RIGHT		= 7,  //Elbow (Right) Linear Actuator 2 H2 (PWM)
	WRIST_PWM_1_LEFT 		= 8,  //Wrist Motor 1 H1 (PWM)
	IMU_RX					= 9,  //IMU Serial Rx (UART)
	IMU_TX					= 10, //IMU Serial Tx (UART)
	ENCODER_MOSI			= 11, //Encoder MOSI
	ENCODER_MISO			= 12, //Encoder MISO
	LED_DO_NOT_USE 			= 13, //On-Board LED Pin
	ENCODER_SCLK	 		= 14, //Encoder Serial Clock
	ELBOW_POT_RIGHT 		= 15, //Elbow POT (Right) ADC
	WRIST_ENCODER 			= 16, //Wrist Encoder
	WRIST_CURRENT_LEFT		= 17, //Wrist Current (Left)
	WRIST_CURRENT_RIGHT		= 18, //Wrist Current (Right)
	ROTUNDA_FEEDBACK		= 19, //Rotunda Feedback
	WRIST_PWM_2_LEFT 		= 20, //Wrist Motor 1 H2 (PWM)
	ROTUNDA_CAMERA_PWM 		= 21, //Rotunda Camera PWM
	SHOULDER_DIR 			= 22, //Shoulder Direction
	TBD_1 					= 23, //Unassigned
	SHOULDER_ENCODER_CS		= 24, //Encoder 1 Select Shoulder
	WRIST_ENCODER_CS		= 25, //Encoder 2 Select Wrist
	BLUETOOTH_STATE 		= 26, //Bluetooth State Pin
	CAMERA_MUX_1 			= 27, //Camera MUX 1
	CAMERA_MUX_2 			= 28, //Camera MUX 2
	WRIST_PWM_1_RIGHT 		= 29, //Wrist Motor 2 H1 (PWM)
	WRIST_PWM_2_RIGHT 		= 30, //Wrist Motor 2 H2 (PWM)
	SHOULDER_CURRENT 		= 31, //Shoulder Current Sensor
	SHOULDER_ENCODER 		= 32, //Shoulder Encoder
	ELBOW_POT_LEFT		 	= 33,  //Elbow (Left) Feedback 
	CLAW_CURRENT 			= 34,  //Claw Current Sensor
	CLAW_PWM_2				= 35,  //Claw Motor H2 (PWM)
	CLAW_PWM_1				= 36,  //Claw Motor H1 (PWM)
	I2C_SCL					= 37,  //I2C Serial Clock
	I2C_SDA					= 38,  //I2C Serial Data
	ROTUNDA_CURRENT			= 39,  //Rotunda Current Sensor
	// From pins_arduino.h
	// #define PIN_A21 (66)
	// #define PIN_A22 (67)
	ELBOW_CURRENT_LEFT		= 67,  //Elbow Current Sensor 1 (ADC)
	ELBOW_CURRENT_RIGHT		= 66   //Elbow Current Sensor 2 (ADC)
} Pins_t;


typedef enum 
{
	CAMERA_1,
	CAMERA_2,
	CAMERA_3
}Camera_t;

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitions                      //
/////////////////////////////////////////////////////////////////////////////

// Structure that will hold incoming commands from Mission Control.
typedef struct 
{
	uint32_t Rotunda 	 = 1300;
	uint32_t Rotunda_Camera; 
	uint32_t Mux = 0;
	uint32_t Shoulder    = 270;
	uint32_t Elbow;
	uint32_t Wrist_Pitch = 180;
	uint32_t Wrist_Roll;
	uint32_t Claw;
	int32_t  Claw_Torque;
	uint32_t Camera_Select;
} Commands_t;

//Structure that will hold Feedback from ADC's and IMU.
typedef struct
{
	uint32_t Rotunda;
	int32_t Shoulder;
	uint32_t Elbow_L;
	uint32_t Elbow_R;
	uint32_t Wrist_Pitch;
	uint32_t Wrist_Roll;
	uint32_t Teensy_Temp;
} Feedback_t;

//Structure that will hold current feedback.
typedef struct
{
	uint32_t Rotunda;
	uint32_t Shoulder;
	uint32_t Elbow_L;
	uint32_t Elbow_R;
	uint32_t Wrist_L;
	uint32_t Wrist_R;
	uint32_t Claw;
} Current_t;

/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////

////Useful but not necessary features////
void GetTeensyTemp(Feedback_t * Feedback);

////Common Features////
void Current_Clamp(Current_t *Current, uint32_t *PWM_Pin);

////Control Systems////
void RotundaControlSystem(Feedback_t * Feedback, Commands_t *Command);
void ShoulderControlSystemBANGBANG(Commands_t *Command, Feedback_t * Feedback);

uint16_t GetPWM(uint16_t Val);
double ClipLimits(double Input, double Min, double Max);
void ShoulderControlSystem(uint32_t, Feedback_t * Feedback);
void ElbowControlSystem(Feedback_t *Feedback, Commands_t *Command);
void WristControlSystem(Feedback_t *Feedback, Commands_t *Command);
void ClawControlSystem(Feedback_t *Feedback, Commands_t *Command);
void MPU_Initialize();
double getAccel();

#endif // METHODS_H