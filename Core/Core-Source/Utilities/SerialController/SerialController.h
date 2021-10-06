#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include <stdio.h>
#include "stdint.h"
#include <stdbool.h>
#include <string.h>
#include "Stream.h"
#include <math.h>

#define MAX_STORAGE 256 // size of uint8_t
#define BUFFER_SIZE 300  //Size needed to print @uint8_t,uint32_t/n
#define VARIABLES_IN_MESSAGE 1

typedef enum
{
    NOTSET,
    UINT8_T,
    UINT16_T,
    UINT32_T,
    UINT64_T,
    INT8_T,
    INT16_T,
    INT32_T,
    INT64_T,
    FLOAT_T,
    DOUBLE_T
} DataTypes_E;

typedef struct
{
    uint64_t Coppied = 0;
    void *Pointed = &Coppied;
    uint8_t Type = NOTSET;
} Storage_Send_S;

typedef struct
{
    void *Pointed;
    uint8_t Type = NOTSET;
} Storage_Recieve_S;

typedef struct
{
    char Buffer_Out[BUFFER_SIZE] = {0};
    char Buffer_In[BUFFER_SIZE] = {0};
} Controller_t;

class SerialController : public Stream
{
public:
    char TempBuffer[100];
    SerialController();

    //Functions for user send
    bool SetToSend(uint8_t key, void * var, DataTypes_E type);
    bool SetToSend(uint8_t key, uint8_t *var);
    bool SetToSend(uint8_t key, uint16_t *var);
    bool SetToSend(uint8_t key, uint32_t *var);
    bool SetToSend(uint8_t key, uint64_t *var);
    bool SetToSend(uint8_t key, int8_t *var);
    bool SetToSend(uint8_t key, int16_t *var);
    bool SetToSend(uint8_t key, int32_t *var);
    bool SetToSend(uint8_t key, int64_t *var);
    bool SetToSend(uint8_t key, float *var);
    bool SetToSend(uint8_t key, double *var);

    //Functions for user Receive
    bool SetToReceive(uint8_t key, void * var, DataTypes_E type);
    bool SetToReceive(uint8_t key, uint8_t *var);
    bool SetToReceive(uint8_t key, uint16_t *var);
    bool SetToReceive(uint8_t key, uint32_t *var);
    bool SetToReceive(uint8_t key, uint64_t *var);
    bool SetToReceive(uint8_t key, int8_t *var);
    bool SetToReceive(uint8_t key, int16_t *var);
    bool SetToReceive(uint8_t key, int32_t *var);
    bool SetToReceive(uint8_t key, int64_t *var);
    bool SetToReceive(uint8_t key, float *var);
    bool SetToReceive(uint8_t key, double *var);

    // //Functions for serial Task send
    void MovePointedToCopied(uint8_t key);
    bool CheckIfNew(uint8_t key);
    void SerialSend(uint8_t key);
    void SerialSendAll();
    void reverse(char *str, int len); 
    int intToStr(int x, char str[], int d);
    void ftoa(double n, char *res, int afterpoint);
    const char* GetIt();

    // //Functions for serial Task Receive
    bool DecodeAndApply(const char *Message);
    bool CollectIncomming();

    void InitiateConnMonitor(int Check_Rate, int Interval);
    void HandelConnMonitor();
    bool CheckConnStatus();

    int  NumDigits (int n);
    void Append(char* C_String, char Character);
    virtual int available(){ printf("Printing wrong available!!!!\n");return 0;};
    virtual int read() {return 0;};
private:
    Storage_Send_S Storage_Send[MAX_STORAGE];
    Storage_Recieve_S Storage_Recieve[MAX_STORAGE];
    //char Buffer_Tmp[300];
    Controller_t Serial_Ctrl;
    
    uint32_t Conn_Incomming;
    int Conn_State;
    int Conn_Count;
    int Conn_Check_Rate;
    int Conn_Interval;
    bool Conn_Status;
};




#endif /* SERIAL_CONTROLLER_H */