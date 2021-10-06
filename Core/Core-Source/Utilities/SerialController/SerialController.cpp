#include "SerialController.h"
#include <stdlib.h>
#include "RTOS_Tasks.h"
#include "FreeRTOS_ARM.h"
// #define FALSE 0
// #define TRUE !(FALSE)
#define MEMEQUAL 0

static uint32_t Type_Sizes[] = {0, 1, 2, 4, 8, 1, 2, 4, 8, 4, 8};

SerialController::SerialController() { }

////////////////////////////////////////////////////////////////////////
//Send
////////////////////////////////////////////////////////////////////////
bool SerialController::SetToSend(uint8_t key, void * var, DataTypes_E type)
{
	bool Success = false;

	if(Storage_Send[key].Type == NOTSET)
	{
		Storage_Send[key].Type = type;
		Storage_Send[key].Pointed = var;
		Success = true;
	}
	return Success;
}
bool SerialController::SetToSend(uint8_t key, uint8_t *var)
{
	return SetToSend(key, (void *)var, UINT8_T);
}
bool SerialController::SetToSend(uint8_t key, uint16_t *var)
{
	return SetToSend(key, (void *)var, UINT16_T);
}
bool SerialController::SetToSend(uint8_t key, uint32_t *var)
{
	return SetToSend(key, (void *)var, UINT32_T);
}
// bool SerialController::SetToSend(uint8_t key, uint64_t *var)
// {
// 	return SetToSend(key, (void *)var, UINT64_T);
// }
bool SerialController::SetToSend(uint8_t key, int8_t *var)
{
	return SetToSend(key, (void *)var, INT8_T);
}
bool SerialController::SetToSend(uint8_t key, int16_t *var)
{
	return SetToSend(key, (void *)var, INT16_T);
}
bool SerialController::SetToSend(uint8_t key, int32_t *var)
{
	return SetToSend(key, (void *)var, INT32_T);
}
// bool SerialController::SetToSend(uint8_t key, int64_t *var)
// {
// 	return SetToSend(key, (void *)var, INT64_T);
// }
bool SerialController::SetToSend(uint8_t key, float *var)
{
	return SetToSend(key, (void *)var, FLOAT_T);
}
bool SerialController::SetToSend(uint8_t key, double *var)
{
	return SetToSend((uint8_t)key, (void *)var, DOUBLE_T);
}

bool SerialController::CheckIfNew(uint8_t key)
{
	bool Is_New = false;

	// Compares the bytes in the uint64_t data space instead of the value inside that requires a type.
		if(memcmp((uint64_t*)Storage_Send[key].Pointed, &Storage_Send[key].Coppied, Type_Sizes[Storage_Send[key].Type]) != MEMEQUAL)
		{
			Is_New = true;
		}

	return Is_New;
}


void SerialController::MovePointedToCopied(uint8_t key)
{
	Storage_Send[key].Coppied = 0;
	memcpy ( &Storage_Send[key].Coppied, Storage_Send[key].Pointed, Type_Sizes[Storage_Send[key].Type]);
}

void SerialController::SerialSend(uint8_t key)
{
	char SendBuffer[50] = {0};
	if(CheckIfNew(key))
	{
		MovePointedToCopied(key);
		switch(Storage_Send[key].Type)
		{
            case UINT8_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%u\r\n", key, *((uint8_t*)Storage_Send[key].Pointed));
                break;
            case UINT16_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%u\r\n", key, *((uint16_t*)Storage_Send[key].Pointed));
                break;
            case UINT32_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%u\r\n", key, *((uint32_t*)Storage_Send[key].Pointed));
                break;
            case UINT64_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%lu\r\n", key, *((uint64_t*)Storage_Send[key].Pointed));
                break;
            case INT8_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%d\r\n", key, *((int8_t*)Storage_Send[key].Pointed));
                break;
            case INT16_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%d\r\n", key, *((int16_t*)Storage_Send[key].Pointed));
                break;
            case INT32_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%d\r\n", key, *((int32_t*)Storage_Send[key].Pointed));
                break;
            case INT64_T:
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%ld\r\n", key, *((int64_t*)Storage_Send[key].Pointed));
                break;
            case FLOAT_T:
            	ftoa(*(float*)Storage_Send[key].Pointed, SendBuffer, 3);
                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%s\r\n", key, SendBuffer);
                break;
            case DOUBLE_T:
            	double Temp = *(double*)Storage_Send[key].Pointed;
            	if(Temp < 0)
            	{
            		Temp = Temp + (Temp * (-2));
            		ftoa(Temp, SendBuffer, 8);
	                sprintf(Serial_Ctrl.Buffer_Out, "@%c,-%s\r\n", key, SendBuffer);
            	}
            	else{
	            	ftoa(*(double*)Storage_Send[key].Pointed, SendBuffer, 8);
	                sprintf(Serial_Ctrl.Buffer_Out, "@%c,%s\r\n", key, SendBuffer);
            	}
	            break;

        }
		this->println(Serial_Ctrl.Buffer_Out);
	}
}

