#include "usb_serial.h"

usb_serial_class::usb_serial_class()
{

}

int usb_serial_class::available()
{
    bool Success = false;
    if(buffer.length() > 0)
    {
        Success = true;
    }

    return Success;
}

void usb_serial_class::InsertDummySerial(const char *C_String)
{
    for(unsigned int iterator = 0; iterator < strlen(C_String); iterator++)
    {
       buffer+=C_String[iterator];
    }
}


int usb_serial_class::read()
{
    int Return_Char;
    if(buffer.length() > 0)
    {
        Return_Char = buffer.at(0);
        buffer.erase(0,1);
    }
    return Return_Char;
}