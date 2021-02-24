
#include "uart.h"

uint8_t flag = 0;        //���ڽ��ձ�־
uint8_t rev_data[20] = {0};  //��Ŵ��ڽ��յ�����
uint8_t rev_num  = 0;        //�洢���ݳ���

/**
 * @brief ���ڳ�ʼ��
 * @param ��
 * @return ��
 */
void Uart_Configuration(void)  
{
    TMOD |= 0x20;    //���ü�����1�Ĺ�����ʽ2
    TH1 = 0xf3;	     //���ü�����1�ĳ�ֵ������������
    TL1 = 0xf3;	     //���ü�����1�ĳ�ֵ������������,0xfd:9600
    PCON = 0x00;     //�����ʱ���  0x00���ӱ�	 0x80�ӱ�
    SCON = 0x50;	 //���ù�����ʽ1 ������������
    EA = 1;		     //�������ж�
    ES = 1;			 //�������ڽ����ж�
    TR1 = 1;		 //������1��ʼ����
}

/**
 * @brief ���ڷ���һ���ַ�����
 * @param dat �����͵�����
 * @return ��
 */
void sendDate(uint8_t dat)
{
    SBUF = dat;		  //���յ������ݷ��뷢�ͻ���������
    while(!TI);       //�ȴ�����������ɣ�TI��־λ����1
    TI = 0;			  //���������ɱ�־λ
}

/**
 * @brief ���ڷ����ַ���
 * @param string �����͵��ַ���
 * @return ��
 */
void sendStr(uint8_t *string)
{
	uint8_t *str = string;
	ES = 0;                  //�رս����ж�
	while(* str)
	{
		sendDate(*str);
		str ++;
	}
	ES = 1;                 //�򿪽����ж�
}

 
/*�жϺ���*/
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
					rev_data[rev_num] = 0;   //�����ַ�����β��ʶ��'\0'
				}
			}
		}
	}
	
	if (TI)
	{
		TI = 0;
	}
	
}