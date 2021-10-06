#include "BNO055-Serial.h"
#include <math.h>
#include "stdint.h"
#include "stdbool.h"
#include "FreeRTOS_ARM.h"

extern "C" void delay(uint32_t); //arduino delay
extern SemaphoreHandle_t xI2CMutex;


BNO055::BNO055(HardwareSerial *Serial_Input) 
{
    _Serial = Serial_Input;
    // if(address == BNO055_ADDRESS_A)
    // {
    //     wire = &Wire;
    // }
    // else
    // {
    //     wire = &Wire1;
    // }
}


void BNO055::recieveFlush()
{
   while(_Serial -> available())
    {
        Serial.print("Flushing Input: ");
        Serial.println(_Serial -> read()); 
    } 
}

void BNO055::ErrorReadDecode(uint8_t Error)
{
    switch(Error)
    {
        case(0x02): Serial.println("READ: READ_FAIL"); break;
        case(0x04): Serial.println("READ: REGMAP_INVALID_ADDRESS"); break;
        case(0x05): Serial.println("READ: REGMAP_WRITE_DISABLED"); break;
        case(0x06): Serial.println("READ: WRONG_START_BYTE"); break;
        case(0x07): Serial.println("READ: BUS_OVER_RUN_ERROR"); break;
        case(0X08): Serial.println("READ: MAX_LENGTH_ERROR"); break;
        case(0x09): Serial.println("READ: MIN_LENGTH_ERROR"); break;
        case(0x0A): Serial.println("READ: RECEIVE_CHARACTER_TIMEOUT"); break;
        default: Serial.println("ErrorReadDecode ERROR"); break;
    }
}
void BNO055::ErrorWriteDecode(uint8_t Error)
{
    switch(Error)
    {
        case(0x03): Serial.println("WRITE: WRITE_FAIL"); break;
        case(0x04): Serial.println("WRITE: REGMAP_INVALID_ADDRESS"); break;
        case(0x05): Serial.println("WRITE: REGMAP_WRITE_DISABLED"); break;
        case(0x06): Serial.println("WRITE: WRONG_START_BYTE"); break;
        case(0x07): Serial.println("WRITE: BUS_OVER_RUN_ERROR"); break;
        case(0X08): Serial.println("WRITE: MAX_LENGTH_ERROR"); break;
        case(0x09): Serial.println("WRITE: MIN_LENGTH_ERROR"); break;
        case(0x0A): Serial.println("WRITE: RECEIVE_CHARACTER_TIMEOUT"); break;
        default: Serial.println("ErrorWriteDecode ERROR"); break;

    }
}

uint8_t BNO055::readByte(uint8_t reg)
{
    uint8_t Return_Data = 0;
    uint8_t Byte_Count = 1;
    uint8_t Transmit_Message[4] = {START_BYTE, READ_BYTE, reg, Byte_Count};
    uint8_t Recieve_Message[2] = {}; 
    // 0xAA 0x00(Write) 0x01(Read) 0xaddress 0xByte_Count 0xvalue

    //Flush Recieving Buffer
    recieveFlush();

    //Send Read Command
    //_Serial -> write(Transmit_Message, 4);
    _Serial -> print(Transmit_Message[0], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[1], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[2], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[3], BYTE);
    
    //Flush Transmitting Buffer
    _Serial -> flush();
    //vTaskDelay(5 / portTICK_PERIOD_MS);


    WaitForSerial(1, 10);
    uint8_t Response_Header = _Serial -> read();

    if(Response_Header == 0xBB)
    {
        WaitForSerial(1, 10);
        uint8_t Response_Length = _Serial -> read(); 
        if(Response_Length == Byte_Count)
        {
            WaitForSerial(1, 10);
            Return_Data = _Serial -> read(); 
        }
        
        else
        {
           Serial.println("READBYTE: ERROR:Incorrect Length"); 
        }
    }
    else if(Response_Header == 0x0EE)
    {
        WaitForSerial(1, 10);
        uint8_t Error_Code =_Serial -> read();
        ErrorReadDecode(Error_Code);
    }
    else
    {
         Serial.println("READBYTE: ERROR:No Response Header!");
    }

    //Read IMU Message
    

    // //Successfully Recieved Message
    // if(Recieve_Message[0] != SUCCESS_BYTE && Recieve_Message[1] == Byte_Count)
    // {
    //     Return_Data = Recieve_Message[2];
    // }

    // //Failed
    // else
    // {
    //     Serial.println("Read Error!");
    // }

    // wire->beginTransmission(Device_Address);
    // wire->write(reg);
    // wire->endTransmission();
    // wire->requestFrom(Device_Address, 1);
    // uint8_t data;
    // data = wire->read();
   
    return Return_Data;
}

