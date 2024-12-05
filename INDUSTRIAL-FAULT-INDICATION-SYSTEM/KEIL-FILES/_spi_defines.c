#include <reg51.h>
#include "_types.h"
#include "_main_headers.h"
#include "_delay_ms.h"

sbit CLK=P1^0;
sbit Din=P1^1;
sbit Dout=P1^2;
sbit _CS=P1^3;

_F32 fread_mcp3204_from_lm35()
{
	_U8 i;
 _U16 adc_value=0;
 _F32 analog_reading;
	CLK=Din=Dout=_CS=1;
	_CS=0;
	CLK =0; CLK=1;
	CLK =0; CLK=1;
	CLK =0; CLK=1;
	CLK =0; 
	Din=0;
	CLK=1;
	CLK =0; CLK=1;
	CLK =0; CLK=1;
	CLK =0; CLK=1;
	for(i=0;i<12;i++)
	{
		CLK=0; 
		CLK=1;
		if(Dout) adc_value |= (1<<(11-i));
	}
	_CS=1;	
	analog_reading = adc_value * (5.0/4096);
	return analog_reading*100;
}






