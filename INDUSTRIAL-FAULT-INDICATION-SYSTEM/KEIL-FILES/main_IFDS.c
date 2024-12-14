#include <reg51.h>
#include "dlyMs.h"
#include "keypadHeaders.h"
#include "mainHeaders.h"
#include "lcdHeaders.h"
#include "i2cHeaders.h"
#include "spiHeaders.h"
#include "types.h"

sbit gLED=P1^6;
sbit rLED=P1^7;

u8 pass[5],i;
u8 set;
u8 v;
u8 cnt;
u8 wrong;
u8 time;
u16 a;
u8 sub_keypad()
{
	while(i=keypad('*'))
		 { 
			 if(i=='D' && v!=0)
			 {
				 lcd_cmd();
				 pass_str();
				 lcd_2ndLine();
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
		       write_data(i);
	   	    }
			}
			 return 2;
}
void int0(void) interrupt 0
{
   	 if(wrong==3)
	   {
			lcd_cmd();
			lcd_stringData("Wait Time:");	 
		 while(time)
		 {
			i=keypad(' ');
			if(i=='*') goto EXIT;

	    lcd_2ndLine();			
			if(time==9)
			{
				lcd_stringData("        ");
				lcd_2ndLine();
			}
			lcd_intData(time--);
			lcd_stringData(" Secs");
			dlyMs(900);
		}	
		wrong=0;
	  } 
	 
		PRO:	  lcd_cmd();
	  pass_str();
	  lcd_2ndLine();
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
			 lcd_stringData("1-Change Pass");
			 lcd_2ndLine();
			 lcd_stringData("2-Change Set Tmp");	
			 v=keypad('A');
			 if(v=='1')
			 {
				 lcd_cmd();
				 pass_str();
			   lcd_2ndLine();
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
				 lcd_2ndLine();
			   cnt=a=v=0;
SUPER:		 
			while(i=keypad('*'))
			{
				if(i=='D' && v!=0)
				{
					lcd_cmd();
				  set_str();
					lcd_2ndLine();
					back_loop(--v,pass);
				}
				
			else	if(i=='*') goto EXIT;
			else	if(v>0 && i=='#') break;
		  else	if(v>3) goto SUPER;
		  else	if(i>='0' && i<='9')
				{
					 a=(a*10)+i-48;
					 write_data(i);
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
						 lcd_stringData("Threshold Range");
						 lcd_2ndLine();
						 lcd_stringData("Exceeded");
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
	        lcd_stringData("YOU ARE BLOCKED");
				  lcd_2ndLine();
				  lcd_stringData("TRY AGAIN LATER");
					delay_3();
          time=60;				 
				 goto EXIT;
			 }
			 lcd_stringData("Incorrect");
			 delay_3();	
       goto PRO;		
			 }				 

EXIT:		
		   lcd_cmd();   	
}

main()
{
	f32 t;
	IE=0X81;
	IT0=1;
	lcd_init();
	
	set=0;
	wrong=0;
	rLED=0;
	gLED=0;
	time=0;

//  Initialize below commented code once only

	/*
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
			dlyMs(650);
			time--;
			if(time==0) 
			wrong=0;
		}	
			t=fread_mcp3204_from_lm35();
			//write_cmd(0x80);
		//lcd_stringData("Temperature is :");
			write_cmd(0x85);
			lcd_floatData(t);
		if(t>set)
		{
			gLED=0;
			rLED=1;
		}
		else
		{
			gLED=1;
			rLED=0;
		}
		dlyMs(300);
	} 
}



/*

#include <reg51.h>
#include "dlyMs.h"
#include "keypadHeaders.h"
#include "mainHeaders.h"
#include "lcdHeaders.h"
#include "i2cHeaders.h"
#include "spiHeaders.h"

sbit gLED=P1^6;
sbit rLED=P1^7;

u8 pass[5],i,set,v,cnt,wrong,time;
u16 a;


u8 sub_keypad()
{
	while(i=keypad('*'))
		 { 
			 if(i=='D' && v!=0)
			 {
				 lcd_cmd();
				 pass_str();
				 lcd_2ndLine();
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
		        write_data(i);
	   	    }
			}
			 return 2;
}

void int0(void) interrupt 0
{
   	 if(wrong==3)
	   {
			lcd_cmd();
			lcd_stringData("Wait Time:");	 
		 while(time)
		 {
			i=keypad(' ');
			if(i=='*') goto EXIT;

	    lcd_2ndLine();			
			if(time==9)
			{
			lcd_stringData("        ");
			lcd_2ndLine();
			}
			lcd_intData(time--);
			lcd_stringData(" Secs");
			delay_ms(900);
		}	
		wrong=0;
	  } 
	 
		PRO:	  lcd_cmd();
	  pass_str();
	 lcd_2ndLine();
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
			 lcd_stringData("1.Change Current Pass");
			 lcd_2ndLine();
			 lcd_stringData("2.Change Set Tmp");	
		 v=keypad('A');
			 if(v=='1')
			 {
				 lcd_cmd();
				 pass_str();
			  lcd_2ndLine();
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
			   lcd_2ndLine();
			   cnt=a=v=0;
SUPER:		 
			while(i=keypad('*'))
			{
				if(i=='D' && v!=0)
				{
					lcd_cmd();
				  set_str();
					lcd_2ndLine();	
					back_loop(--v,pass);
				}	
			else	if(i=='*') goto EXIT;
			else	if(v>0 && i=='#') break;
		  else	if(v>3) goto SUPER;
		  else	if(i>='0' && i<='9')
				{
					 a=(a*10)+i-48;
					write_data(i);
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
						 lcd_stringData("Threshold Range");
						 lcd_2ndLine();	
						 lcd_stringData("Exceeded");
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
	        lcd_stringData("YOU ARE BLOCKED");
				  lcd_2ndLine();
				  lcd_stringData("TRY AGAIN LATER");
				 delay_3();
         time=60;				 
				 goto EXIT;
			 }
			lcd_stringData("Incorrect");
        delay_3();	
        goto PRO;		
			 }				 

EXIT:		
		   lcd_cmd();   	
}

main()
{
	f32 t;
	IE=0X81;
	IT0=1;
	lcd_init();
	set=wrong=rLED=gLED=time=0;
	
//
//  Initialize below commented code once only
//	
//	for(i=1;i<7;i++)
//	{
//		i2c_byte_write(i-1,i+48);
//	}
//	for(i=1;i<3;i++)
//	{
//		i2c_byte_write(i-1+8,i+48);
//	}
//		
//  Note: If code size is exceeded. Then, Comment below code and run above code.
//
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
			dlyMs(650);
			time--;
			if(time==0) 
				wrong=0;
		}	
		lcd_init();
		t=fread_mcp3204_from_lm35();
    write_cmd(0x80);
		lcd_stringData("Temperature is :");
		lcd_2ndLine();
		lcd_floatData(t);
		if(t>set)
		{
			gLED=0; rLED=1;
		}
		else
		{
			gLED=1; rLED=0;
		}
    dlyMs(300);
	} 
}

*/