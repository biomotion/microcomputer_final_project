#include "stm32f4xx.h"
#include "stm324xg_lcd_sklin.h"


void show_welcome(void){
	LCD_Clear(WHITE);
	LCD_SetColors(RED, WHITE);
	LCD_SetFont(&Font24);
	LCD_DisplayStringAt(0, 0, "Welcome",CENTER_MODE);
}
