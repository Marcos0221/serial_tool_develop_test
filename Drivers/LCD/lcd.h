#ifndef __LCD_H_
#define __LCD_H_

#include "stm32f4xx.h"                  // Device header

#define LCD_RES_Set() GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define LCD_RES_Clr() GPIO_ResetBits(GPIOC, GPIO_Pin_4)

#define LCD_DC_Set() GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define LCD_DC_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_2)

#define LCD_CS_Set() GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LCD_CS_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_13)

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#define NO_OPERATION            0x00    // 无操作
#define SWRESET                 0x01    // 软件复位
#define READ_DISPLAY_ID         0x04    // 读显示ID
#define READ_DISPLAY_STATUS     0x09    // 读显示状态
#define READ_DISPLAY_POWER      0x0A    // 读显示电源
#define READ_DISPLAY            0x0B    // 读显示
#define READ_DISPLAY_PIXEL      0x0C    // 读显示像素
#define READ_DISPLAY_IMAGE      0x0D    // 读显示图像
#define READ_DISPLAY_SIGNAL     0x0E    // 读显示信号
#define READ_DISPLAY_SD_RESULT  0x0F    // 读显示自检结果
#define SLEEP_IN                0x10    // 进入休眠模式
#define SLEEP_OUT               0x11    // 退出休眠模式
#define PART_MODE_ON            0x12    // 部分模式开启
#define PART_MODE_OFF           0x13    // 部分模式关闭
#define INVOFF                  0x20    // 显示反转关闭
#define INVON                   0x21    // 显示反转关闭
#define GAMSET                  0x26    // 显示反转开启
#define DISPOFF                 0x28    // 显示关闭
#define DISPON                  0x29    // 显示开启
#define CASET                   0x2A    // 列设置
#define RASET                   0x2B    // 行设置
#define RAMWR                   0x2C    // 内存写
#define RAMRD                   0x2E    // 内存读
#define PTLAR                   0x30    // 部分开始/结束地址设置
#define VSCRDEF                 0x33    // 垂直滚动定义
#define TEOFF                   0x34    // 行撕裂效果关闭
#define TEON                    0x35    // 行撕裂效果开启
#define MADCTL                  0x36    // 内存数据存取控制
#define VSCRSADD                0x37    // 垂直滚动开始地址
#define IDMOFF                  0x38    // 空闲模式关闭
#define IDMON                   0x39    // 空闲模式开启
#define COLMOD                  0x3A    // 接口像素格式
#define RAMWRC                  0x3C    // 内存连续写
#define RAMRDC                  0x3E    // 内存连续读
#define TESCAN                  0x44    // 设置泪损扫描线
#define RDTESCAN                0x45    // 获取扫描线
#define WRDISBV                 0x51    // 设置显示亮度
#define RDDISBV                 0x52    // 读显示亮度的值
#define WRCTRLD                 0x53    // 写控制显示
#define RDCTRLD                 0x54    // 读控制显示的值
#define WRCACE                  0x55    // 写内容适应的亮度控件和颜色增强 MNET
#define RDCABC                  0x56    // 读内容适应的亮度控件和颜色增强 MNET 的值
#define WRCABCMB                0x5E    // 写 CABC 最低亮度
#define RDCABCMB                0x5F    // 读 CABC 最低亮度的值
#define RDABCSDR                0x68    // 读取自动亮度控制自我诊断结果
#define RDID1                   0xDA    // 读 ID1
#define RDID2                   0xDB    // 读 ID2    
#define RDID3                   0xDC    // 读 ID3

void lcd_init(void);
void lcd_write_data8(uint8_t data);
void lcd_write_data(uint16_t data);
void lcd_write_reg(uint8_t data);
void lcd_write_bus(uint8_t data);
void lcd_address_set(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);
void lcd_fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_backlight_on(void);
void lcd_backlight_off(void);
void lcd_draw_rect(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height, uint16_t color);
void lcd_show_char(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
#endif
