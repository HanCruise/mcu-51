#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_DIG P0
uchar code DIG_CODE[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                         0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void Delay10ms(uint c);

void main(void)
{
	uchar i=0;
	while(1)
	{
		GPIO_DIG=~DIG_CODE[i];
		Delay10ms(50);
		i++;
		if(i==16) i=0;
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
