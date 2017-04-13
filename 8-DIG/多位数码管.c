#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_DIG   P0
#define GPIO_PLACE P1

//位选控制，采用查表方式
uchar code DIG_PLACE[8]=
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

//共阴数码管 0~F 编码
uchar code DIG_CODE[16]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

uchar DisplayData[8];

void Display(void);

void main(void)
{
	uint i;
	for(i=0;i<8;i++)
	{
		DisplayData[i]=DIG_CODE[i];
	}
	while(1)
	{
		Display();
	}
}

void Display(void)
{
	uint i,j;
	for(i=0;i<8;i++)
	{
		GPIO_PLACE=DIG_PLACE[i];
		GPIO_DIG=DisplayData[i];
		j=10;
		while(j--);
		GPIO_DIG=0x00;//消影
	}
}

