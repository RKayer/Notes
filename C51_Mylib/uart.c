
#include "uart.h"

uint8_t flag = 0;        //串口接收标志
uint8_t rev_data[20] = {0};  //存放串口接收的数据
uint8_t rev_num  = 0;        //存储数据长度

/**
 * @brief 串口初始化
 * @param 无
 * @return 无
 */
void Uart_Configuration(void)  
{
    TMOD |= 0x20;    //设置计数器1的工作方式2
    TH1 = 0xf3;	     //设置计数器1的初值，决定波特率
    TL1 = 0xf3;	     //设置计数器1的初值，决定波特率,0xfd:9600
    PCON = 0x00;     //波特率倍增  0x00不加倍	 0x80加倍
    SCON = 0x50;	 //设置工作方式1 开启接受允许
    EA = 1;		     //开启总中断
    ES = 1;			 //开启串口接受中断
    TR1 = 1;		 //计数器1开始运行
}

/**
 * @brief 串口发送一个字符数据
 * @param dat 待发送的数据
 * @return 无
 */
void sendDate(uint8_t dat)
{
    SBUF = dat;		  //接收到的数据放入发送缓存器发送
    while(!TI);       //等待发送数据完成，TI标志位会置1
    TI = 0;			  //清除发送完成标志位
}

/**
 * @brief 串口发送字符串
 * @param string 待发送的字符串
 * @return 无
 */
void sendStr(uint8_t *string)
{
	uint8_t *str = string;
	ES = 0;                  //关闭接收中断
	while(* str)
	{
		sendDate(*str);
		str ++;
	}
	ES = 1;                 //打开接收中断
}

 
/*中断函数*/
void Uart() interrupt 4 
{
    if (RI)
    {
		if(! flag)
		{
			RI = 0;
			rev_data[rev_num ++] = SBUF;
			if(rev_data[rev_num] >= 2){
				if(rev_data[rev_num - 2] == '\r' && rev_data[rev_num - 1] == '\n')
				{
					flag = 1;
					rev_data[rev_num] = 0;   //加入字符串结尾标识符'\0'
				}
			}
		}
	}
	
	if (TI)
	{
		TI = 0;
	}
	
}