#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
sbit Beep=P1^5;

void Delay(uint c);

void main(void)
{
	Beep=0;
	Delay(1);
	Beep=1;
	Delay(1);
}

void Delay(uint c)
{
	uchar a;
	for(;c>0;c--)
		for(a=200;a>0;a--);
}
