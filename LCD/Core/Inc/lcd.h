#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx.h"
#include "main.h"

void lcd_clear();
void lcd_print(const char *s);
void lcd_goto(uint8_t x, uint8_t y);
void lcd_init(uint8_t rows, uint8_t cols);
#endif /* INC_LCD_H_ */