bool BNO055::readBytes(uint8_t Reg, uint8_t Byte_Count, uint8_t * Data)
{
    bool Return_Status = false;

    uint8_t Transmit_Message[4] = {START_BYTE, READ_BYTE, Reg, Byte_Count};

    //Flush Recieving Buffer
    recieveFlush();
    
    //Send Read Command
    //_Serial -> write(Transmit_Message, 4);

    _Serial -> print(Transmit_Message[0], BYTE);
    delayMicroseconds(180);
    _Serial -> print(Transmit_Message[1], BYTE);
    delayMicroseconds(180);
    _Serial -> print(Transmit_Message[2], BYTE);
    delayMicroseconds(180);
    _Serial -> print(Transmit_Message[3], BYTE);
    
    //Flush Transmitting Buffer
    _Serial -> flush();

    //vTaskDelay(5 / portTICK_PERIOD_MS);
    //Get incomming status byte
    WaitForSerial(1, 10);
    uint8_t Response_Status = _Serial -> read();

    //Normal Operations
    if(Response_Status == 0xBB)
    {
        // Serial.print("READBYTES: RESPONSE STATUS: ");
        // Serial.println(Response_Status);
        //Check requested Bytes matches bytes to read
        WaitForSerial(1, 10);
        uint8_t Read_Length = _Serial -> read();
        if(Read_Length == Byte_Count)
        {
            //Read data bytes
            for(int Bytes_Read = 0; Bytes_Read < Byte_Count; Bytes_Read++)
            {
                WaitForSerial(1, 10);
                Data[Bytes_Read] = _Serial -> read();
            } 
            Return_Status = true;
        }       
        else
        {
             Serial.print("READBYTES: Incorrect length: ");
        }
    }
    //Operaton Error
    else if(Response_Status == 0xEE)
    {
        WaitForSerial(1, 10);
        uint8_t Error_Code =_Serial -> read();
        Serial.print("READBYTES: RESPONSE STATUS: ");
        Serial.println(Response_Status);
        ErrorReadDecode(Error_Code);
    }
    else
    {
        Serial.print("READBYTES: RESPONSE STATUS ERROR: ");
        Serial.println(Response_Status);
    }
       
    return Return_Status;
    // wire->beginTransmission(Device_Address);
    // wire->write(reg);
    // wire->endTransmission();
    // wire->requestFrom(Device_Address, count);
    // for(int i = 0; i < count; i++)
    // {
    //     data[i] = wire->read();
    // }
}

void BNO055::WaitForSerial(int Num_Bytes, int Timeout_MS)
{
    int Time_Start = millis();
    while((_Serial -> available() < Num_Bytes) && ((millis() - Time_Start) < Timeout_MS))
    {
        // Serial.println("WAITING!");
    }
    // Serial.print("RUNNING: ");
    // Serial.println(_Serial -> available());
    // Serial.println(((millis() - Time_Start) > Timeout_MS));
}

