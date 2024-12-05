#include <reg51.h>
#include "_types.h"
#include "_delay_ms.h"
sbit SCL=P1^4;
sbit SDA=P1^5;

void i2c_start()
{
	SDA=0;
}
void i2c_stop()
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}
void i2c_restart()
{
	SCL=0;
	SDA=1;
	SCL=1;
	SDA=0;
}
void i2c_slave_ack()
{
	SCL=0;
	SDA=1;
	SCL=1;
	while(SDA);
}
void i2c_not_ack()
{
	SCL=0;
	SDA=1;
	SCL=1;
}

void i2c_write(_U8 value)
{
	_U8 i;
	for(i=0;i<8;i++)
	{
		SCL=0;
		SDA = (value >>(7-i))&1;
		SCL=1;
	}
}
_U8 i2c_read()
{
	_U8 i,buff=0;
	for(i=0;i<8;i++)
	{
		SCL=0; SCL=1;
		if(SDA) buff |= (0x80>>i);
	}
	return buff;
}

void i2c_byte_write(_U8 ad,_U8 da)
{
	i2c_start();
	i2c_write(0x50<<1);
	i2c_slave_ack();
	i2c_write(ad);
	i2c_slave_ack();
	i2c_write(da);
	i2c_slave_ack();
	i2c_stop();
	_delay_ms(10);
}
_U8 i2c_random_read(_U8 ad)
{
	_U8 buff;
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