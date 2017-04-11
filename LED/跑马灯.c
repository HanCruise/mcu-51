#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

void Delay10ms(uint c);

void main(void)
{
	uchar led=0x01;
	while(1)
	{
		P0=led;
		Delay10ms(50);
		led=_crol_(led,1);
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
