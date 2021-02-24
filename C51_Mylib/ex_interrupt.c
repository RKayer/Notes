#include "ex_interrupt.h"
uint8_t status = DEFAULT;
/**
 *@brief  �ⲿ�ж�0��ʼ��
 * @param mode 1:���ش��� 0����ƽ����
 * @return ��
 *
*/
void INT0Config(bit mode)
{
	EA = ENABLE;   //��ȫ���ж�
	EX0 = ENABLE;  //�ⲿ�ж�0��
	IT0 = mode; //����ģʽ��1������ 0����ƽ
}



void INT1Config(bit mode)
{
	EA = ENABLE;   //��ȫ���ж�
	EX1 = ENABLE;  //�ⲿ�ж�1��
	IT1 = mode; //����ģʽ��1������ 0����ƽ
}


/**
 *
 *�ⲿ�ж�0������
*/

void INT0_SER() interrupt 0
{
	delay_ms(4);  
	if(! KEY_INT0)
	{
		status = ENTER; 
		//ҵ�����
	}
}

/**
 *
 *�ⲿ�ж�1������
*/

void INT1_SER() interrupt 2
{
	delay_ms(4);  
	if(! KEY_INT1)
	{
		status = CHANGE;
		//ҵ�����
	}
}