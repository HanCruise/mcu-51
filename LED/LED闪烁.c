#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

void Delay10ms(uint c);

void main(void)
{
	while(1)
	{
		P0=0x00;
		Delay10ms(50);
		P0=0xff;
		Delay10ms(50);
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