bool BNO055::writeByte(uint8_t reg, uint8_t data)
{
    bool Return_Status = false;
    int Recive_Count = 0;
    uint8_t Byte_Count = 1;
    uint8_t Transmit_Message[5] = {START_BYTE, WRITE_BYTE, reg, Byte_Count, data};
    
    //Flush Recieving Buffer
    recieveFlush();

    //Send Wrtie command to IMU
    _Serial -> print(Transmit_Message[0], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[1], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[2], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[3], BYTE);
    delayMicroseconds(50);
    _Serial -> print(Transmit_Message[4], BYTE);
    //_Serial -> write(Transmit_Message, 5);

    //Flush Transmitting Buffer
    _Serial -> flush();

    //vTaskDelay(5 / portTICK_PERIOD_MS);
    //Validate Data was sent by checking response.
    WaitForSerial(1, 10);
    uint8_t Response_Status = _Serial -> read();
    if(Response_Status == 0xEE)
    {
        Serial.print("WRITING: Recieved Response Byte");
        WaitForSerial(1, 10);
        uint8_t Status_Byte =_Serial -> read();
        if(Status_Byte != 0x01)
        {
            ErrorWriteDecode(Status_Byte);
            Return_Status = false;
        }
        else
        {
            Return_Status = true;
        }
    }
    else
    {
        Serial.print("WRITING: RESPONSE STATUS ERROR: ");
    }
    return Return_Status;
    // wire->beginTransmission(Device_Address);
    // wire->write(reg);
    // wire->write(data);
    // wire->endTransmission();
}

bool BNO055::init()
{
    //Check if device is working
    if(readByte(BNO055_CHIP_ID_ADDR) != BNO055_ID)
    {
        return false;
    }

    
    // //Set to config mode
    // writeByte(BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);

    // //Reset
    // writeByte(BNO055_SYS_TRIGGER_ADDR, 0x20);
    // //Wait for device to come back online
    // while(readByte(BNO055_CHIP_ID_ADDR) != BNO055_ID) {
    //     //vTaskDelay(5 / portTICK_PERIOD_MS);
    // }
    // //vTaskDelay(5 / portTICK_PERIOD_MS);
    // //Set to normal power mode
    // writeByte(BNO055_PWR_MODE_ADDR, POWER_MODE_NORMAL);
    // //vTaskDelay(5 / portTICK_PERIOD_MS);
    // //Set to page 0 of register map
    // writeByte(BNO055_PAGE_ID_ADDR, 0x0);
    // //Set to internal clock
    // writeByte(BNO055_SYS_TRIGGER_ADDR, 0x0);
    // //vTaskDelay(5 / portTICK_PERIOD_MS);
    
    //Set operating mode
    //9DOF sensor fusion
    writeByte(BNO055_OPR_MODE_ADDR, OPERATION_MODE_NDOF);
    //vTaskDelay(5 / portTICK_PERIOD_MS);

    return true;
}

bool BNO055::getEuler(Euler *euler)
{
    uint8_t buffer[6];
    bool Return_Status = false;

    if(readBytes(BNO055_EULER_H_LSB_ADDR, 6, buffer))
    {
        euler->X = (int16_t)(((uint16_t)buffer[3] << 8) | buffer[2]);
        euler->Y = (int16_t)(((uint16_t)buffer[5] << 8) | buffer[4]);
        euler->Z = (int16_t)(((uint16_t)buffer[1] << 8) | buffer[0]);
        Return_Status = true;
    }
    if((euler->X == 0) && (euler->Y == 0) && (euler->Z == 0))
    {
        init();
    }

    return Return_Status;
}

Quaternion BNO055::getQuaternion()
{
    uint8_t buffer[8];
    Quaternion quat;

    readBytes(BNO055_QUATERNION_DATA_W_LSB_ADDR, 8, buffer);
    quat.W = (int16_t)(((uint16_t)buffer[1] << 8) | buffer[0]);
    quat.X = (int16_t)(((uint16_t)buffer[3] << 8) | buffer[1]);
    quat.Y = (int16_t)(((uint16_t)buffer[5] << 8) | buffer[4]);
    quat.Z = (int16_t)(((uint16_t)buffer[7] << 8) | buffer[6]);

    return quat;
}

