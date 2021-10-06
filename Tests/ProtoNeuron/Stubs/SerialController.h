#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include <stdio.h>
#include "stdint.h"
#include <stdbool.h>
#include <string.h>
#include "Stream.h"
#include <math.h>

#define MAX_STORAGE 256 // size of uint8_t
#define BUFFER_SIZE 100  //Size needed to print @uint8_t,uint32_t/n
#define VAARIABLES_IN_MESSAGE 2



class SerialController : public Stream
{
public:
    SerialController();
    //Functions for user send
    bool SetToSend(uint8_t key, uint32_t *var);
    bool SetToSend(uint8_t key, float *var);

    //Functions for user Receive
    bool SetToReceive(uint8_t key, uint32_t *var);
    bool SetToReceive(uint8_t key, float *var);

    //Functions for serial Task send
    bool CheckIfNew(uint8_t key);
    void SerialSendAll();
    void SerialSend(uint8_t key);

    //Functions for serial Task Receive
    bool DecodeAndApply(const char *Message);
    bool CollectIncomming();
    void Append(char* C_String, char Character);
    virtual int available(){ printf("Printing wrong available!!!!\n");return 0;};
    virtual int read() {return 0;};

private:
    
};




#endif /* SERIAL_CONTROLLER_H */