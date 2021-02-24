#include "ex_interrupt.h"
uint8_t status = DEFAULT;
/**
 *@brief  外部中断0初始化
 * @param mode 1:边沿触发 0：电平触发
 * @return 无
 *
*/
void INT0Config(bit mode)
{
	EA = ENABLE;   //开全局中断
	EX0 = ENABLE;  //外部中断0开
	IT0 = mode; //触发模式，1：边沿 0：电平
}



void INT1Config(bit mode)
{
	EA = ENABLE;   //开全局中断
	EX1 = ENABLE;  //外部中断1开
	IT1 = mode; //触发模式，1：边沿 0：电平
}


/**
 *
 *外部中断0服务函数
*/

void INT0_SER() interrupt 0
{
	delay_ms(4);  
	if(! KEY_INT0)
	{
		status = ENTER; 
		//业务代码
	}
}

/**
 *
 *外部中断1服务函数
*/

void INT1_SER() interrupt 2
{
	delay_ms(4);  
	if(! KEY_INT1)
	{
		status = CHANGE;
		//业务代码
	}
}