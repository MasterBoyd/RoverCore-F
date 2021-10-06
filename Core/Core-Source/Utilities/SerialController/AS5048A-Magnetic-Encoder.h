#include "WProgram.h"

#ifndef AS5048A_MAGNETIC_ENCODER_H
#define AS5048A_MAGNETIC_ENCODER_H

#define SHOULDER_ENCODER_CS_INTERNAL	 24 //Encoder 1 Select Shoulder
#define WRIST_ENCODER_CS_INTERNAL	 25 //Encoder 2 Select Wrist

void Encoder_Init();
uint16_t Encoder_Get_Magnetude(uint16_t *Data);

uint8_t spiCalcEvenParity(word value);
uint16_t Encoder_Get_Data(uint16_t *Data, int Pin);
uint16_t Encoder_Read(uint16_t Address, int pin);
void Chip_Enable(int Pin);
void Chip_Disable(int Pin);
double SoftwareaAdjust(double Input, double Min, double Max, double Offset);

#endif // AS5048A-MAGNETIC-ENCODER_Hs