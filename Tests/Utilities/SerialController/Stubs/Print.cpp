#include "Print.h"

Print::Print()
{

}

// int Print::printf(const char *format, ...)
// {
// 	return false;
// }
// int Print::printf(const __FlashStringHelper *format, ...)
// {
// 	return false;
// }
void Print::println(char *s)
{
    strcat(CharacterCapture, s);
}

void Print::ClearString()
{
    memset(CharacterCapture, 0, sizeof(CharacterCapture));
}

const char* Print::ReturnCapture()
{
    return CharacterCapture;
}