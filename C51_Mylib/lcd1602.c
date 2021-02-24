#include "lcd1602.h"

/**************Start of the Function about LCD1602**************/
/**
 * �ж�LCD�Ƿ�æµ.
 * @param result ״ֵ̬.
 * @return ״̬��1Ϊæµ��0Ϊ����.
 */
bit lcd_busy()
{
    bit result; //��״̬
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    _nop_();
    result = (bit)(P0 & 0X80);
    LCD_EN = 0;
    return(result);
}

/**
 * д��ָ��.
 * @param cmd ���������.
 * @return ��.
 */
void lcd_wcmd(uint8_t cmd)
{
    while(lcd_busy());
    LCD_RS = 0;//ѡ��������
    LCD_RW = 0;//ѡ��д��
    LCD_EN = 0;//ʹ������
    _nop_();
    _nop_();
    LCD_DATA = cmd;//��������
    _nop_();//�ȴ������ȶ�
    LCD_EN = 1;//���ߵ�ƽ
    _nop_();//����ʱ��
    LCD_EN = 0;//�����½���д��ʱ��
}

/**
 * д������.
 * @param dat ����.
 * @return ��.
 */
void lcd_wdat(uint8_t dat)
{
    while(lcd_busy());
    LCD_RS = 1;//ѡ����������
    LCD_RW = 0;//ѡ��д��
    LCD_EN = 0;//ʹ������
    _nop_();
    _nop_();
    LCD_DATA = dat;//д������
    _nop_();
    LCD_EN = 1;//���ߵ�ƽ
    _nop_();//����ʱ��
    LCD_EN = 0;//�����½���д��ʱ��
}

/**
 * LCD��ʼ��.
 * @param ��.
 * @return ��.
 */
void lcd_init()
{
    lcd_wcmd(0X38);//16*2��ʾ��5*7����8λ����
    lcd_wcmd(0X0C);//����ʾ���ع��
    lcd_wcmd(0X06);//дһ���ַ�ָ����ַָ���һ
    lcd_wcmd(0X01);//����
}

/**
 * ������ʾλ��.
 *	@param pos ���λ��.
 *	@return ʵ����ʾλ��.
 */
void lcd_pos(uint16_t pos)
{
    lcd_wcmd(pos | 0X80);
}
/**************End of the Function about LCD1602**************/