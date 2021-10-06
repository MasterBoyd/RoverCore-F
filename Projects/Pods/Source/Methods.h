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
#include "SdFat.h"

/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

/* SPI protocol */
#define CS 4 /* active low */
#define MOSI 11
#define MISO 12
#define SCK 13

typedef enum
{
	NO_ERROR,
	PARAMETER,
	ADDRESS,
	ERASE_SEQUENCE,
	CRC,
	ILLEGAL_COMMAND
} Sd_Card_Error_t;

/////////////////////////////////////////////////////////////////////////////
//                              Structure Definitions                      //
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//                              Function Declarations                      //
/////////////////////////////////////////////////////////////////////////////

// confirm operation of SD card and set to SPI mode
Sd_Card_Error_t initializeSdCard();

// read unit ID from SD card
int retrieveUnitId();

// write message to SD card
int saveMessage(uint64_t value);


#endif // METHODS_H