#include "i2c.h"
#include "delay.h"
uint8_t AddRd = 0XA1;
uint8_t AddWr = 0XA0;

/**************Start of the Function about IIC**************/

/**
 * @brief 产生I2C起始信号
 * @callsubfunc I2CDelay 5微秒左右延时
 * @return 无
 */
void I2CStart(void)
{
    I2C_SCL = 1; //时钟总线为高电平
    I2C_SDA = 1; //数据总线为高电平
    I2CDelay(); //延时，起始条件建立时间
    I2C_SDA = 0; //拉低数据总线，产生电平跳变
    I2CDelay();  //延时，起始条件保持时间
    I2C_SCL = 0; //拉低时钟总线，允许数据变化
}

/**
 * @brief 产生I2C停止信号
 * @callsubfunc I2CDelay 5微秒左右延时
 * @return 无
 */
void I2CStop(void)
{
    I2C_SCL = 0; //时钟总线为低电平
    I2C_SDA = 0; //数据总线为低电平
    I2CDelay();  //延时，停止条件建立
    I2C_SCL = 1; //拉高时钟总线
    I2CDelay();  //延时，总线释放
    I2C_SDA = 1; //数据总线跳为高电平
    I2CDelay();  //延时，为下一次做准备
    I2C_SCL = 0; //拉低时钟总线，允许数据变化
}

/**
 * @brief 发送应答位
 * @callsubfunc I2CDelay 5微秒左右延时
 * @return 无
 */
void I2CACK(void)
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2CDelay();
    I2C_SCL = 0;
    I2C_SDA = 1;
}

/**
 * @brief 发送非应答位
 * @callsubfunc I2CDelay 5微秒左右延时
 * @return 无
 */
void I2CNACK(void)
{
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2CDelay();
    I2C_SCL = 0;
    I2C_SDA = 0;
}

/**
 * @brief 等待从机应答IIC总线.
 * @param i 软件控制等待时间，防止死机.
 * @return 无
 */
void I2CWaitAck(void)
{
    uint8_t i = 0;
    I2C_SCL = 1;
    I2CDelay();
    while(I2C_SDA == 1 && i < 250)
    {
        i ++;
    }
    I2C_SCL = 0;
}

/**
 * @brief 主机发送一个字节数据到IIC总线
 * @param Data 待发送的字节
 * @param mask 位探查标志
 * @return 无
 */
void I2CSendByte(uint8_t Data)
{
	uint8_t mask = 0x80;
	for (mask = 0x80; mask != 0; mask >>= 1)
	{
	    I2C_SCL = 0;          //允许数据变化，进行一次数据传输
		I2CDelay();
		I2C_SDA = (mask & Data) ? 1 : 0;
		I2CDelay();
        I2C_SCL = 1;          //拉高SCL
        I2CDelay();
	}
	I2C_SCL = 0;              //再拉低SCL，完成位周期
}


/**
 * @brief 读取IIC总线上的数据
 * @param mask 位探查标志
 * @return Data 读取的数据
 */
uint8_t I2CReadByte(void)
{
    uint8_t mask = 0x80, Data = 0x00;
    I2C_SDA = 1;               //主机释放SDA
	for (mask = 0x80; mask != 0; mask >>= 1)
	{
	    I2C_SCL = 1;          //不允许数据变化，读取数据
		I2CDelay();
		Data |= (I2C_SDA ? mask : 0x00); //读取SDA的值，并置位data响应位
		I2CDelay();
        I2C_SCL = 0;          //拉低SCL，为下一次数据读取做准备
        I2CDelay();
	}
	return Data;
}

/**
 * @brief 主机向从机写入数据
 * @param Data 待写入的数据
 * @param Address 写入的地址 24c02：0x00-0xff
 * @param Num 字节数
 * @return 无
 */
void WrToROM(uint8_t *Data, uint8_t Address, uint8_t Num)
{
    uint8_t i;
    uint8_t * PData;
    PData=Data;
    for(i = 0; i < Num; i ++)
    {
        I2CStart();               //发送起始信号
        I2CSendByte(AddWr);       //发送控制字节
        I2CWaitAck();             //等待从机响应
        I2CSendByte(Address + i); //写入存储地址0X00-0XFF
        I2CWaitAck();             //等待从机响应
        I2CSendByte(*(PData + i));//写数据
        I2CWaitAck();             //等待从机响应
        I2CStop();                //发送停止信号
        I2CDelay();
		delay_ms(10);
    }
	
}

/**
 * @brief 主机读取从机数据
 * @param Data 数据临时存储
 * @param Address 读取的地址 24c02：0x00-0xff
 * @param Num 读取字节数
 * @return 无
 */
void RdFromROM(uint8_t *Data, uint8_t Address, uint8_t Num)
{
    uint8_t i;
    uint8_t * PData;
    PData = Data;
    for(i = 0; i < Num; i ++)
    {
        I2CStart();              //发送起始信号
        I2CSendByte(AddWr);      //发送控制字节，写地址找芯片
        I2CWaitAck();            //等待应答
        I2CSendByte(Address + i);//写入存储地址
        I2CWaitAck();            //等待从机应答
		
        I2CStart();              //发送起始信号
        I2CSendByte(AddRd);      //发送控制字节，找芯片/读
        I2CWaitAck();            //等待应答
        * (PData + i) = I2CReadByte();//读数据
        I2C_SCL = 0;             //拉低SCL，数据可改变，为读取下一位数据作准备
        I2CNACK();               //读完该字节，无需发数据
        I2CStop();               //停止信号
		delay_ms(10);
    }
}
/**************END of the Function about IIC**************/