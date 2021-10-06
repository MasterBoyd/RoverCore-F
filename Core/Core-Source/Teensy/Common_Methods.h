#ifndef COMMON_METHODS_H
#define COMMON_METHODS_H

#include "FreeRTOS_ARM.h"

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s
#define PRIORITY(p) tskIDLE_PRIORITY + p
#define ARR_SIZEOF(x)   (sizeof((x)) / sizeof((x[0])))
#define FOREVER 1

typedef enum
{
    PRIORITY_CRITICAL   = PRIORITY(3),
    PRIORITY_HIGH       = PRIORITY(2),
    PRIORITY_MEDIUM     = PRIORITY(1),
    PRIORITY_LOW        = PRIORITY(0)
} RTOS_Task_Priorities;

// #define PRIORITY_CRITICAL  (tskIDLE_PRIORITY + 3)
// #define PRIORITY_HIGH      (tskIDLE_PRIORITY + 2)
// #define PRIORITY_MEDIUM    (tskIDLE_PRIORITY + 1)
// #define PRIORITY_LOW       (tskIDLE_PRIORITY + 0)


// typedef enum
// {
  
// } RTOS_Task_Priorities;







#endif //Common_Methods.h