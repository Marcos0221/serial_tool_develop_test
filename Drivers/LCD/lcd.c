#include "lcd.h"
#include "delay.h"
#include "spi1.h"

void lcd_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

    LCD_CS_Set();
    LCD_RES_Set();
    LCD_DC_Set();

	// 打开背光
	lcd_backlight_on();

	// 复位
    LCD_RES_Clr();
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);
    // debug_printf("file: %s\tline:%d\nlcd_init", __FILE__, __LINE__);

    //************* Start Initial Sequence **********//
    lcd_write_reg(0x11);
    delay_ms(120);
    //************* Start Initial Sequence **********//
    lcd_write_reg(0x36);
    lcd_write_data8(0x00);      // 设置显示方向

    lcd_write_reg(0x3A);
    lcd_write_data8(0x05);

    lcd_write_reg(0xB2);
    lcd_write_data8(0x0C);
    lcd_write_data8(0x0C);
    lcd_write_data8(0x00);
    lcd_write_data8(0x33);
    lcd_write_data8(0x33);

    lcd_write_reg(0xB7);
    lcd_write_data8(0x35);

    lcd_write_reg(0xBB);
    lcd_write_data8(0x32); // Vcom=1.35V

    lcd_write_reg(0xC2);
    lcd_write_data8(0x01);

    lcd_write_reg(0xC3);
    lcd_write_data8(0x15); // GVDD=4.8V  颜色深度

    lcd_write_reg(0xC4);
    lcd_write_data8(0x20); // VDV, 0x20:0v

    lcd_write_reg(0xC6);
    lcd_write_data8(0x0F); // 0x0F:60Hz

    lcd_write_reg(0xD0);
    lcd_write_data8(0xA4);
    lcd_write_data8(0xA1);

    lcd_write_reg(0xE0);
    lcd_write_data8(0xD0);
    lcd_write_data8(0x08);
    lcd_write_data8(0x0E);
    lcd_write_data8(0x09);
    lcd_write_data8(0x09);
    lcd_write_data8(0x05);
    lcd_write_data8(0x31);
    lcd_write_data8(0x33);
    lcd_write_data8(0x48);
    lcd_write_data8(0x17);
    lcd_write_data8(0x14);
    lcd_write_data8(0x15);
    lcd_write_data8(0x31);
    lcd_write_data8(0x34);

    lcd_write_reg(0xE1);
    lcd_write_data8(0xD0);
    lcd_write_data8(0x08);
    lcd_write_data8(0x0E);
    lcd_write_data8(0x09);
    lcd_write_data8(0x09);
    lcd_write_data8(0x15);
    lcd_write_data8(0x31);
    lcd_write_data8(0x33);
    lcd_write_data8(0x48);
    lcd_write_data8(0x17);
    lcd_write_data8(0x14);
    lcd_write_data8(0x15);
    lcd_write_data8(0x31);
    lcd_write_data8(0x34);
    lcd_write_reg(0x21);

    lcd_write_reg(0x29);
}

/**
 * 向总线写数据
*/
void lcd_write_bus(uint8_t data)
{
    // LCD_CS_Set();
    LCD_CS_Clr();
	spi1_write_byte(data); 
     LCD_CS_Set();
}

/**
 * spi写入一个字节
 */
void lcd_write_data8(uint8_t data)
{
    lcd_write_bus(data);
}

/**
 * spi写入两个字节
 */
void lcd_write_data(uint16_t data)
{
    lcd_write_bus(data>>8);
    lcd_write_bus(data);
}

/**
 * 写命令
 */
void lcd_write_reg(uint8_t data)
{
    LCD_DC_Clr(); // 写命令
    lcd_write_bus(data);
    LCD_DC_Set();
}

void lcd_address_set(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    lcd_write_reg(0x2A);
    lcd_write_data(startX);
    lcd_write_data(endX);
    lcd_write_reg(0x2B);
    lcd_write_data(startY + 20);
    lcd_write_data(endY + 20);
    lcd_write_reg(0x2C);
}

void lcd_fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    uint16_t i, j;
    lcd_address_set(xsta, ysta, xend - 1, yend - 1); // 设置显示范围
    for (i = ysta; i < yend; i++)
    {
        for (j = xsta; j < xend; j++)
        {
            lcd_write_data(color);
        }
    }
}

void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_address_set(x, y, x, y);
    lcd_write_data(color);
}

// 绘制矩形
void lcd_draw_rect(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height, uint16_t color)
{
	uint16_t endx=startX+width>=240?240:startX+width;
	uint16_t endy=startY+height>=280?280:startY+height;
	lcd_fill(startX, startY, endx, endy, color);
}

/**
 * 打开 LCD 背光
*/
void lcd_backlight_on()
{
	GPIO_SetBits(GPIOF, GPIO_Pin_6);
}

/**
 * 关闭 LCD 背光
*/
void lcd_backlight_off()
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_6);
}
