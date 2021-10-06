#ifndef WPROGRAM_H
#define WPROGRAM_H

//#include "Stream.h"
#include "SerialController.h"

#define HIGH	1
#define LOW 	0
#define OUTPUT 	1
#define INPUT 	0

void digitalWrite(int pin, int Value);

void pinMode(int pin, int Value);

class HardwareSerial : public SerialController
{

};

extern HardwareSerial Serial;
#endif // WPROGRAM.H