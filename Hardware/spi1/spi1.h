#ifndef __SPI1_H_
#define __SPI1_H_

#include "stm32f4xx.h"

void spi1_init(void);
void spi1_write_byte(uint8_t byte);

#endif
