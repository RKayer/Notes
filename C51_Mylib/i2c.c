#include "i2c.h"
#include "delay.h"
uint8_t AddRd = 0XA1;
uint8_t AddWr = 0XA0;

/**************Start of the Function about IIC**************/

/**
 * @brief ����I2C��ʼ�ź�
 * @callsubfunc I2CDelay 5΢��������ʱ
 * @return ��
 */
void I2CStart(void)
{
    I2C_SCL = 1; //ʱ������Ϊ�ߵ�ƽ
    I2C_SDA = 1; //��������Ϊ�ߵ�ƽ
    I2CDelay(); //��ʱ����ʼ��������ʱ��
    I2C_SDA = 0; //�����������ߣ�������ƽ����
    I2CDelay();  //��ʱ����ʼ��������ʱ��
    I2C_SCL = 0; //����ʱ�����ߣ��������ݱ仯
}

/**
 * @brief ����I2Cֹͣ�ź�
 * @callsubfunc I2CDelay 5΢��������ʱ
 * @return ��
 */
void I2CStop(void)
{
    I2C_SCL = 0; //ʱ������Ϊ�͵�ƽ
    I2C_SDA = 0; //��������Ϊ�͵�ƽ
    I2CDelay();  //��ʱ��ֹͣ��������
    I2C_SCL = 1; //����ʱ������
    I2CDelay();  //��ʱ�������ͷ�
    I2C_SDA = 1; //����������Ϊ�ߵ�ƽ
    I2CDelay();  //��ʱ��Ϊ��һ����׼��
    I2C_SCL = 0; //����ʱ�����ߣ��������ݱ仯
}

/**
 * @brief ����Ӧ��λ
 * @callsubfunc I2CDelay 5΢��������ʱ
 * @return ��
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
 * @brief ���ͷ�Ӧ��λ
 * @callsubfunc I2CDelay 5΢��������ʱ
 * @return ��
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
 * @brief �ȴ��ӻ�Ӧ��IIC����.
 * @param i ������Ƶȴ�ʱ�䣬��ֹ����.
 * @return ��
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
 * @brief ��������һ���ֽ����ݵ�IIC����
 * @param Data �����͵��ֽ�
 * @param mask λ̽���־
 * @return ��
 */
void I2CSendByte(uint8_t Data)
{
	uint8_t mask = 0x80;
	for (mask = 0x80; mask != 0; mask >>= 1)
	{
	    I2C_SCL = 0;          //�������ݱ仯������һ�����ݴ���
		I2CDelay();
		I2C_SDA = (mask & Data) ? 1 : 0;
		I2CDelay();
        I2C_SCL = 1;          //����SCL
        I2CDelay();
	}
	I2C_SCL = 0;              //������SCL�����λ����
}


/**
 * @brief ��ȡIIC�����ϵ�����
 * @param mask λ̽���־
 * @return Data ��ȡ������
 */
uint8_t I2CReadByte(void)
{
    uint8_t mask = 0x80, Data = 0x00;
    I2C_SDA = 1;               //�����ͷ�SDA
	for (mask = 0x80; mask != 0; mask >>= 1)
	{
	    I2C_SCL = 1;          //���������ݱ仯����ȡ����
		I2CDelay();
		Data |= (I2C_SDA ? mask : 0x00); //��ȡSDA��ֵ������λdata��Ӧλ
		I2CDelay();
        I2C_SCL = 0;          //����SCL��Ϊ��һ�����ݶ�ȡ��׼��
        I2CDelay();
	}
	return Data;
}

/**
 * @brief ������ӻ�д������
 * @param Data ��д�������
 * @param Address д��ĵ�ַ 24c02��0x00-0xff
 * @param Num �ֽ���
 * @return ��
 */
void WrToROM(uint8_t *Data, uint8_t Address, uint8_t Num)
{
    uint8_t i;
    uint8_t * PData;
    PData=Data;
    for(i = 0; i < Num; i ++)
    {
        I2CStart();               //������ʼ�ź�
        I2CSendByte(AddWr);       //���Ϳ����ֽ�
        I2CWaitAck();             //�ȴ��ӻ���Ӧ
        I2CSendByte(Address + i); //д��洢��ַ0X00-0XFF
        I2CWaitAck();             //�ȴ��ӻ���Ӧ
        I2CSendByte(*(PData + i));//д����
        I2CWaitAck();             //�ȴ��ӻ���Ӧ
        I2CStop();                //����ֹͣ�ź�
        I2CDelay();
		delay_ms(10);
    }
	
}

/**
 * @brief ������ȡ�ӻ�����
 * @param Data ������ʱ�洢
 * @param Address ��ȡ�ĵ�ַ 24c02��0x00-0xff
 * @param Num ��ȡ�ֽ���
 * @return ��
 */
void RdFromROM(uint8_t *Data, uint8_t Address, uint8_t Num)
{
    uint8_t i;
    uint8_t * PData;
    PData = Data;
    for(i = 0; i < Num; i ++)
    {
        I2CStart();              //������ʼ�ź�
        I2CSendByte(AddWr);      //���Ϳ����ֽڣ�д��ַ��оƬ
        I2CWaitAck();            //�ȴ�Ӧ��
        I2CSendByte(Address + i);//д��洢��ַ
        I2CWaitAck();            //�ȴ��ӻ�Ӧ��
		
        I2CStart();              //������ʼ�ź�
        I2CSendByte(AddRd);      //���Ϳ����ֽڣ���оƬ/��
        I2CWaitAck();            //�ȴ�Ӧ��
        * (PData + i) = I2CReadByte();//������
        I2C_SCL = 0;             //����SCL�����ݿɸı䣬Ϊ��ȡ��һλ������׼��
        I2CNACK();               //������ֽڣ����跢����
        I2CStop();               //ֹͣ�ź�
		delay_ms(10);
    }
}
/**************END of the Function about IIC**************/