void SerialController::SerialSendAll()
{
	for(int key = 0; key < MAX_STORAGE; key++)
	{
		if((Storage_Send[key].Type != NOTSET) && CheckIfNew(key))
		{
			SerialSend(key);
			vTaskDelay(DELAY_MS(15));
		}
	}
}

// //memcpy ( &person_copy, &person, sizeof(person) );
// //memcpy(Storage_Send.Pointed, (uint64_t*)var, sizeof(var));

////////////////////////////////////////////////////////////////////////
//Receive
////////////////////////////////////////////////////////////////////////

////SetToRecieve////
bool SerialController::SetToReceive(uint8_t key, void * var, DataTypes_E type)
{
	bool Success = false;
	if(Storage_Recieve[key].Type == NOTSET)
	{
		Storage_Recieve[key].Type = type;
		Storage_Recieve[key].Pointed = var;
		Success = true;
	}
	return Success;
}
bool SerialController::SetToReceive(uint8_t key, uint8_t *var)
{
	return SetToReceive(key, var, UINT8_T);
}
bool SerialController::SetToReceive(uint8_t key, uint16_t *var)
{
	return SetToReceive(key, var, UINT16_T);
}
bool SerialController::SetToReceive(uint8_t key, uint32_t *var)
{
	return SetToReceive(key, var, UINT32_T);
}
// bool SerialController::SetToReceive(uint8_t key, uint64_t *var)
// {
// 	return SetToReceive(key, var, UINT64_T);
// }
bool SerialController::SetToReceive(uint8_t key, int8_t *var)
{
	return SetToReceive(key, var, INT8_T);
}
bool SerialController::SetToReceive(uint8_t key, int16_t *var)
{
	return SetToReceive(key, var, INT16_T);
}
bool SerialController::SetToReceive(uint8_t key, int32_t *var)
{
	return SetToReceive(key, var, INT32_T);
}
// bool SerialController::SetToReceive(uint8_t key, int64_t *var)
// {
// 	return SetToReceive(key, var, INT64_T);
// }
bool SerialController::SetToReceive(uint8_t key, float *var)
{
	return SetToReceive(key, var, FLOAT_T);
}
bool SerialController::SetToReceive(uint8_t key, double *var)
{
	return SetToReceive((uint8_t)key, var, DOUBLE_T);
}

bool SerialController::DecodeAndApply(const char *Message)
{
	bool        Success = 0;
	bool        Check_Key = false;
	int         Check_Size = 0;
	uint8_t     key;
	uint64_t    Temp_Store = 0;
	const int 	SKIP_MESSAGE_KEY = 3;
	const char  *Formats[] = {
		"",             // case NOTSET:
		"%d|\r\n",       // case UINT8_T:
		"%hd|\r\n",      // case UINT16_T:
		"%d|\r\n",       // case UINT32_T:
		"%ju|\r\n",      // case UINT64_T:
		"%d|\r\n",       // case INT8_T:
		"%hd|\r\n",      // case INT16_T:
		"%d|\r\n",       // case INT32_T:
		"%jd|\r\n",      // case INT64_T:
		"%d|\r\n",    // case FLOAT_T:
		"%d|\r\n"     // case DOUBLE_T:
	};

	//Get Key to properly decode
	Check_Key = sscanf(Message,"@%c,", &key);

	if(Check_Key == true)
	{
		Check_Size = sscanf(&Message[SKIP_MESSAGE_KEY],
			Formats[Storage_Recieve[key].Type],
			&Temp_Store
		);
		if(Check_Size == VARIABLES_IN_MESSAGE)
		{
			switch(Storage_Recieve[key].Type)
			{
				case FLOAT_T:
					*(float *)Storage_Recieve[key].Pointed = (float)atof(&Message[SKIP_MESSAGE_KEY]);
					break;
				case DOUBLE_T:
					*(double *)Storage_Recieve[key].Pointed = atof(&Message[SKIP_MESSAGE_KEY]);
					break;
				default:
					uint32_t Type_Size = Type_Sizes[Storage_Recieve[key].Type];
					memcpy(Storage_Recieve[key].Pointed, ((char *)&Temp_Store), Type_Size);
					break;
			}
			Success = true;
		}
	}
	return Success;
}

