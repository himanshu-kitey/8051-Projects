#ifndef __LCD_HEADER_H__
#define __LCD_HEADER_H__

void _lcd_init();
void _write_cmd(_U8);
void _write_data(_U8);
void _lcd_stringData(_U8 *);
void _lcd_intData(_U8);
void _lcd_floatData(_F32);

#endif