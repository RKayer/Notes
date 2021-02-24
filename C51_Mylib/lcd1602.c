#include "lcd1602.h"

/**************Start of the Function about LCD1602**************/
/**
 * 判断LCD是否忙碌.
 * @param result 状态值.
 * @return 状态：1为忙碌，0为空闲.
 */
bit lcd_busy()
{
    bit result; //读状态
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    _nop_();
    result = (bit)(P0 & 0X80);
    LCD_EN = 0;
    return(result);
}

/**
 * 写入指令.
 * @param cmd 放入的命令.
 * @return 无.
 */
void lcd_wcmd(uint8_t cmd)
{
    while(lcd_busy());
    LCD_RS = 0;//选择发送命令
    LCD_RW = 0;//选择写入
    LCD_EN = 0;//使能清零
    _nop_();
    _nop_();
    LCD_DATA = cmd;//放入命令
    _nop_();//等待数据稳定
    LCD_EN = 1;//拉高电平
    _nop_();//保持时间
    LCD_EN = 0;//产生下降沿写入时序
}

/**
 * 写入数据.
 * @param dat 数据.
 * @return 无.
 */
void lcd_wdat(uint8_t dat)
{
    while(lcd_busy());
    LCD_RS = 1;//选择输入数据
    LCD_RW = 0;//选择写入
    LCD_EN = 0;//使能清零
    _nop_();
    _nop_();
    LCD_DATA = dat;//写入数据
    _nop_();
    LCD_EN = 1;//拉高电平
    _nop_();//保持时间
    LCD_EN = 0;//产生下降沿写入时序
}

/**
 * LCD初始化.
 * @param 无.
 * @return 无.
 */
void lcd_init()
{
    lcd_wcmd(0X38);//16*2显示，5*7点阵，8位数据
    lcd_wcmd(0X0C);//开显示，关光标
    lcd_wcmd(0X06);//写一个字符指针后地址指针加一
    lcd_wcmd(0X01);//清屏
}

/**
 * 计算显示位置.
 *	@param pos 相对位置.
 *	@return 实际显示位置.
 */
void lcd_pos(uint16_t pos)
{
    lcd_wcmd(pos | 0X80);
}
/**************End of the Function about LCD1602**************/