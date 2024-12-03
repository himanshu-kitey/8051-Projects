#ifndef __LCD_HEADERS_H__
#define __LCD_HEADERS_H__

#include "types.h"

void lcd_data(u8 d);
void lcd_cmd(u8 cmd);
void lcd_init(void);
void lcd_string(u8 *ptr);
void lcd_int(s8 n);
void lcd_float(f32 f);
void scroll_string(s8 *ptr);
void lcdDecToHex(u16 n);
#endif





/*
#ifndef __LCD_H__ 
#define __LCD_H__ 
#include "types.h" 
//primary drivers for HD44780 LCD controller declarations 
void WriteLCD(u8); 
void CmdLCD(u8); 
void CharLCD(u8); 
void InitLCD(void); 
//add more as required 
//secondary drivers for HD44780 LCD controller declarations 
void StrLCD(u8 *); 
void U16LCD(u16); 
void S16LCD(s16); 
void F32LCD(f32,u8); 
void BinLCD(u8 ); 
void HexLCD(u16); 
void BuildCGRAM(u8 *,u8); 
//add more as required 
#endif 

*/