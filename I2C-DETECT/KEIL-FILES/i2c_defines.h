											/*i2c_defines.h*/
#ifndef __I2C_DEFINES_H__
#define __I2C_DEFINES_H__

#include <reg51.h>
sbit SCL=P3^6;					// IO pin of 8051 connected to SCL line of I2C bus.
sbit SDA=P3^7;					// IO pin of 8051 connected to SDA line of I2C bus.

#endif
