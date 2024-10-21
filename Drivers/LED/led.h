#ifndef __LED_H_
#define __LED_H_

#include "stm32f4xx.h"

void led_init(void);
void led_red_on(void);
void led_red_off(void);
void led_red_toggle(void);
void led_green_on(void);
void led_green_off(void);
void led_green_toggle(void);

#endif
