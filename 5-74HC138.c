#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
sbit LSA=P0^0;
sbit LSB=P0^1;
sbit LSC=P0^2;

void Delay10ms(uint c);

void main(void)
{
	uchar i=1;
	while(1)
	{
		switch(i)
		{
			case 1:LSA=0;LSB=0;LSC=0;break;
			case 2:LSA=1;LSB=0;LSC=0;break;
			case 3:LSA=0;LSB=1;LSC=0;break;
			case 4:LSA=1;LSB=1;LSC=0;break;
			case 5:LSA=0;LSB=0;LSC=1;break;
			case 6:LSA=1;LSB=0;LSC=1;break;
			case 7:LSA=0;LSB=1;LSC=1;break;
			case 8:LSA=1;LSB=1;LSC=1;break;
			default:break;
		}
		Delay10ms(50);
		i++;
		if(i==9) i=1;
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
