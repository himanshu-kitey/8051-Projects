#include "types.h"
#include "i2c_defines.h"
#include "dlyMs.h"
#include "lcd_headers.h"

/* 	Routine to issue start event/condition. */
void i2cStart(void)
{
	SCL=1;						//Default status of SDA line can be avoided.
	SDA=1;						//Default status of SCL line can be avoided.
	SDA=0;						//Pull down sda from high to low issues start event.
}

/* 	Routine to issue Stop event/condition. */
void i2cStop(void)
{
  SCL=0;						//To change status of SDA ,SCL is made low during communication.
  SDA=0;						//Now SCL is made low.
  SCL=1;						//SCL line is released.
  SDA=1;						//SDA is raised from low to high to issue stop condition.
}

bit I2C_Write(u8 dat) 			//for I2C Detect
{
    u8 i;     bit ack;
    for(i=0;i<8;i++) 
		{
			SCL = 0;							// Clock low
      SDA=(dat>>(7-i))&1;  	// Send each bit, MSB first
      SCL = 1;             	// Clock high               
    }
    //For checking ACK bit
		SCL=0;    						// Clock low
    SDA=1;  							// Release SDA line for ACK
    SCL=1;  							// Clock high
		dlyMs(10);
    ack=SDA;  					// Read ACK bit
    SCL=0;    					// Clock low
    return ack;  					// Return ACK bit
}

void i2cDetect(void)
{
	u8 nDevices=0;	u8 address=0;
	u8 ack;
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Scanning...");
	lcd_cmd(0xC0);
	lcd_string("I2C Device:");
	lcd_string("0x");
	lcdDecToHex(address);
	while(1)
	{
		for(address=0;address<127;address++)
		{
			i2cStart();
			ack=I2C_Write((address<<1)|0);
			if(ack==0)
			{
				++nDevices;
				lcd_cmd(0xC0);
				lcd_string("I2C Devices:");
				lcd_string("0x");
				lcdDecToHex(address);
				dlyMs(1000);
			}/*
			else if(ack==4)
			{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string("Unknown Error");
				lcd_cmd(0xC0);
				lcd_string("at:0x");
				lcdDecToHex(address);
			}*/
			i2cStop();
			dlyMs(100);			
		}
		if(nDevices==0)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("No I2C Device");
			lcd_cmd(0xC0);
			lcd_string("Found");
		}
		else
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("Devices Found:");
			lcd_int(nDevices);
			lcd_cmd(0xC0);
			lcd_string("Scan Completed");
		}
			while(1);
	}
}
