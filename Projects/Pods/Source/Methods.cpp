#include "Methods.h"


/////////////////////////////////////////////////////////////////////////////
//                              Function Definitions                       //
/////////////////////////////////////////////////////////////////////////////

SdFat SD;

Sd_Card_Error_t initializeSdCard()
{
// only proceed with other card-related functions if ends with no errors - otherwise sends message to MC
	// return value goes to a variable in vMessageTask used to see whether other card-related functions should be called

	// SPI protocol
	/*
	 * Pin 4 (active low) is CS, 11 is MOSI, 12 is MISO, 13 is SCK
	 */

	if (SD.begin(CS)) 
	{
		return NO_ERROR;
	}
		return PARAMETER;

	/*
	set all pins to correct direction and name them
	unused pins set to outputs

	MOSI set 1(no message is being sent)

	place SD card into SPI mode:
		configure clock to frequency supported by slave (SD card) = 100 to 400 kHz1q

		MOSI and CS set 1
		toggle SCK 74 cycles or more

		CS set from 1 to 0
		if MISO is 1:
		send command CMD0: 01 6'b0 32'b0 1001010 1 (reset command, set to SPI mode if CS is low)
		MOSI set 1
		CS still set 0
		continuously toggle SCK and observe MISO for 0 bit that indicates a response (usually 8b, 40b for two commands)
		Response should be 00000001 to indicate no errors, in idle state

		 	MSB
		 	7: 0 bit
		 	6: parameter error
		 	5: address error
		 	4: erase sequence error
		 	3: CRC error
		 	2: illegal command
		 	1: erase reset
		 	0: in idle state
		 	LSB

		 	What to do for error handling? Send message to MC?
		MOSI set 1 (no message being sent), toggle SCK
		if response is not received within 16 cycles, report to MC and repeat

		Now in SPI mode

		CS set from 1 to 0
		send CMD8 to verify SD card interface operation condition
		01 001000 00000000 00000000 00000001 10101010 0000111 1
		(mandatory for SDHC/SDXC)
		send 48b command
		 	set MOSI to each bit, starting from MSB
		 	toggle SCK (0 to 1 to 0)
		MOSI set 1 (no message being sent), toggle 8 cycles

		if VCA in response is 0, cannot operate on supplied voltage - report to MC
		if check pattern not matched, inform MC and retry CMD8

		CS set to 1 to indicate transaction over

		CS set from 1 to 0
		CMD58 (READ_OCR)
		(not mandatory but recommended)
		If not valid command, not a SD card! Report to MC
		MOSI set 1 (no message being sent), toggle 8 cycles

		CS set to 1 to indicate transaction over

		// recommended to enable CRC verification with CMD59

		loop until idle bit in response is unset:
			R1 response with idle bit unset indicates initialization process is over. Can take hundreds of ms depending on card size, so take in consideration for determining timeout value.

			CS set from 1 to 0
			send ACMD41 to read OCR register and check working voltage range since card is confirmed SDC
			(only type of command other than reset accepted in current state)

			MSB
			39: 0 bit
			38: parameter error
			37: address error
			36: erase sequence error
			35: CRC error
			34: illegal command
			33: erase reset
			32: in idle state
			31-28: version
			27-12: reserved
			11-8: voltage
			7-0: check pattern
			LSB

			send 48b command = 0 1 (6b command number) (32b argument) (6b CRC) 1
			 	set MOSI to each bit, starting from MSB
			 	toggle SCK (0 to 1 to 0)
			MOSI set 1 (no message being sent), toggle 8 cycles

			if system supply voltage is out of range, card must be rejected
				Report to MC and block all FreeRTOS tasks other than idle
			(card initiates initialization process at this point)
			if not valid command, not a SD card! Report to MC

			CS set to 1 to indicate transaction over

		CS set from 1 to 0
		CMD58 to get card capacity info (CCS)
		should get CCS = 0 for SDC, CCS = 1 for SDHC/SDXC
		MOSI set 1 (no message being sent), toggle 8 cycles

		if card is SDHC/SDXC, reads/writes 512B per operation.

		CS set to 1 to indicate transaction over

		Setup complete: SD card now ready to accept generic read/write commands!
		*/
}

// read unit ID from SD card
int retrieveUnitId()
{
	// SPI protocol
	// unitId pre-written in the SD card. Simplifies identification of SD cards
	/*
	CS set from 1 to 0
	set block len (CMD16) to 1B: 01 010000 32'b1 7'b0 1
	MOSI set 1 (no message being sent), toggle 8 cycles
	receive response
	receive data error token or data block
	CS set to 1 to indicate transaction over

	read from file (data.txt?) the unit ID:
		CS set from 1 to 0
		single block read (CMD17): 
		MOSI set 1 (no message being sent), toggle 8 cycles
		receive response
		receive data error token or data block
		CS set to 1 to indicate transaction over

	CS set from 1 to 0
	set block len (CMD16) to 512B to make behavior same
	MOSI set 1 (no message being sent), toggle 8 cycles
	receive response
	receive data error token or data block
	CS set to 1 to indicate transaction over

	if (data error)
		report to MC and loop in FreeRTOS idle task until retrieved
		(will have to figure out identity by process of elimination)
	else
		report to MC that identity was found
		return unitId
		*/
	return 0;
}

// write message to SD card
int saveMessage(uint64_t value)
{
	// SPI protocol
	// for now, just save what is sent and assume data is compiled into chartable data after retrieval
	/*
	 * Pin 4 (active low) is CS, 11 is MOSI, 12 is MISO, 13 is SCK
	 */
	/*
	MOSI set 1(no message is being sent)

	from here on, only writing PODS messages
		data -> data.txt
		status & error -> log.txt

	CS set from 1 to 0

	single block write (CMD24)
	MOSI set 1 (no message being sent), toggle 8 cycles
	receive response
	send datablock
	MOSI set 1 (no message being sent), toggle 8 cycles
	receive data_response
	keep toggling until MISO goes high, indicating write finished

	CS set 1 to indicate transaction over

	recommended:
		CS set from 1 to 0

		send status to check for errors (CMD13)
		MOSI set 1 (no message being sent), toggle 8 cycles
		receive response
		send datablock
		MOSI set 1 (no message being sent), toggle 8 cycles
		receive response
		keep toggling until MISO goes high, indicating write finished

		CS set 1 to indicate transaction over

	report to MC if failed, otherwise success (indicate space left with return value?)
	*/
	return 0;
}










