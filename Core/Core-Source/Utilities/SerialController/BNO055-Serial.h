#ifndef BNO055_HPP
#define BNO055_HPP

#include <stdint.h>
#include <i2c_t3.h>
#include "quaternion.hpp"

#define BNO055_ID        (0xA0)
#define BNO055_PAGE_ID_ADDR 0x07
#define BNO055_CHIP_ID_ADDR 0x00
#define BNO055_ACCEL_REV_ID_ADDR 0x01
#define BNO055_MAG_REV_ID_ADDR 0x02
#define BNO055_GYRO_REV_ID_ADDR 0x03
#define BNO055_SW_REV_ID_LSB_ADDR 0x04
#define BNO055_SW_REV_ID_MSB_ADDR 0x05
#define BNO055_BL_REV_ID_ADDR 0x06

#define BNO055_EULER_H_LSB_ADDR 0x1A

#define BNO055_QUATERNION_DATA_W_LSB_ADDR 0x20

#define BNO055_OPR_MODE_ADDR 0x3D
#define BNO055_PWR_MODE_ADDR 0x3C

#define BNO055_SYS_TRIGGER_ADDR 0x3F


//UART
#define START_BYTE     0xAA
#define READ_BYTE      0x01
#define WRITE_BYTE     0x00
#define LENGTH_1_BYTE  0x01
#define SUCCESS_BYTE   0xBB

typedef enum
{
  POWER_MODE_NORMAL                                       = 0X00,
  POWER_MODE_LOWPOWER                                     = 0X01,
  POWER_MODE_SUSPEND                                      = 0X02
} adafruit_bno055_powermode_t;

typedef enum
{
  /* Operation mode settings*/
  OPERATION_MODE_CONFIG                                   = 0X00,
  OPERATION_MODE_ACCONLY                                  = 0X01,
  OPERATION_MODE_MAGONLY                                  = 0X02,
  OPERATION_MODE_GYRONLY                                  = 0X03,
  OPERATION_MODE_ACCMAG                                   = 0X04,
  OPERATION_MODE_ACCGYRO                                  = 0X05,
  OPERATION_MODE_MAGGYRO                                  = 0X06,
  OPERATION_MODE_AMG                                      = 0X07,
  OPERATION_MODE_IMUPLUS                                  = 0X08,
  OPERATION_MODE_COMPASS                                  = 0X09,
  OPERATION_MODE_M4G                                      = 0X0A,
  OPERATION_MODE_NDOF_FMC_OFF                             = 0X0B,
  OPERATION_MODE_NDOF                                     = 0X1C
} adafruit_bno055_opmode_t;

typedef enum
{
    BNO055_ADDRESS_A = 0x28,
    BNO055_ADDRESS_B = 0x29
} BNO055_Address;

class BNO055
{
    private:
        bool readBytes(uint8_t reg, uint8_t count, uint8_t * data);
        bool writeByte(uint8_t reg, uint8_t data);
        uint8_t readByte(uint8_t reg);
        void recieveFlush();
        void ErrorReadDecode(uint8_t Error);
        void ErrorWriteDecode(uint8_t Error);
        void WaitForSerial(int Num_Bytes, int Timeout_MS);
        HardwareSerial * _Serial;
        //i2c_t3 * wire;
    public:
        BNO055(HardwareSerial *Serial_Input);
        bool init();
        bool getEuler(Euler *euler);
        Quaternion getQuaternion();

};

#endif
