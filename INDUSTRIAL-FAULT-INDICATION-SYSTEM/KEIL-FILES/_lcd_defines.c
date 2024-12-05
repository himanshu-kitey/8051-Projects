#include <reg51.h>
#include "_types.h"
#include "_delay_ms.h"
#include "_lcd_headers.h"
#define LCD P0

sbit RS=P3^0;
sbit RW=P3^1;
sbit EN=P3^3;
_U8 str[3];
_U8 s;

void _lcd_init()
{
	_delay_ms(15);
	_write_cmd(0x30);
	_delay_ms(5);
	_write_cmd(0x30);
	_delay_ms(1);
	_write_cmd(0x30);
	_delay_ms(1);
	_write_cmd(0x38);
	_write_cmd(0x10);
	_write_cmd(0x01);
	_write_cmd(0x06);
	_write_cmd(0x0c);
}

void _write_cmd(_U8 c)
{
	LCD=c;
	RS=0;
	RW=0;
	EN=1;
	_delay_ms(1);
	EN=0;
}

void _write_data(_U8 c)
{
	LCD=c;
	RS=1;
	RW=0;
	EN=1;
	_delay_ms(1);
	EN=0;
}

void _lcd_stringData(_U8 *str)
{
	while(*str)
		_write_data(*str++);
}

void _lcd_intData(_U8 n)
{
	 s=0;
	 while(n)
	 {
		 str[s++]=(n%10)+48;
		 n=n/10;
	 }
	 while(s)
	 {
		 _write_data(str[--s]);
	 } 
}

void _lcd_floatData(_F32 value)
{
	 _U8 n=value;
	_lcd_intData(n);
	s=2;
	_write_data('.');
	n=value;
	while(s)
	{
		value=(value-n)*10;
		n=value;
		_write_data(n+48);
		s--;
	}
}