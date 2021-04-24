@[TOC]

# Arduino




本节主要是对理学堂物联网模块先前学习的一个总结笔记，以及最近学的用Arduino来实现WIFI对小车的控制的一个学习总结


之前的一些课件，笔记我都还在，我就复习了一下，然后把一些要点进行了总结归纳。
## 温湿度采集与显示

*温湿度采用DHT11采集数据*

*将采集到的数据在OLED上显示*



> ***Arduino DHT11编程***
>
> 首先，我们必须包含“ DHT.h”库。
>
> ​	`\#include "DHT.h"`
>
> 然后定义连接DHT11的数字引脚。
>
> ​	`#define DHTPIN 5`
>
> 定义DHT传感器的类型。
>
> 由于我们使用的是DHT11传感器，因此可以这样编写。
>
> ​	`#define DHTTYPE DHT1`
>
> 如果您有DHT22，请编写此代码。
>
> ​	`#define DHTTYPE DHT22`
>
> 然后定义DHT参数以初始化DHT传感器。
>
> ​	`DHT dht(DHTPIN, DHTTYPE);`
>
> **Setup 初始化**
>
> ```c
> void setup() {
>
> ​	Serial.begin(9600);
>
> ​	Serial.println(F(“DHTxx test!”));
>
> ​	dht.begin();
>
> }
>```
> **Loop 读取数据并输出**
>```c
> float h = dht.readHumidity(); //读取湿度
>
> float t = dht.readTemperature(); // 读取温度 摄氏度
>
> float f = dht.readTemperature(true); // 读取温度 华氏度
> ```

## **Arduino** **使用U8G2**
//u8g2库


> ```c
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
>```
> **u8g2的使用**
>```c
> void loop(void) { 
>
> ​	u8g2.clearBuffer(); 
>
> ​	// ... write something to the buffer 
>
> ​	u8g2.sendBuffer(); 
>
> }
>```
> U8g2显示字符
>```c
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
> ```

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
>```c
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
> ```

## 温湿度显示仪

```c
/*
*Author:祝光
*Data:2021/4/23
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




* 工具网站 
[调整图片尺寸和像素](https://www.iloveimg.com/zh-cn/resize-image)
[图片取模](http://tools.clz.me/image-to-bitmap-array)



## esp8266实现WIFI控制小车
理学堂讲解的比较杂，比较粗糙，通过我自己的摸索，总算是能大致了解这么一个WIFI控制小车的原理和主要功能实现的步骤。

### 通过Arduino编程将esp8266连接电脑热点
要实现的功能：
1. esp8266连接电脑热点
2. esp8266作为服务端，电脑作为客户端进行网络通信
3. 用OLED显示屏显示WIFI数据

必要的头文件
```c
#include <Arduino.h>  
#include <U8g2lib.h>   //OLED显示屏要包含的头文件
#include <ESP8266WiFi.h>  //ESP8266WIFI头文件
```
设置WIFI
```c
const char *ssid     = "zhu guang";//这里写入网络的ssid
const char *password = "12345678";//wifi密码
```
设置字体
```c
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 14, 2, U8X8_PIN_NONE);
```
设置WIFI服务的端口号
```c
WiFiServer server(80);   //端口
```
setup函数部分
* 串口初始化、OLED初始化
* 连接WIFI热点
* 启用TCP 服务端
* 显示WIFI数据
```c
void setup() {

  u8g2.begin();  
  Serial.begin(2400); //串口2400
  u8g2.setFont(u8g2_font_6x10_mf);//oled字体
  
  WiFi.begin(ssid, password); //等待wifi连接
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
  }
    
  server.begin(); //启动TCP server服务器
  u8g2.clearBuffer();          
  u8g2.drawStr(6,10," WiFi connected");
  u8g2.drawStr(6,22,(" ip: " + WiFi.localIP().toString()).c_str());   //显示服务端的IP地址
  u8g2.sendBuffer();
}
```
loop循环函数部分
```c
void loop() {

  //检查客户端是否已连接
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  client.setTimeout(5000); //默认为 1000  
    //读取客户端发起的TCP请求
  String req = client.readStringUntil('\r');
  
  /*解析请求里是否含有以下指定内容
    这部分可以自己选择写几个，根据自己需要用WIFI控制小车不同状态的指令数来决定
 */
  //检查发起的请求内容是否包含"0" 
  if (req.indexOf(F("0")) != -1)
  {
    Serial.print("0");
  }
  //检查发起的请求内容是否包含"1" 
  if (req.indexOf(F("1")) != -1)
  {
    Serial.print("1");
  }

  //检查发起的请求内容是否包含"2" 
  if (req.indexOf(F("2")) != -1)
  {
    Serial.print("2");
  }

  
  //检查发起的请求内容是否包含"3" 
  if (req.indexOf(F("3")) != -1)
  {
    Serial.print("3");
  }

    //检查发起的请求内容是否包含"4" 
  if (req.indexOf(F("4")) != -1)
  {
    Serial.print("4");
  }

  //检查发起的请求内容是否包含"5" 
  if (req.indexOf(F("5")) != -1)
  {
    Serial.print("5");
  }
  
    //将响应体发送到客户端 注:若要使用中文则必须在其中添加<meta charset=\"utf-8\">声明编码
    //HTML了解一点，感觉放在这里好像没什么必要
  client.print("<!DOCTYPE HTML><html><head><style type=\"text/css\">button {text-decoration: none;position: absolute;width: 20%;min-height: 20%;height: auto;font-size: 40px;}</style></head>");
 
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/0'> <button style=\"top: 30%; left: 20%;\">  on  </button> </a> "));
  
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/1'> <button style=\"top: 30%; left: 40%;\">  up  </button> </a> "));
  
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/2'> <button style=\"top: 30%; left: 60%;\">  off  </button> </a> "));

  
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/3'> <button style=\"top: 60%; left: 20%;\">  left  </button> </a> "));

  
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/4'> <button style=\"top: 60%; left: 40%;\">  down  </button> </a> "));

      
  client.print(F("\r\n<a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/message/5'> <button style=\"top: 60%; left: 60%;\">  right  </button> </a> "));
  
  client.print(F("</html>"));
}
```

### 通过串口助手发出指令控制小车
1. 将arduino程序烧录到ESP8266上，待ESP8266上OLED显示屏显示WIFI conected 以及IP地址则表示连接成功，断开数据线。
2. 将ESP8266上的引脚接线到单片机
3. 将小车程序烧录到单片机（在连接ESP8266的时候程序有可能烧不进去，建议先断开ESP8266）
4. 通过串口助手发出指令控制小车

```c
void Com_Int() interrupt 4  //串口中断函数
{
	if(RI==1)
	{
		char receive = SBUF;
		RI=0;
		
		//蓝牙模块接受数据处理
		switch (receive)
		{
			case '1':  //电机模式切换
				enableMotor=~enableMotor;break;
			case '2':   //寻迹避障模式切换
				Mode=~Mode;break;
			//case 1 + 0x30 :enableMotor=~enableMotor;break;
		}
	}
}

