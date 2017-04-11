#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

void Delay10ms(uint c);

void main(void)
{
	uchar i,led=0xfe;
	while(1)
	{
		for(i=0;i<7;i++)
		{
			P0=led;
			Delay10ms(50);
			led=led<<1;
			led=led|0x01;
		}
		for(i=0;i<7;i++)
		{
			P0=led;
			Delay10ms(50);
			led=led>>1;
			led=led|0x80;
		}
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
