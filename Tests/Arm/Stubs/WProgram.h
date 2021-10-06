#ifndef WPROGRAM_H
#define WPROGRAM_H

//#include "Stream.h"
#include "SerialController.h"

#define HIGH	1
#define LOW 	0
#define OUTPUT 	1
#define INPUT 	0

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s
#define PRIORITY(p) 0 + p
#define ARR_SIZEOF(x)   (sizeof((x)) / sizeof((x[0])))
#define FOREVER 1

typedef enum
{
    PRIORITY_CRITICAL   = PRIORITY(3),
    PRIORITY_HIGH       = PRIORITY(2),
    PRIORITY_MEDIUM     = PRIORITY(1),
    PRIORITY_LOW        = PRIORITY(0)
} RTOS_Task_Priorities;

void digitalWrite(int pin, int Value);

void pinMode(int pin, int Value);

uint32_t analogWriteResVal();

uint32_t analogWrite(uint32_t, uint32_t);


uint32_t pulseIn(uint32_t, bool);

class HardwareSerial : public SerialController
{

};

extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
#endif // WPROGRAM.H