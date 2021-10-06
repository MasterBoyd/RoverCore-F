#include "Print.h"

Print::Print()
{

}


void Print::println(char *s)
{
    strcat(CharacterCapture, s);
}

void print(const char *s)
{

}

void print(int s)
{
	
}

void Print::ClearString()
{
    memset(CharacterCapture, 0, sizeof(CharacterCapture));
}

const char* Print::ReturnCapture()
{
    return CharacterCapture;
}