void SerialController::Append(char* C_String, char Character)
{
	int length = strlen(C_String);
	C_String[length] = Character;
	C_String[length+1] = '\0';
}

// const char* SerialController::GetIt()
// {
// 	return Buffer_Tmp;
// }


bool SerialController::CollectIncomming()
{
	char Incomming_Char = 0;
	bool Success = false;
	int state = 0;
	//memset(Buffer_Tmp, '\0', sizeof(Serial_Ctrl.Buffer_In));
	while(this->available())
	{
		Incomming_Char = (char)this->read();
		//this->Append(Buffer_Tmp, Incomming_Char);

		switch(state)
		{
			case 0:
				if(Incomming_Char == '@')
				{
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
					state = 1;
				}
				break;
			case 1:
				this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
				if(Incomming_Char == '|')
				{
					state = 2;
				}
				else if(Incomming_Char == '@')
				{
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
				}
				break;
			case 2:
				if(Incomming_Char == '\r')
				{
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
					state = 3;
				}
				else if(Incomming_Char == '@')
				{
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
					state = 1;
				}
				else
				{
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					state = 0;
				}
				break;
			case 3:
				if(Incomming_Char == '\n')
				{
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
					this->DecodeAndApply(Serial_Ctrl.Buffer_In);
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					state = 0;
					Success = true;
				}
				else if(Incomming_Char == '@')
				{
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
					state = 1;
				}
				else
				{
					memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
					state = 0;
				}
				break;
		}
		//printf("%s\n",Serial_Ctrl.Buffer_In);
	}
	return Success;
}



		// if(Incomming_Char == '@')
		// this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);





		// if(Incomming_Char == '|')
		// {
		// 	Incomming_Char = (char)this->read();
		// 	this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
		// 	if(Incomming_Char == '\r')
		// 	{
		// 		Incomming_Char = (char)this->read();
		// 		this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
		// 		if(Incomming_Char == '\n')
		// 		{
		// 			this->DecodeAndApply(Serial_Ctrl.Buffer_In);
		// 			memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
		// 			Success = true;
		// 		}
		// 	}
		// }
// while(this->available())
// 	{
// 		Incomming_Char = (char)this->read();
// 		if(Incomming_Char == '@')
// 		{
// 			this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
// 			for(int i = 0; (i < 51) || (Incomming_Char == '|'); i++)
// 			{
// 				Incomming_Char = (char)this->read();
// 				this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
// 				if(i == 50) {memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));}
// 			}
// 			if(Incomming_Char == '|')
// 			{
// 				this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
// 				Incomming_Char = (char)this->read();
// 				if(Incomming_Char == '\r')
// 				{
// 					this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
// 					Incomming_Char = (char)this->read();
// 					if(Incomming_Char == '\n')
// 					{
// 						this->Append(Serial_Ctrl.Buffer_In, Incomming_Char);
// 						this->DecodeAndApply(Serial_Ctrl.Buffer_In);
// 						memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));
// 						Success = true;
// 					}
// 					else {memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));}
// 				}
// 				else {memset(Serial_Ctrl.Buffer_In, '\0', sizeof(Serial_Ctrl.Buffer_In));}
// 			}
// 		}
// 	}


// C program for implementation of ftoa()
#include<stdio.h>
#include<math.h>
 
// reverses a string 'str' of length 'len'
void SerialController::reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int SerialController::intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
 
// Converts a floating point number to string.
void SerialController::ftoa(double n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    double fpart = n - (double)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}


void SerialController::InitiateConnMonitor(int Check_Rate, int Interval)
{
	Conn_Check_Rate = Check_Rate;
	Conn_Interval = Interval;
	Conn_Incomming = 0;
	Conn_State = 0;
	Conn_Count = 10000;
	Conn_Status = 0;
	SetToReceive('~', &Conn_Incomming); 
}

void SerialController::HandelConnMonitor()
{
	Conn_Count ++;
	// print("Conn_Incomming: "); print(Conn_Incomming);
	// print("Conn_State: "); println(Conn_State);
	//printf("%d %d\n\n",Conn_Incomming, Conn_State );
	if(Conn_Incomming != Conn_State)
	{
		Conn_State = Conn_Incomming;
		Conn_Count = 0;

	}
	if(Conn_Count < (Conn_Interval / Conn_Check_Rate))
	{
		Conn_Status = true;
	}
	else
	{
		Conn_Status = false;
	}
	
}

bool SerialController::CheckConnStatus()
{
	return Conn_Status;
}