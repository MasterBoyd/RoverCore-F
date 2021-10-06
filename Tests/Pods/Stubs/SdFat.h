#ifndef SDFAT_H
#define SDFAT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

class SdFat
{
public:
  SdFat();
  bool begin(uint8_t csPin);
  
  
};



#endif /* PRINT_H */