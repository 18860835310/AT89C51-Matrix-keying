# AT89C51系列开发板_矩阵按键
在普中-4开发板上的一个关于4*4矩阵按键的简单项目

本程序是基于AT89C51的开发板上的4*4矩阵的控制与效果实现。
当从左向右依次按下矩阵按键后，可以在一位共阳极数码管上显示符号0-9，A-F。
其矩阵按键扫描的思想可以移植，至于输出的效果可以更改成其他输出设备或程序模块。
矩阵占据单片机的P1口的8位，数码管占据P0的8位端口。

# 硬件设备
## 开发板如图所示，可以使用其他开发板，这里只做参考
![Loading](开发板图片.png "普中-4开发板")

## 矩阵电路的连接如下所示
![Loading](矩阵按键.png "普中-4开发板")

# 具体程序
## 全部程序
先上程序，具体方法讲解后面再提
```c
#include "reg52.h"

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;

#define KEY_MATRIX_PORT	P1	//使用宏定义矩阵按键控制口	

#define SMG_A_DP_PORT	P0	//使用宏定义数码管段码口


//共阴极数码管显示0~F的段码数据
u8 gsmg_code[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

// 二维矩阵存储按键状态
u8 key_matrix[4][4] = {
						{0x77,0x7b,0x7d,0x7e},
						{0xb7,0xbb,0xbd,0xbe},
						{0xd7,0xdb,0xdd,0xde},
						{0xe7,0xeb,0xed,0xee}	
						};  

// 一维矩阵存储按照行扫描的方式
u8 key_cows[4] = {0x7f,0xbf,0xdf,0xef};

u8 value = 0;

void scan_keys()
{
	u8 i,j;
	//u8 key_value = 0;
	for(i=0;i<4;i++)
	{
		KEY_MATRIX_PORT = key_cows[i];
		if( KEY_MATRIX_PORT != key_cows[i] )//判断第一列按键是否按下
		{
				for(j=0;j<4;j++)
			{
				delay_10us(550);//消抖
				if(KEY_MATRIX_PORT == key_matrix[i][j])
				{
					value = 4*i+j;
					//SMG_A_DP_PORT = gsmg_code[4*i+j];
					//while(KEY_MATRIX_PORT == key_cows[i]);//等待按键松开
				}
			}
		}
	}
}

void main()
{	
	while(1)
	{
		scan_keys();
	   	SMG_A_DP_PORT = gsmg_code[value];
	}		
}
```

## 程序拆分
