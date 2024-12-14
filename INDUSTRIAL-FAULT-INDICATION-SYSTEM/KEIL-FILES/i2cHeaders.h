#ifndef __I2C_HEADER_H__
#define __I2C_HEADER_H__

#include "types.h"

void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_slave_ack(void);
void i2c_not_ack(void);
void i2c_write(u8);
u8 i2c_read(void);
void i2c_byte_write(u8,u8);
u8 i2c_random_read(u8);

#endif