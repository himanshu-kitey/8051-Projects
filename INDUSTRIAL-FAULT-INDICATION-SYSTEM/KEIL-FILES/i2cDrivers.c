#include <reg51.h>
#include "types.h"
#include "dlyMs.h"

sbit SCL=P1^4;
sbit SDA=P1^5;

void i2c_start(void)
{
	SDA=0;
}

void i2c_stop(void)
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}

void i2c_restart(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
	SDA=0;
}

void i2c_slave_ack(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
	while(SDA);
}

void i2c_not_ack(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
}

void i2c_write(u8 value)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SCL=0;
		SDA = (value >>(7-i))&1;
		SCL=1;
	}
}

u8 i2c_read(void)
{
	u8 i,buff=0;
	for(i=0;i<8;i++)
	{
		SCL=0; SCL=1;
		if(SDA) buff |= (0x80>>i);
	}
	return buff;
}

void i2c_byte_write(u8 ad,u8 da)
{
	i2c_start();
	i2c_write(0x50<<1);
	i2c_slave_ack();
	i2c_write(ad);
	i2c_slave_ack();
	i2c_write(da);
	i2c_slave_ack();
	i2c_stop();
	dlyMs(10);
}

u8 i2c_random_read(u8 ad)
{
	u8 buff;
	i2c_start();
	i2c_write(0x50<<1);
	i2c_slave_ack();
	i2c_write(ad);
	i2c_slave_ack();
	i2c_restart();
	i2c_write((0x50<<1)|1);
	i2c_slave_ack();
	buff=i2c_read();
	i2c_not_ack();
	i2c_stop();
	return buff;
}
