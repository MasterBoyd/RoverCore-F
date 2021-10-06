/////////////////////////////////////////////////////////////////////////////
//                              Includes                                   //
/////////////////////////////////////////////////////////////////////////////

//// Core Libraries ////
#include "WProgram.h"
#include "FreeRTOS_ARM.h"
#include <stdbool.h>
#include <stdio.h>
#include "Common_Methods.h"
#include "CommonFunctions.h"

//// User Libraries ////
#include "Methods.h"
#include "RTOS_Tasks.h"
#include "UserInterrupts.h"


/////////////////////////////////////////////////////////////////////////////
//                              Defines                                    //
/////////////////////////////////////////////////////////////////////////////

#define DELAY_MS(ms) (ms / portTICK_PERIOD_MS)
#define STACK(s) configMINIMAL_STACK_SIZE + s
#define PRIORITY(p) tskIDLE_PRIORITY + p
#define ARR_SIZEOF(x)   (sizeof((x)) / sizeof((x[0])))
#define BAUDRATE 38400

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Handels                               //
/////////////////////////////////////////////////////////////////////////////

TaskHandle_t Heart;
TaskHandle_t Serial_Task;
TaskHandle_t CurrentSense;
TaskHandle_t TempSense;
TaskHandle_t Bluetooth;
TaskHandle_t CommandResponse;




/////////////////////////////////////////////////////////////////////////////
//                              Startup                                    //
/////////////////////////////////////////////////////////////////////////////
extern "C" 
int main(void)
{

    // Initializing USB Serial Communication
    Serial.begin(BAUDRATE);
    // while(!Serial) {}
    Serial.println("Teensy is Alive!");

    // Initializing UART Serial Communications
    Serial1.begin(BAUDRATE);
    // while(!Serial1) {}
    // Serial2.begin(BAUDRATE);
    // while(!Serial2) {}
    
    //set output pins
    pinMode(BAT_RELAY1, OUTPUT);
    pinMode(BAT_RELAY2, OUTPUT);
    pinMode(BAT_RELAY3, OUTPUT);
    pinMode(DRIVE_BACKUP_RELAY, OUTPUT);
    pinMode(STEER_RELAY, OUTPUT);
    pinMode(ARM_RELAY, OUTPUT);
    pinMode(DRIVE_FRONT_RELAY, OUTPUT);
    pinMode(DRIVE_BACK_RELAY, OUTPUT);
    // pinMode(BLUETOOTH_TX, OUTPUT);
    pinMode(BLUETOOTH_ST, OUTPUT);
    pinMode(REAL_TIME_CTRL, OUTPUT);

    //set input pins
    pinMode(OPEN_CIR_VOL1, INPUT);
    pinMode(OPEN_CIR_VOL2, INPUT);
    pinMode(OPEN_CIR_VOL3, INPUT);
    pinMode(REAL_TIME_VOL, INPUT);
    // pinMode(BLUETOOTH_RX, INPUT);

    //set input resolution (0-4095)
    analogReadResolution(INPUT_RESOLUTION);

    //set PWM frequency for relays
    analogWriteFrequency(BAT_RELAY1, PWM_FREQUENCY);
    analogWriteFrequency(BAT_RELAY2, PWM_FREQUENCY);
    analogWriteFrequency(BAT_RELAY3, PWM_FREQUENCY);
    analogWriteFrequency(DRIVE_BACKUP_RELAY, PWM_FREQUENCY);
    analogWriteFrequency(STEER_RELAY, PWM_FREQUENCY);
    analogWriteFrequency(ARM_RELAY, PWM_FREQUENCY);
    analogWriteFrequency(DRIVE_FRONT_RELAY, PWM_FREQUENCY);
    analogWriteFrequency(DRIVE_BACK_RELAY, PWM_FREQUENCY);
    // analogWriteFrequency(INTEL_RELAY, PWM_FREQUENCY);
    // analogWriteFrequency(MAST_RELAY, PWM_FREQUENCY);

    // while(1) {
    //     Serial1.println(0xAA);
    //     // Serial1.flush();
    //     digitalWrite(13, HIGH);
    //     delay(500);
    //     Serial1.println(0xAA);
    //     // Serial1.flush();
    //     digitalWrite(13, LOW);
    //     delay(500);
    // }
    
    

    delay(1000);

/////////////////////////////////////////////////////////////////////////////
//                              RTOS Task Initalization                    //
/////////////////////////////////////////////////////////////////////////////

//// Heart Beat Task ////
    xTaskCreate(
        vHeartBeatTask, //Function that implements the task
        "Heart",        //Test name for the task
        STACK(256),     //Stack size in words, no bytes
        NULL,           //Parameter passes into the task
        PRIORITY_CRITICAL,//Priority at which the task is created
        &Heart          //Used to pass out the created task's handel
    );

//// SerialController Task ////
    // xTaskCreate(
    //     vSerialController,   //Function that implements the task
    //     "Serial",      //Test name for the task
    //     STACK(256),    //Stack size in words, not bytes
    //     NULL,          //Parameter that is passed into the task
    //     PRIORITY_MEDIUM,   //Priority at which the task is created
    //     &Serial_Task   //Used to pass out the created task's handel
    //  );

    xTaskCreate(
        vCurrentSense,
        "CurrentSense",
        STACK(256),
        NULL,
        PRIORITY_HIGH,
        &CurrentSense
    );

    // xTaskCreate(
    //     vTempSense,
    //     "TempSense",
    //     STACK(256),
    //     NULL,
    //     PRIORITY_HIGH,
    //     &TempSense
    // );

    xTaskCreate(
        vBluetoothController,
        "BluetoothController",
        STACK(256),
        NULL,
        PRIORITY_HIGH,
        &Bluetooth
    );

    // Start FreeRTOS
    vTaskStartScheduler();

    // should never return
    while(1);
}