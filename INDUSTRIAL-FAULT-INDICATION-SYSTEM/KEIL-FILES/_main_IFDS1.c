#include <reg51.h>
#include "_delay_ms.h"
#include "_keypad_headers.h"
#include "_main_headers.h"
#include "_lcd_headers.h"
#include "_i2c_headers.h"
#include "_spi_headers.h"
#include "_void_keyboard.h"

sbit gLED=P1^6;
sbit rLED=P1^7;

_U8 pass[5],i,set,v,cnt,wrong,time;
_U16 a;


_U8 sub_keypad()
{
	while(i=keypad('*'))
		 { 
			 if(i=='D' && v!=0)
			 {
				 lcd_cmd();
				 pass_str();
				 _lcd_2ndLine();
				 back_loop(--v,pass);
			 }  			
  else  if(v==5)
			 {
          if(i=='#') break;
         else return 1;		
			 }
  else  if(i=='*') return 0;				 
  else  if(i!='#' && i!='D')
		      {
		       pass[v++]=i;
		        _write_data(i);
	   	    }
			}
			 return 2;
}

void int0(void) interrupt 0
{
   	 if(wrong==3)
	   {
			lcd_cmd();
			_lcd_stringData("Wait Time:");	 
		 while(time)
		 {
			i=keypad(' ');
			if(i=='*') goto EXIT;

	     _lcd_2ndLine();			
			if(time==9)
			{
				_lcd_stringData("        ");
			_lcd_2ndLine();
			}
			_lcd_intData(time--);
			_lcd_stringData(" Secs");
			_delay_ms(900);
		}	
		wrong=0;
	  } 
	 
		PRO:	  lcd_cmd();
	  pass_str();
	 _lcd_2ndLine();
	 cnt=0;
	  v=0;
AGAIN: 
	       a=sub_keypad();				 
				 if(a==0) goto EXIT;
				 if(a==1) goto AGAIN;
	
	  for(i=0;i<v;i++)
	   {
		if(pass[i] != i2c_random_read(i))
		    break;
	   }
		 lcd_cmd();
		 if(i==5)
		 {
			 wrong=0;
			 gLED=1;
			 rLED=0;
			 _lcd_stringData("1.Change Current Pass");
			 _lcd_2ndLine();
			 _lcd_stringData("2.Change Set Tmp");	
		 v=keypad('A');
			 if(v=='1')
			 {
				 lcd_cmd();
				 pass_str();
			  _lcd_2ndLine();
				 cnt=v=0;
AGAIN1: 
				 a=sub_keypad();				 
				 if(a==0) goto EXIT;
				 if(a==1) goto AGAIN1;
			
  		 for(i=0;i<5;i++)
		   i2c_byte_write(i,pass[i]);
			    lcd_cmd();
				  sucess_str();
				  delay_3();
	    }
	else  if(v=='2')
	   {
REPEAT:
			   lcd_cmd();
				 set_str();
			   _lcd_2ndLine();
			   cnt=a=v=0;
SUPER:		 
			while(i=keypad('*'))
			{
				if(i=='D' && v!=0)
				{
					lcd_cmd();
				  set_str();
					_lcd_2ndLine();	
					back_loop(--v,pass);
				}	
			else	if(i=='*') goto EXIT;
			else	if(v>0 && i=='#') break;
		  else	if(v>3) goto SUPER;
		  else	if(i>='0' && i<='9')
				{
					 a=(a*10)+i-48;
					_write_data(i);
				  pass[v++]=i;
				}
			}
			  
     			if(a<=150)
			     {
				      for(i=0;i<3;i++)
						  i2c_byte_write(i+8,0xff);
              set=0;
						  for(i=0;i<v;i++)
						 {
							set=set*10 + (pass[i]-48);
						  i2c_byte_write(i+8,pass[i]);
						 }
			     }
					 else
					 {
						 lcd_cmd();
						 _lcd_stringData("Threshold Range");
						 _lcd_2ndLine();	
						 _lcd_stringData("Exceeded");
						 delay_3();
						 goto REPEAT;
					 }
		      lcd_cmd();
				  sucess_str();
					delay_3();
		 }
	 }
	   else
		 {
			 wrong++;
			 gLED=0;
			 rLED=1;
			 if(wrong==3)
			 {
				  lcd_cmd();
	        _lcd_stringData("YOU ARE BLOCKED");
				  _lcd_2ndLine();
				  _lcd_stringData("TRY AGAIN LATER");
				 delay_3();
         time=60;				 
				 goto EXIT;
			 }
			_lcd_stringData("Incorrect");
        delay_3();	
        goto PRO;		
			 }				 

EXIT:		
		   _lcd_cmd();   	
}

main()
{
	_F32 t;
	IE=0X81;
	IT0=1;
	_lcd_init();
	set=wrong=rLED=gLED=time=0;
	
	/*
//  Initialize below commented code once only
	
	for(i=1;i<7;i++)
	{
		i2c_byte_write(i-1,i+48);
	}
	for(i=1;i<3;i++)
	{
		i2c_byte_write(i-1+8,i+48);
	}
		
//  Note: If code size is exceeded. Then, Comment below code and run above code.
*/
  for(i=0;i<3;i++)
	{
		v=i2c_random_read(i+8);
		if(v==0xff) break;
	 set=set*10+(v-48);
  }
	while(1)
	{
		if(time)
		{
			_delay_ms(650);
			time--;
			if(time==0) 
				wrong=0;
		}	
		_lcd_init();
		t=fread_mcp3204_from_lm35();
    _write_cmd(0x80);
		_lcd_stringData("Temperature is :");
		_lcd_2ndLine();
		_lcd_floatData(t);
		if(t>set)
		{
			gLED=0; rLED=1;
		}
		else
		{
			gLED=1; rLED=0;
		}
    _delay_ms(300);
	} 
}





