#include <reg51.h>
#include "dlyMs.h"
#include "types.h"
#include "lcd_headers.h"

#define LCD_DATA P0
sbit RS=P2^7;
sbit RW=P2^6;
sbit EN=P2^5;

void lcd_data(u8 d)
{
	LCD_DATA=d;
	RS=1;
	RW=0;
	EN=1;
	dlyMs(2);
	EN=0;
}

/*
//4-bit-mode-setting
void lcd_data(u8 d)
{
	LCD_DATA=(d&0xF0);						//LCD_DATA=d>>4;
	RS=1;
	RW=0;
	EN=1;
	dlyMs(2);											//dlyMs(1000);
	EN=0;
	
	LCD_DATA=((d<<4) & 0xF0);			//LCD_DATA=d&0x0F;
	RS=1;
	RW=0;
	EN=1;
	dlyMs(2);											//dlyMs(1000);
	EN=0;
}
*/

void lcd_cmd(u8 cmd)
{
	LCD_DATA=cmd;
	RS=0;
	RW=0;
	EN=1;
	dlyMs(2);
	EN=0;
}

/*
//4-bit-mode-setting
void lcd_cmd(u8 cmd)
{
	LCD_DATA=(cmd&0xF0);					//LCD_DATA=cmd>>4;
	RS=0;
	RW=0;
	EN=1;
	dlyMs(2);											//dlyMs(1000);
	EN=0;
	
	LCD_DATA=((cmd<<4)& 0xF0);		//LCD_DATA=cmd&0x0F;
	RS=0;
	RW=0;
	EN=1;
	dlyMs(2);											//dlyMs(1000);
	EN=0;
}
*/

/* 8-bit-mode-interfacing*/
void lcd_init(void)
{
	lcd_cmd(0x02);
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}

/*
//4-bit-mode-interfacing
void lcd_init(void)
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}
*/

void lcd_string(u8 *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
	}
}

void lcd_int(s8 n)
{
	s8 a[10],i=0;
	if(n<0)
	{
		lcd_data('.');
		n=-n;
	}
	do
	{
		a[i++]=n%10+48;
		n=n/10;
	}while(n);
	for(i;i>0;i--)
	lcd_data(a[i-1]);
}

void lcdDecToHex(u16 n) 			//n=127 / 0x7f 
{
	u8 a[4],t;
	s8 i=0; 
  if(n==0)
	{
		lcd_data('0'); 
  }    
  else 
  {
		while(n>0) 
		{
			t=n%16; 
			if(t>9) 
				t=(t-10)+'A'; 
			else 
				t=t+48; 
    a[i]=t; 
    n=n/16; 
    i++; 
		}   
		for(--i;i>=0;i--) 
			lcd_data(a[i]);    
   }    
}

