#ifndef _C51_I2C_H
#define _C51_I2C_H

#include <reg52.h>

#define uint8_t  unsigned char
#define uint16_t unsigned int

/********************************************/
#include <reg52.h>
#include <intrins.h>

#define I2CDelay() { _nop_(); \
                     _nop_(); \
                     _nop_(); \
                     _nop_(); \
                     _nop_(); }



sbit I2C_SCL = P3^2;
sbit I2C_SDA = P3^3;
                                                                                         
//��������					 
void I2CStart(void);
void I2CStop(void);
void I2CACK(void);
void I2CNACK(void);
void I2CWaitAck(void);//�ȴ��ӻ�Ӧ��IIC����.
void I2CSendByte(uint8_t Data);//����һ���ֽ�
uint8_t I2CReadByte(void);//����һ���ֽڲ�����.
void WrToROM(uint8_t *Data, uint8_t Address, uint8_t Num);//��ӻ�д����
void RdFromROM(uint8_t *Data, uint8_t Address, uint8_t Num);//��ȡ�ӻ�����

/********************************************/



#endif
