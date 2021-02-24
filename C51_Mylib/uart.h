
#ifndef _C51_UART_H
#define _C51_UART_H

#include <reg52.h>

#define uint8_t  unsigned char
#define uint16_t unsigned int

//相关数据全局声明
extern uint8_t flag;        //串口接收标志
extern uint8_t rev_data[20];  //存放串口接收的数据
extern uint8_t rev_num;        //存储数据长度

void Uart_Configuration(void);   //串口初始化
void sendDate(uint8_t dat);      //发送数据
void sendStr(uint8_t *string);   //发送字符串


#endif