```
当时这些功能实现之后可以控制小车的模式切换
启动/停止，左转/右转
```c
switch (receive)
		{
			case '1':  //电机模式切换
				enableMotor=~enableMotor;break;
			case '2':   //左转
				setPWM(-50,50);break;;break;
			case '3':   //左转
				setPWM(50,-50);break;
			case '4':   //后退
				setPWM(-50,-50);break;
			//case 1 + 0x30 :enableMotor=~enableMotor;break;
		}
```
但是这样不同的状态切换通过电脑输入\message\0~5这样比较麻烦，我就用收集上的TCP试了一下，esp8266连接手机热点，发现这样延迟太严重，根本没法控制。感觉还有很多的优化之处，可以试一试遥感操作和换成STM32可能会比较容易控制。


# STM32
还是想早点接触STM32吧，而且之前自创有位学长推荐我自学STM32，并给我推荐了一本书，送了我一款STM32F103C8T6最小系统板。
学习一款全新的单片机，从51到STM32，跟着电科协的视频集学习，首先，搭建开发环境。第一步还是遇到了很多困难的吧，本来以为用原来的keil就可，于是跳过了科协第一集关于keil32的环境搭建，后来在科协技术部学长的帮助下，我总算是弄好了。

## keil5 + STM32CubeMX搭建开发环境
1. 在官网下载keil5最新版
2. 用keil注册机破解
3. 下载stm32f103的固件包并放在keil的pack目录下
4. 下载STM32CubeMX

## 固件库开发模式

首先这本书首先讲了固件库开发模式。

像我们之前的51单片机就是寄存器开发模式，不同的外设，不同的IO口我们都可以通过配置寄存器去进行相关的设置，最常见的可能就是设置LED高低电平，这种开发模式对于小功能的实现无可厚非，但是对于复杂功能的实现就有点鞭长莫及了。我之前在学习模块化编程的时候就在想，能不能把每个模块的一些常用不变的代码做成一个模板，保存起来，然后每次要写的时候再拿出来直接用，这样就会大大提高效率。

所谓固件库开发模式就是每次只用通过调用函数去实现寄存器的配置，建立一个新的软件抽象层。虽然接触得不多，但是觉得这种模式开发会使整个程序代码分块明细，规范有序。






