#include "AS5048A-Magnetic-Encoder.h"
#include <SPI.h> 

void Encoder_Init()
{
	SPI.begin();
	SPI.setSCK(14);
	pinMode(24, OUTPUT);
	pinMode(25, OUTPUT);

} 

uint8_t spiCalcEvenParity(word value){
	uint8_t cnt = 0;
	uint8_t i;

	for (i = 0; i < 16; i++)
	{
		if (value & 0x1)
		{
			cnt++;
		}
		value >>= 1;
	}
	return cnt & 0x1;
}

void Chip_Enable(int Pin)
{
	if(Pin == SHOULDER_ENCODER_CS_INTERNAL || Pin == WRIST_ENCODER_CS_INTERNAL)
	{
		digitalWrite(Pin, LOW);
	}
	else
	{
		Serial.println("Incorrect Chip Select on Enable!");
	}
}
void Chip_Disable(int Pin)
{
	if(Pin == SHOULDER_ENCODER_CS_INTERNAL || Pin == WRIST_ENCODER_CS_INTERNAL)
	{
		digitalWrite(Pin, HIGH);
	}
	else
	{
		Serial.println("Incorrect Chip Select on Disable!");
	}
}

uint16_t Encoder_Read(uint16_t Address, int Pin)
{
	uint16_t command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | Address;

	//Add a parity bit on the the MSB
	command |= ((uint16_t)spiCalcEvenParity(command)<<15);

	//Split the command into two bytes
	uint8_t left_byte = ( command >> 8 ) & 0xFF;
	uint8_t right_byte = command & 0xFF;

	SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1)); 
	
	Chip_Enable(Pin);
	// digitalWrite(24, LOW);
 	SPI.transfer(left_byte);
 	SPI.transfer(right_byte); 
 	// digitalWrite(24, HIGH);
 	Chip_Disable(Pin);
 	SPI.endTransaction();


 	SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1)); 
 	Chip_Enable(Pin);
 	// digitalWrite(24, LOW);
 	left_byte = SPI.transfer(0x00);
 	right_byte = SPI.transfer(0x00);
 	Chip_Disable(Pin); 
 	// digitalWrite(24, HIGH);
 	
 	SPI.endTransaction();

 	//Check if the error bit is set
	if (left_byte & 0x40) {
		//Serial.println("Setting Error bit");
	}	

 	// result1 &= 0b00111111;
 	// result1 = result1 << 8;
 	// *Data = (result1 | result2);

 	//Return the data, stripping the parity and error bits
	return (( ( left_byte & 0xFF ) << 8 ) | ( right_byte & 0xFF )) & ~0xC000;
}

uint16_t Encoder_Get_Data(uint16_t *Data, int Pin)
{
	uint16_t Mag_Field = Encoder_Read(0x3FFE, Pin);
	bool Return_Status = false;
 	//Serial.print(" Magnetic Field Issue");
	if(Mag_Field > 1500 && Mag_Field < 16000)
	{
		// Serial.print("MAG: ");
		// Serial.println(Mag_Field);
		Return_Status = true;
		*Data = Encoder_Read(0x3FFF, Pin);
		//Serial.println(*Data);

	}
	else
	{
		Serial.print(" Magnetic Field Issue");
		Serial.println(Mag_Field);
	}

 	return Return_Status;
}

uint16_t Encoder_Get_Magnetude(uint16_t *Data)
{
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1)); 
	digitalWrite(24, LOW);
 	SPI.transfer(0x3f);
 	SPI.transfer(0xfd);
 	digitalWrite(24, HIGH);
 	
 	digitalWrite(24, LOW);
 	uint16_t result1 = SPI.transfer(0x3f);
 	uint16_t result2 = SPI.transfer(0xfd);
 	digitalWrite(24, HIGH);
 	SPI.endTransaction();

 	//result1 &= 0b00111111;
 	//result1 = result1 << 8;
 	//*Data = (result1 | result2);
 	*Data = result1;
 	return true;
}

double SoftwareaAdjust(double Input, double Min, double Max, double Offset)
{
	double Output = Input + Offset;
	if(Output > Max)
	{
		Output = Output - Max;
	}
	else if(Output < Min)
	{
		Output = Output + Max;
	}
	return Output;
} 

// 0x3FFE


// 12345678 | 910111213141516
// 01000000 | 00 0 0 0 0 0 0