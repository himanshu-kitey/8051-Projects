#include <reg51.h>
#include "types.h"
#include "mainHeaders.h"
#include "dlyMs.h"

sbit CLK=P1^0;
sbit Din=P1^1;
sbit Dout=P1^2;
sbit CS=P1^3;

f32 fread_mcp3204_from_lm35()
{
	u8 i;
	u16 adc_value=0;
	f32 analog_reading;
	CLK=Din=Dout=CS=1;
	CS=0;
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
	CS=1;	
	analog_reading = adc_value * (5.0/4096);
	return analog_reading*100;
}






