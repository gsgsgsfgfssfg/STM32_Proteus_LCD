#include "lcd.h"

static uint8_t lcd_rows = 0, lcd_cols = 0;
static void lcd_setData(uint8_t data){
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
static void lcd_send(uint8_t data, uint8_t rs){
	HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin, rs & 0x01);
	lcd_setData(data >> 4);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	//HAL_Delay(1);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
	//HAL_Delay(1);
	lcd_setData(data & 0x0F);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	//HAL_Delay(1);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
	//HAL_Delay(1);
}
static void lcd_send_nibble(uint8_t data){
	lcd_setData(data >> 4);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1);
	//HAL_Delay(1);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
	//HAL_Delay(1);
}
static void lcd_cmd(uint8_t cmd){
	lcd_send(cmd,0);
}
static void lcd_data(uint8_t data){
	lcd_send(data,1);
}
void lcd_clear(){
	lcd_cmd(0x01);
	HAL_Delay(2);
}
void lcd_print(const char *s){
	while (*s) lcd_data((uint8_t)*s++);
}
void lcd_goto(uint8_t x, uint8_t y){
	if (x >= lcd_rows || y >= lcd_cols) return;
	static const uint8_t row_start[2] = { 0x00, 0x40 };
	lcd_cmd(0x80 | (row_start[y] + x));
}
void lcd_init(uint8_t rows, uint8_t cols){
	lcd_rows = rows;
	lcd_cols = cols;
	HAL_Delay(50);

	lcd_send_nibble(0x30); HAL_Delay(5);
	lcd_send_nibble(0x30); HAL_Delay(1);
	lcd_send_nibble(0x30); HAL_Delay(1);
	lcd_send_nibble(0x20); HAL_Delay(1);

	lcd_cmd(0x28);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	HAL_Delay(2);
}
