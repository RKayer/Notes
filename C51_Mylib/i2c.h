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
                                                                                         
//函数声明					 
void I2CStart(void);
void I2CStop(void);
void I2CACK(void);
void I2CNACK(void);
void I2CWaitAck(void);//等待从机应答IIC总线.
void I2CSendByte(uint8_t Data);//发送一个字节
uint8_t I2CReadByte(void);//读入一个字节并返回.
void WrToROM(uint8_t *Data, uint8_t Address, uint8_t Num);//向从机写数据
void RdFromROM(uint8_t *Data, uint8_t Address, uint8_t Num);//读取从机数据

/********************************************/



#endif
