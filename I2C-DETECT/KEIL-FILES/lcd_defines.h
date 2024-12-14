/* lcd_defines.h */
#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

//Defines for LCD Controller HD44780 Commands

#define CLEAR_LCD    				0x01
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