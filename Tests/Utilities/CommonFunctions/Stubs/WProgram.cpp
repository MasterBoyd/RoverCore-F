#ifndef WProgram_h
#define WProgram_h

#include "stdbool.h"
#include "stdint.h"
#include "WProgram.h"

static uint16_t Register_Value = 12;

uint16_t analogWriteResVal()
{
	return Register_Value;
}

void MimicAnalogPrecision(uint16_t Mimic_Value)
{
	Register_Value = Mimic_Value;
}


#endif // WProgram_h
