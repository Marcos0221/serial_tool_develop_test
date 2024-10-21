#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "usart_1.h"
#include "stdio.h"
#include "spi1.h"

int main(void)
{
	// ***** 外设层初始化 *****
	delay_init(168);
	// led_init();
	usart1_init(115200);
	spi1_init();
		
	// ***** 驱动层初始化 *****
	lcd_init();
	lcd_draw_rect(0, 0, 100, 100, WHITE);

	while(1){

	}
}

