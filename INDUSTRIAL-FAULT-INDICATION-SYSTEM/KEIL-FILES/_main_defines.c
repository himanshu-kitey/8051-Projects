#include "_delay_ms.h"
#include "_lcd_headers.h"
#include "_main_headers.h"
_U8 x;

void delay_3()
{
	_delay_ms(3000);
}

void set_str()
{
	_lcd_stringData("Set Tmp");
}

void back_loop(_U8 u,_U8 *pass)
{
	for(x=0;x<u;x++)
		_write_data(pass[x]);
}

void sucess_str()
{
	_lcd_stringData("Sucess");
}

void pass_str()
{
	_lcd_stringData("Enter 5 Digt Pass : ");
}

void _lcd_2ndLine()
{
	_write_cmd(0xc0);
}

void _lcd_cmd()
{
	    _write_cmd(0x01);
	    _write_cmd(0x80);
}

	
