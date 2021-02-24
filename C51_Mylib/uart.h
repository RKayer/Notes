
#ifndef _C51_UART_H
#define _C51_UART_H

#include <reg52.h>

#define uint8_t  unsigned char
#define uint16_t unsigned int

//�������ȫ������
extern uint8_t flag;        //���ڽ��ձ�־
extern uint8_t rev_data[20];  //��Ŵ��ڽ��յ�����
extern uint8_t rev_num;        //�洢���ݳ���

void Uart_Configuration(void);   //���ڳ�ʼ��
void sendDate(uint8_t dat);      //��������
void sendStr(uint8_t *string);   //�����ַ���


#endif
