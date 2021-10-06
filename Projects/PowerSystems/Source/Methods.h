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
#include "CommonFunctions.h"
#include "WProgram.h"

/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define MAX_MV_IN 			3300.0
#define MAX_ANALOG_VALUE 	4095.0
#define MV_OFFSET 			502		//will be different for other sensor models
#define MILLI_TO_BASE 		1000
#define MV_PER_AMP 			26.66	//will be different for other sensor models
#define MAX_MAH 			4000 	//4000 per battery
#define CRITICAL_BAT_TEMP 	140		//60C;	140F
#define APPROACH_CRIT_TEMP 	135
#define MAX_V_PER_CELL 		4.2
#define NUM_OF_CELL_PER_BAT 7
#define MAX_V_OF_BAT		29.4
#define MIN_V_PER_CELL		3.6
#define RATE_OF_DRAIN 		36000.0 //seconds in an hour / sample rate (in seconds) = 3600/0.1

//PIN FOR TEENSY'S LED
#define LED_PIN 			13

//RELAY PINS
#define BAT_RELAY1 			9
#define BAT_RELAY2 			10
#define BAT_RELAY3 			25
#define DRIVE_BACKUP_RELAY	23 //#define DRIVE_RELAY		23
#define STEER_RELAY 		22
#define ARM_RELAY 			21
#define DRIVE_FRONT_RELAY	20 //#define INTEL_RELAY 		20
#define DRIVE_BACK_RELAY	32 //#define MAST_RELAY 		32

//VOLTAGE MEASUREMENT PINS
#define OPEN_CIR_VOL1 		26
#define OPEN_CIR_VOL2 		27
#define OPEN_CIR_VOL3 		28
#define REAL_TIME_VOL 		29
#define REAL_TIME_CTRL		24

//CURRENT MEASUREMENT PINS
#define DRIVE_BACKUP_CURRENT	16 //#define DRIVE_CURRENT 		16
#define STEER_CURRENT 		15
#define ARM_CURRENT 		14
#define DRIVE_FRONT_CURRENT	31 //#define INTEL_CURRENT 		31
#define DRIVE_BACK_CURRENT	30 //#define MAST_CURRENT 		30

//TEMPERATURE SENSOR ADDRESSES
#define TEMP_SENSOR1_ADDR 	0x40
#define TEMP_SENSOR2_ADDR 	0x41
#define TEMP_SENSOR3_ADDR 	0x44
#define TEMP_READ_REG		0x01
#define TEMP_CONFIG_REG		0x02
#define TEMP_CONFIG_VALUE	0x8100

//TEMPERATURE SENSOR PINS
#define TEMP_DATAR1 		6
#define TEMP_DATAR2 		7
#define TEMP_DATAR3 		8
#define TEMP_SDA 			18
#define TEMP_SCL 			19

#define BYTES_READ			2

//BLUETOOTH MODULE PINS
#define BLUETOOTH_TX 		0
#define BLUETOOTH_RX 		1
#define BLUETOOTH_ST 		2

//MISCELLANEOUS DEFINES
#define DEGREE				248 	//ASCII value for degree symbol
#define DELAY_TIME			100
#define INPUT_RESOLUTION	12
#define IN_MIN 				128
#define IN_MAX				3647
#define OUT_MIN				22
#define OUT_MAX				29.4
#define REAL_TIME_RELATION 	2.6277547358
#define REAL_TIME_OFFSET 	21.6339335583
#define PWM_FREQUENCY		22000 
#define INPUT_TO_FAHRENHEIT 0.0140625
#define FAHRENHEIT_OFFSET 	32.0
#define CUTOFF_VOLTAGE	 	22.05
#define ZERO				0
#define ONE 				1
#define FIVE				5
#define TEN 				10
#define TWELVE 				12

//ERROR CODES
#define NO_ERROR 			0
#define DRIVE_BACKUP_CURRENT_TRIP 	1
#define STEER_CURRENT_TRIP 	2
#define ARM_CURRENT_TRIP 	3
#define DRIVE_FRONT_RELAY_TRIP 	4
#define DRIVE_BACK_RELAY_TRIP 	5
#define BAT1_TEMP_WARNING 	6
#define BAT2_TEMP_WARNING 	7
#define BAT3_TEMP_WARNING 	8
#define BAT1_TEMP_CRITICAL 	9
#define BAT2_TEMP_CRITICAL 	10
#define BAT3_TEMP_CRITICAL 	11

