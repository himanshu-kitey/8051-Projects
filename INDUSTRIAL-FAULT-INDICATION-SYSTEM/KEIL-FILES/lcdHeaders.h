#ifndef __LCD_HEADER_H__
#define __LCD_HEADER_H__
#include "types.h"


void lcd_init(void);
void write_cmd(u8);
void write_data(u8);
void lcd_stringData(u8 *);
void lcd_intData(u8);
void lcd_floatData(f32);

#endif