# Arduino

## 温湿度采集与显示

*温湿度采用DHT11采集数据*

*将采集到的数据在OLED上显示*



> ***Arduino DHT11编程***
>
> 首先，我们必须包含“ DHT.h”库。
>
> ​	\#include "DHT.h"
>
> 然后定义连接DHT11的数字引脚。
>
> ​	#define DHTPIN 5
>
> 定义DHT传感器的类型。
>
> 由于我们使用的是DHT11传感器，因此可以这样编写。
>
> ​	#define DHTTYPE DHT11
>
> 如果您有DHT22，请编写此代码。
>
> ​	#define DHTTYPE DHT22
>
> 然后定义DHT参数以初始化DHT传感器。
>
> ​	DHT dht(DHTPIN, DHTTYPE);
>
> **Setup 初始化**
>
> void setup() {
>
> ​	Serial.begin(9600);
>
> ​	Serial.println(F(“DHTxx test!”));
>
> ​	dht.begin();
>
> }
>
> **Loop 读取数据并输出**
>
> float h = dht.readHumidity(); //读取湿度
>
> float t = dht.readTemperature(); // 读取温度 摄氏度
>
> float f = dht.readTemperature(true); // 读取温度 华氏度

## **Arduino** **使用U8G2**



> **u8g2的初始化**
>
> \#include <Arduino.h> 
>
> \#include <U8g2lib.h> 
>
> U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 14, 2, U8X8_PIN_NONE); 
>
> void setup(void) {
>
> u8g2.begin(); 
>
> }
>
> **u8g2的使用**
>
> void loop(void) { 
>
> ​	u8g2.clearBuffer(); 
>
> ​	// ... write something to the buffer 
>
> ​	u8g2.sendBuffer(); 
>
> }
>
> U8g2显示字符
>
> void loop(void) {
>
> ​	u8g2.clearBuffer(); 
>
> ​	// clear the internal memory
>
> ​	u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
>
> ​	u8g2.drawStr(0,10,"Hello World!"); // write something to the internal memory
>
> ​	u8g2.sendBuffer(); 
>
> ​	// transfer internal memory to the display
>
> ​	delay(1000); 
>
> }

> **u8g2的设置相关函数**
>
> 1.setFront();
>
> ​	//设置要显示的字符的字体。
>
> 2.setPrintPos(x,y);
>
> ​	//作用：设置下文中print()的显示位置 x:横坐标,y:纵坐标
>
> 3.setColorIndex(color_index);
>
> ​	//作用：对于本文使用的单色oled来说，此函数的功能为显示对象。
>
> ​	// 可以理解为透明或不透明。对于灰度值得屏幕则是一个灰度值 color_index:0 或 1；
>
> 4.setRot90(),setRot180(),setRot270()
>
> ​	//作用：将显示得结果旋转90，180，270.
>
> 5.setFrontPosTop();
>
> ​	//使用drawStr显示字符串时，默认标准为显示字符的左下角坐标,
>
> ​	//本函数可理解为将坐标位置改为显示字符串的左上角为坐标标准.

> **U8g2显示图片**
>
> const unsigned char col[] U8X8_PROGMEM = {
>
> 0xFF, 0xFE … 
>
> }
>
> u8g2.clearBuffer(); // 清空显示设备内部缓冲区
>
> u8g2.drawXBMP( 0 , 0 , 128 , 57 , col ); //128,57为图片尺寸，根据你的图片尺寸修改
>
> u8g2.sendBuffer(); // 显示缓冲区内容

### 温湿度显示仪

```c
/*
*Author:祝光
*Data:2021/2/1
*/

#include "DHT.h"

#include <Arduino.h>
#include <U8g2lib.h>



#define DHTPIN 5
#define DHTTYPE DHT11

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 14, 2, U8X8_PIN_NONE);

// width: 21, height: 32
const unsigned char icon_hum[] U8X8_PROGMEM = { 0xff,0xf9,0x1f,0xff,0xf1,0x1f,0xff,0xf0,0x1f,0xff,0xe4,0x1f,0x7f,0xe4,0x1f,0x7f,0xce,0x1f,0x3f,0xce,0x1f,0x3f,0x9f,0x1f,0x1f,0x9f,0x1f,0x9f,0x3f,0x1f,0x8f,0x3f,0x1f,0xcf,0x7f,0x1e,0xc7,0x7f,0x1e,0xe7,0xff,0x1c,0xe3,0xff,0x1c,0xf3,0xff,0x19,0xf3,0xff,0x19,0xf9,0xff,0x13,0xf8,0xff,0x13,0x00,0xff,0x03,0x00,0xfc,0x07,0x00,0xf8,0x07,0x00,0xe0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x10,0x03,0x00,0x18,0x03,0x00,0x1c,0x0f,0x00,0x1c,0x1f,0x00,0x1f,0x7f,0xc0,0x1f };

   
// width: 32, height: 32
const unsigned char icon_tem[] U8X8_PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x00,0xe0,0x07,0x00,0x00,0xf0,0x0f,0x00,0x00,0x70,0x0e,0x00,0x00,0xf0,0x0f,0x00,0x00,0xf0,0x0e,0x00,0x00,0xf0,0x0e,0x00,0x00,0xf0,0x0f,0x00,0x00,0x70,0x0e,0x00,0x00,0xf0,0x0f,0x00,0x00,0xf0,0x0e,0x00,0x00,0x70,0x0e,0x00,0x00,0x70,0x0e,0x00,0x00,0x70,0x0e,0x00,0x00,0x70,0x0e,0x00,0x00,0x3c,0x3c,0x00,0x00,0x5c,0x38,0x00,0x00,0x6e,0x70,0x00,0x00,0x7e,0x70,0x00,0x00,0x36,0x60,0x00,0x00,0x7e,0x76,0x00,0x00,0xee,0x77,0x00,0x00,0xdc,0x3b,0x00,0x00,0xf8,0x1f,0x00,0x00,0xf0,0x0f,0x00,0x00,0xe0,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


DHT dht(DHTPIN, DHTTYPE);

//初始化函数
void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}


char chars_t[10];
char chars_h[10];

//主程序，始终再次循环
void loop(void) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.drawStr(0,10,"Temperature Humidity");
  u8g2.drawLine(0,11,128,11);   //画横线
  u8g2.drawLine(64,11,64,64);  //画垂直向下中间的数
  u8g2.drawXBMP( 16 , 12 , 32 , 32 , icon_tem );   //画左边的温度图标
  u8g2.drawXBMP( 84 , 12 , 21 , 32 , icon_hum );   //画右边的温度图标
  float h = dht.readHumidity(); //读取湿度
  String str_h = String(h , 2) ; 
  str_h.toCharArray(chars_h , 7);
  u8g2.drawStr(80,60, chars_h);

  
  float t = dht.readTemperature(); // 读取温度 摄氏度
  String str_t = String(t , 2) ; 
  str_t.toCharArray(chars_t , 8);
  u8g2.drawStr(16,60, chars_t);
  
  //Serial.println(h);  //如果想把温湿度通过串口打印下来可以用此语句
  //Serial.println(t);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}

```





[调整图片尺寸和像素]: https://www.iloveimg.com/zh-cn/resize-image
[图片取模]: http://tools.clz.me/image-to-bitmap-array

