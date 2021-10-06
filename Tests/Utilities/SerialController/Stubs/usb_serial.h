#ifndef USBserial_h_
#define USBserial_h_

#define BUFFERSIZE 300

#include <stdio.h>
#include <string>
#include "Print.h"
#include "SerialController.h"


class usb_serial_class : public SerialController
{
public:
    usb_serial_class();
    int available();
    void InsertDummySerial(const char *C_String);
    int read();

private:
    std::string buffer;
};

#endif // USBserial_h_