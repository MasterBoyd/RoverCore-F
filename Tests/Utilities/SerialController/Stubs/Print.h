#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <string.h>
#define CHARACTER_CAPTURE_SIZE 1000

class __FlashStringHelper;

class Print
{
public:
    Print();
    //int printf(const char *format, ...);
    //int printf(const __FlashStringHelper *format, ...);
    void println(char *s);
    const char* ReturnCapture();
    void ClearString();
private:
    char CharacterCapture[CHARACTER_CAPTURE_SIZE] = {0};
};

#endif /* PRINT_H */