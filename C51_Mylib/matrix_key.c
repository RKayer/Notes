#include "matrix_key.h"

/**************Start of the Function about Matrix Keyboard**************/
/**
 * @brief 线反转扫描按键并记录键值.
 * @param 无
 * @return KeyValue 键值.
 */
uint8_t Matrix_Key_Scan()
{
	uint8_t KeyValue = 0;
    GPIO_KEY = 0X0F;
    if(GPIO_KEY != 0x0f)
    {
        delay_ms(10);
        if(GPIO_KEY != 0x0f)
        { 
			switch(GPIO_KEY)
            {
            case(0x07):
                KeyValue = 1;
                break;
            case(0x0b):
                KeyValue = 2;
                break;
            case(0x0d):
                KeyValue = 3;
                break;
            case(0x0e):
                KeyValue = 4;
                break;
            }
            GPIO_KEY = 0xf0;							   //高四位为高电平
            switch(GPIO_KEY)
            {
            case(0x70):
                KeyValue = KeyValue;
                break;
            case(0xb0):
                KeyValue += 4;
                break;
            case(0xd0):
                KeyValue += 8;
                break;
            case(0xe0):
                KeyValue += 12;
                break;
            }
            while(GPIO_KEY != 0xf0)				//松手检测
            {
                GPIO_KEY = 0xf0;
                delay_ms(5);
            }
        }
    }
	return KeyValue;
}
/**************END of the Function about Matrix Keyboard**************/