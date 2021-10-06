#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <string.h>
#define CHARACTER_CAPTURE_SIZE 1000

class Print
{
public:
    Print();
    void println(char *s);
	void print(const char *s);  
	void print(int s);  
    const char* ReturnCapture();
    void ClearString();
private:
    char CharacterCapture[CHARACTER_CAPTURE_SIZE] = {0};
};

#endif /* PRINT_H */