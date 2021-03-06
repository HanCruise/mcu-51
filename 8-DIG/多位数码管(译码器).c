#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_DIG   P0
sbit LSA=P1^0;
sbit LSB=P1^1;
sbit LSC=P1^2;

uchar code DIG_CODE[16]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void main(void)
{
	uint i=0,j;
	while(1)
	{
		switch(i)
		{
			case 0:LSA=0;LSB=0;LSC=0;break;
			case 1:LSA=1;LSB=0;LSC=0;break;
			case 2:LSA=0;LSB=1;LSC=0;break;
			case 3:LSA=1;LSB=1;LSC=0;break;
			case 4:LSA=0;LSB=0;LSC=1;break;
			case 5:LSA=1;LSB=0;LSC=1;break;
			case 6:LSA=0;LSB=1;LSC=1;break;
			case 7:LSA=1;LSB=1;LSC=1;break;
			default:break;
		}
		GPIO_DIG=DIG_CODE[i];
		//刷新时间间隔语句，若放在消影语句之后可调节数码管亮度
		j=10;          
		while(j--);
		//原理：位选段选语句表示亮，消影语句表示灭，调整亮灭时间长度从而在不断刷新的机制下调节数码管亮度
		GPIO_DIG=0x00; //消影
		i++;
		if(i==8) i=0;
	}
}

