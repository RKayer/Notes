# 复读机

*网络编程*



**Server端**

当收到客户端发送的消息“xxx”(英文字符串)，自动回复“I get xxx”

监听在任意端口

**Client端**

可以使用任意网络助手（手机、PC、自己的程序）

> void init_dll(); //加载动态链接库
>
> void close_dll(); //释放动态链接库
>
> void close_socket(SOCKET socket); //关闭socket
>
> SOCKET new_client(char *domain, int port); //创建一个客户端
>
> SOCKET new_server(int port); //创建一个服务端
>
> void send_msg(SOCKET socket, char *msg); //往Socket中写入数据
>
> void recv_msg(SOCKET socket, char *buf); //从Socket中读取数据

```c
/*复读机
*网络编程语言
*Author:祝光
*Data：2021/1/30
*/
#include <stdio.h>
#include <stdlib.h>
#include "E:\visual desk\单片机leaning\物联网\程序\common\yuyang_net.h"   //包含.h文件的函数封装库

//主函数
int main()
{
    init_dll();    //加载动态链接库
    SOCKET server = new_server(8888);  //定义一个SOCKET型变量，创建一个服务端
    char buf[1024];   
    char send[1024];
    while(1){
        for(int i = 0;i <1024;i++){
            buf[i] = '\0';
            send[i] = '\0';

        }
        recv_msg(server,buf);     //接收数据
        sprintf(send,"I get %s\r\n",buf);   //字符拼接
        send_msg(server,send);     //发送数据

    }
    return 0;
}

```





# 加法机器人

**Server端**

读取用户输入的数字，自动做加法并返回当前结果，一直做累加。

读取用户输入’#’，则清空当前数据。

监听在任意端口

**Client端**

可以使用任意网络助手（手机、PC、自己的程序）

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../单片机leaning/物联网/程序/common/yuyang_net.h"

int main()
{
    init_dll();
    SOCKET server = new_server(8889);
    char buf[1024];
    char send[1024];
    int i = 0;
    while(1){
        for(int j = 0;j<1024;j++){
            buf[j] = '\0';      //每次接收数据后将字符数组清空
            send[j] = '\0';
        }
        recv_msg(server,buf);
        if( strcmp(buf,"#") == 0 || strcmp(buf,"#\r") == 0 || strcmp(buf,"#\r\n") == 0){
            i = 0;
            continue; 
        }
        i += (int)(atoi(buf));   //atoi函数将字符类型转为整型
        sprintf(send,"%d\r\n",i);     //整型转为字符型
        send_msg(server,send);
    }

    return 0;
}
```





# 我爱算数

**Server端**

当有客户端连接时，自动生成2个数(x1 x2)，以及运算方式（加减乘），返回给客户端。

然后等待客户端返回答案。

判断客户端返回答案是否正确，返回Y or N，并再次出题。

**Client端**

获取到服务端的题目，用户输入答案，再次做题

```C
/*
*Author:祝光
*Data：2021/1/30
*/

#include <stdio.h>
#include <stdlib.h>

#include "common/yuyang_net.h"

#define type_+ 0
#define type_- 1
#define type_* 2


//主程序
int main()
{
    init_dll();
    SOCKET server = new_server(8890);   //创建新的服务端（端口号）

    char send[1024];
    char buf[1024];
    int i = 0;
    while(1){
        for(int j = 0;j<1024;j++){
            send[j] = '\0';
            buf[j] = '\0';
        }
        time_t tm = time(NULL);//得到系统时间
        srand((unsigned int)tm);//随机种⼦只需要设置⼀次即可
        int num1 = rand() % 100;    //将生成的随机数保存取模，控制在100以内
        int num2 = rand() % 100;
        int num3 = rand() % 3;     //将生成的数字的三种情况分别表示三种运算方式
        int res;    //结果
        
        switch(num3){
        case type_+:
            sprintf(send,"%d + %d = \r\n",num1,num2);
            res = num1 + num2;
            send_msg(server,send);
            break;
        case type_-:
            sprintf(send,"%d - %d = \r\n",num1,num2);
            res = num1 - num2;
            send_msg(server,send);
            break;
        case type_*:
            sprintf(send,"%d * %d = \r\n",num1,num2);
            res = num1 * num2;
            send_msg(server,send);
            break;
        }
        recv_msg(server,buf);
        int temp = atoi(buf);
        if(temp == res){
            send_msg(server,"You Are Right!");

        }else{
            send_msg(server,"You Are Wrong!");
        }
    }
    return 0;
}

```



# C语言随机数

***time     srand***

```c
#include <time.h>
time_t tm = time(NULL);//得到系统时间
srand((unsigned int)tm);//随机种⼦只需要设置⼀次即可
int num = rand() % 100;  //获取随机数并将其控制在100以内
```



