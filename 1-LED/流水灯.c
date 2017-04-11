#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

void Delay10ms(uint c);

void main(void)
{
	uchar led=0xfe;
	while(1)
	{
		P0=led;
		Delay10ms(50);
		led=led<<1;
		if(led==0x00)
			led=0xfe;
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
