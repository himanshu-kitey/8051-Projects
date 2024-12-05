#ifndef __I2C_HEADER_H__
#define __I2C_HEADER_H__

void i2c_start();
void i2c_stop();
void i2c_restart();
void i2c_slave_ack();
void i2c_not_ack();
void i2c_write(_U8);
_U8 i2c_read();
void i2c_byte_write(_U8,_U8);
_U8 i2c_random_read(u8);

#endif