//Max Currents for each System (const uint8_t for use with telemetry)
const uint8_t MAX_DRIVE_BACKUP	= 51; 		//actual: 100
const uint8_t MAX_STEER 		= 8;		//actual: 7
const uint8_t MAX_ARM 			= 21;		//actual: 20?
const uint8_t MAX_DRIVE_FRONT 	= 60;// const uint8_t MAX_INTELLIGENCE 	= 3;		//actual: 2
const uint8_t MAX_DRIVE_BACK 	= 80;// const uint8_t MAX_MASTTRACKER 	= 9;		//actual: 8

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitions                      //
/////////////////////////////////////////////////////////////////////////////

// enum {
// 	NO_ERROR, 			
// 	DRIVE_CURRENT_TRIP,
// 	STEER_CURRENT_TRIP,
// 	ARM_CURRENT_TRIP,
// 	INTEL_CURRENT_TRIP,
// 	MAST_CURRENT_TRIP,
// 	BAT1_TEMP_WARNING,
// 	BAT2_TEMP_WARNING,
// 	BAT3_TEMP_WARNING,
// 	BAT1_TEMP_CRITICAL,
// 	BAT2_TEMP_CRITICAL,
// 	BAT3_TEMP_CRITICAL
// };


typedef struct 
{
	uint32_t temp1;
	uint32_t temp2;
	uint32_t temp3;
	double currentDriveBackup; //double currentDrive; //will not be used
	double currentSteer;
	double currentArm;
	double currentDriveFront;// double currentIntel;
	double currentDriveBack;// double currentMast;
	double realTimeVoltage;
	double mAhRemaining;
	double previousVoltages[FIVE];
	uint32_t errorCode;
} feedback_t;

//holds current status of module current levels
typedef struct
{
	uint32_t bat1;		//0=open, 1=closed
	uint32_t bat2;		//0=open, 1=closed
	uint32_t bat3;		//0=open, 1=closed
	uint32_t driveBackup; 	//0=open, 1=closed
	uint32_t steer; 	//0=open, 1=closed
	uint32_t arm;		//0=open, 1=closed
	uint32_t driveF;// uint32_t intel;		//0=open, 1=closed
	uint32_t driveB;// uint32_t mast;		//0=open, 1=closed
	uint32_t allPower;	//0=open all
} flags_t;

//holds instructions from mission control
typedef struct
{
	uint32_t batRelay1;
	uint32_t batRelay2;
	uint32_t batRelay3;
	uint32_t driveBackupRelay;
	uint32_t steerRelay;
	uint32_t armRelay;
	uint32_t driveFrontRelay;// uint32_t intelRelay;
	uint32_t driveBackRelay;// uint32_t mastRelay;
	uint32_t allPower;
} commands_t;

/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////

//read analog values from current sensors
void currentRead(feedback_t * feedback);

//math function for current reading
double currentConvert(uint8_t pinNumber);

//for approximate reamining battery life
void coulombCount(feedback_t * feedback);

//check current readings against set limits
void currentCheck(feedback_t * feedback, flags_t * flags, commands_t * commands); 

//configure temperature sensors
void tempConfig(uint8_t addr);

//setup for Arduino Wire library
void WireSetup();

//read values from temperature sensors
void tempRead(feedback_t * feedback);

//math for temperature sensor data
uint32_t tempReadTransmit(uint8_t addr);

//compare temperature readings again critical values
void tempCheck(feedback_t * feedback);

//find initial state of charge for battery
void openCircuitVoltage(feedback_t * feedback);

//math function for state of charge
double OCV_Math(uint8_t pin);

//discharge function of batteries
double dischargeFxn(double ocv);

//close all relays and initialize all flags
void closeModuleRelays(feedback_t * feedback, flags_t * flags, commands_t * commands);

//update PWM duty cycles to account for steady decrease in battery voltage
void updatePWM(feedback_t * feedback, flags_t * flags);

//update real time voltage feedback value to account for steady decrease in battery voltage
void updateRealTimeVoltage(feedback_t * feedback);

//respond to commands from mission control
void commandResponse(feedback_t * feedback, flags_t * flags, commands_t * commands, SemaphoreHandle_t * xSemaphore);

#endif // METHODS_H