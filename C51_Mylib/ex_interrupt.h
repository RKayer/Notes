#ifndef _C51_MATRIX_KEY_H
#define _C51_MATRIX_KEY_H

#include <reg52.h>
#include "delay.h"

#define uint8_t  unsigned char
#define uint16_t unsigned int
#define ENABLE 1
#define DISABLE 0
#define SET 1
#define RESET 0

#define EDGE_TRIGGERED 1   //���ش���
#define LEVEL_TRIGGERED 0  //��ƽ����

/******************ҵ�����������****************/
#define ENTER 1
#define CHANGE 2
#define DEFAULT 3

extern uint8_t status;
/******************ҵ�����������***************/
sbit KEY_INT0 = P3^ 2;
sbit KEY_INT1 = P3^ 3;



//��ʼ����������
void INT0Config(bit mode);   //�ⲿ�ж�0��ʼ������,mode:����ģʽѡ��1������ 0����ƽ
void INT1Config(bit mode);   //�ⲿ�ж�1��ʼ������,mode:����ģʽѡ��1������ 0����ƽ

#endif

