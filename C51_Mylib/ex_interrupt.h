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

#define EDGE_TRIGGERED 1   //边沿触发
#define LEVEL_TRIGGERED 0  //电平触发

/******************业务参量声明区****************/
#define ENTER 1
#define CHANGE 2
#define DEFAULT 3

extern uint8_t status;
/******************业务参量声明区***************/
sbit KEY_INT0 = P3^ 2;
sbit KEY_INT1 = P3^ 3;



//初始化函数声明
void INT0Config(bit mode);   //外部中断0初始化函数,mode:触发模式选择，1：边沿 0：电平
void INT1Config(bit mode);   //外部中断1初始化函数,mode:触发模式选择，1：边沿 0：电平

#endif

