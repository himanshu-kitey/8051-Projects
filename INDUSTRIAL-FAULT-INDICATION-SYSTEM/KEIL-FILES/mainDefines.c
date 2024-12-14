#include "dlyMs.h"
#include "lcdHeaders.h"
#include "mainHeaders.h"

u8 x;

void delay_3()
{
	dlyMs(3000);
}

void set_str()
{
	lcd_stringData("Set Tmp");
}

void back_loop(u8 u,u8 *pass)
{
	for(x=0;x<u;x++)
		write_data(pass[x]);
}

void sucess_str()
{
	lcd_stringData("Sucess");
}

void pass_str()
{
	lcd_stringData("Enter 5 Digt Pass : ");
}

void lcd_2ndLine()
{
	write_cmd(0xc0);
}

void lcd_cmd()
{
	write_cmd(0x01);
	write_cmd(0x80);
}
