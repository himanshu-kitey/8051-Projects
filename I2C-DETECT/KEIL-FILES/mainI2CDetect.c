#include "i2cDetectHeader.h"
void main()
{
	i2cDetect();
}









/*
#include <reg51.h>
#include "types.h"
#include "lcd_headers.h"
#include "i2c_headers.h"
#include "dlyMs.h"
bit I2C_Write(u8 dat);
sbit SDA = P3^7; // Define SDA pin
sbit SCL = P3^6; // Define SCL pin

void main()
{
	u8 nDevices=0;	u8 ack;
	u8 address;	
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Scanning...");
	while(1){
	for(address=0;address<127;address++)
		{
			i2cStart();
			ack=I2C_Write((address<<1)|0);
			if(ack==0)
			{
				++nDevices;

				lcd_cmd(0xC0);
				lcd_string("I2C Device:");
				lcd_string("0x");
				HexLCD(address);
			}
			i2cStop();
			dlyMs(100);			
		}
		lcd_init();
		lcd_cmd(0x80);
		lcd_string("Devices Found:");
		lcd_cmd(0xC0);
		lcd_int(nDevices);
		while(1);
	}
}
*/





