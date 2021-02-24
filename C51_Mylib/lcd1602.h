#ifndef _C51_LCD1602_H
#define _C51_LCD1602_H

#include <reg52.h>


/****************Begin*of*LCD****************************/
#include <reg52.h>
#include <intrins.h>

#define uint8_t  unsigned char
#define uint16_t unsigned int

sbit LCD_RS = P1^0;
sbit LCD_RW = P1^1;
sbit LCD_EN = P1^2;

#define LCD_DATA P0


//函数声明
bit lcd_busy();//判断LCD是否忙碌
void lcd_wcmd(uint8_t cmd);//写入指令
void lcd_wdat(uint8_t dat);//写入数据
void lcd_init();//LCD初始化
void lcd_pos(uint16_t pos); //显示位置
/****************End of LCD***************************/




#endif
