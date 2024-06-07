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
