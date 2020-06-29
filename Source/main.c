#include "stm32f4xx.h"
#include "stm324xg_lcd_sklin.h"
#include "screen_control.h"
#include <stdio.h>

void stm32f4_Hardware_Init(void);

int main(void){
	stm32f4_Hardware_Init();
	// Initilize GPIO
	
	// Show Welcome Message
	LCD_Init();
	LCD_DisplayOn();
	
  LCD_Clear(RED);
	
	// Loop for Playing
	
}
