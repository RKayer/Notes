
#QQ消息轰炸器

**每次运行前先复制消息**

```C
#include <stdio.h>
#include <Windows.h>

int main()
{
    int times;
    char name[100];
    printf("输入你要轰炸的名称：\n");
    scanf("%s",name);
    printf("输入你要轰炸的次数：\n");
    scanf("%d",&times);
    HWND H = FindWindow(0,name);
    while(times -- > 0){
        SendMessage(H, WM_PASTE,0,0);
        SendMessage(H, WM_KEYDOWN,VK_RETURN,0);
    }
    
    return 0;
    
}
```
