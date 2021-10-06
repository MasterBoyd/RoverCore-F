#ifndef FreeRTOS_ARM_h
#define FreeRTOS_ARM_h

#include <stdint.h>

typedef uint32_t TickType_t;
#define portMAX_DELAY 		( TickType_t ) 0xffffffffUL
#define configTICK_RATE_HZ	( ( TickType_t ) 1000 )
#define portTICK_PERIOD_MS	( ( TickType_t ) 1000 / configTICK_RATE_HZ )


TickType_t xTaskGetTickCount();
void vTaskDelayUntil(TickType_t *LastWakeTime, TickType_t Delay);

#endif // FreeRTOS_ARM.h