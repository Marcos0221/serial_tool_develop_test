﻿#include "led.h"

void led_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void led_red_on()
{
	GPIO_SetBits(GPIOF, GPIO_Pin_9);
}

void led_red_off()
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_9);
}

void led_red_toggle()
{
	GPIOF->ODR^=GPIO_Pin_9;
}

void led_green_on()
{
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
}

void led_green_off()
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_10);
}

void led_green_toggle()
{
	GPIOF->ODR^=GPIO_Pin_10;
}
