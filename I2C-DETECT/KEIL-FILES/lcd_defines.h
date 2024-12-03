/* lcd_defines.h */
#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

//Defines for LCD Controller HD44780 Commands

														//base commands
#define CLEAR_LCD    				0x01   //00000001 
#define RET_CUR_TO_HOME     0x02
#define SET_CUR_MOV_DIR     0x04  
#define DISP_OFF            0x08              
#define DISP_ON_CUR_OFF     0x0C   
#define DISP_ON_CUR_ON      0x0E   
#define DISP_ON_CUR_BLINK   0x0F 
#define MOV_CUR_SHIFT_DISP  0x10 
#define SET_INTERFACE_LEN   0x30 
#define CUR_TO_DDRAM_START  0x80
#define CUR_TO_CGRAM_START  0x40
#define POLL_BUSY_FLAG      0x80 
#define SET_CUR_LINE1       0x80 
#define SET_CUR_LINE2       0xC0


#endif

/*
#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

#define CLEAR_LCD 0x01
#define RET_CUR_HOME 0x02
#define SHIFT_DISP_LEFT 0x06
#define SHIFT_DISP_RIGHT 0x07
#define DSP_OFF 0x08
#define DSP_ON_CUR_OFF 0x0C
#define DSP_ON_CUR_ON 0x0e
#define DSP_ON_CUR_BLINK 0x0f
#define MODE_8BIT_1LINE 0x30
#define MODE_8BIT_2LINE 0x38
#define MODE_4BIT_1LINE 0x20
#define MODE_4BIT_2LINE 0x28
#define GOTO_LINE1_POSO 0x80
#define GOTO_LINE2_POSO 0xC0
#define GOTO_LINE3_POSO 0x94
#define GOTO_LINE4_POSO 0xD4
#define GOTO_CGRAM_START 0x40
#define SHIFT_CUR_LEFT 0x10
#define SHIFT_CUR_RIGHT 0x14
#define LCD_D0 8
#define LCD_D1 9
#define LCD_D2 10
#define LCD_D3 11
#define LCD_D4 12
#define LCD_D5 13
#define LCD_D6 14
#define LCD_D7 15
#define LCD_RS 17
#define LCD_RW 18
#define LCD_EN 19
#endif
*/