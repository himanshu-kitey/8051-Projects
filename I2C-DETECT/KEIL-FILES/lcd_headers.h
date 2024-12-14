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
