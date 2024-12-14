#include <reg51.h>
#include "types.h"
#include "dlyMs.h"
#include "lcdHeaders.h"
#define LCD P0

sbit RS=P3^0;
sbit RW=P3^1;
sbit EN=P3^3;
u8 str[3];
u8 s;

void lcd_init(void)
{
	dlyMs(15);
	write_cmd(0x30);
	dlyMs(5);
	write_cmd(0x30);
	dlyMs(1);
	write_cmd(0x30);
	dlyMs(1);
	write_cmd(0x38);
	write_cmd(0x10);
	write_cmd(0x01);
	write_cmd(0x06);
	write_cmd(0x0c);
}

void write_cmd(u8 c)
{
	LCD=c;
	RS=0;
	RW=0;
	EN=1;
	dlyMs(1);
	EN=0;
}

void write_data(u8 c)
{
	LCD=c;
	RS=1;
	RW=0;
	EN=1;
	dlyMs(1);
	EN=0;
}

void lcd_stringData(u8 *str)
{
	while(*str)
		write_data(*str++);
}

void lcd_intData(u8 n)
{
	 s=0;
	 while(n)
	 {
		 str[s++]=(n%10)+48;
		 n=n/10;
	 }
	 while(s)
	 {
		 write_data(str[--s]);
	 } 
}

void lcd_floatData(f32 value)
{
	 u8 n=value;
	lcd_intData(n);
	s=2;
	write_data('.');
	n=value;
	while(s)
	{
		value=(value-n)*10;
		n=value;
		write_data(n+48);
		s--;
	}
}
