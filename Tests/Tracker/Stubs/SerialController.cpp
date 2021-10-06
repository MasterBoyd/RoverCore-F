#include "stdio.h"
#include "SerialController.h"

// #define FALSE 0
// #define TRUE !(FALSE)

SerialController::SerialController()
{
}

////////////////////////////////////////////////////////////////////////
//Send
////////////////////////////////////////////////////////////////////////

bool SerialController::SetToSend(uint8_t key, uint32_t *var)
{
    return false;
}

bool SerialController::SetToSend(uint8_t key, float *var)
{
    return false;
}

void SerialController::SerialSendAll()
{
}

bool SerialController::CheckIfNew(uint8_t key)
{
  
    return false;
}

void SerialController::SerialSend(uint8_t key)
{
}

////////////////////////////////////////////////////////////////////////
//Receive
////////////////////////////////////////////////////////////////////////

bool SerialController::SetToReceive(uint8_t key, uint32_t *var)
{
    return false;
}

bool SerialController::SetToReceive(uint8_t key, float *var)
{
    return false;
}

bool SerialController::DecodeAndApply(const char *Message)
{
    return false;
}
void SerialController::Append(char* C_String, char Character)
{
}

bool SerialController::CollectIncomming()
{
    return false;
}




