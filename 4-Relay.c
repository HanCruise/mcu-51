#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
sbit Relay=P1^4;
sbit K1=P0^0;

void Delay10ms(uint c);

void main(void)
{
	uchar i=0;
	while(1)
	{
		if(K1==0)
		{
			Delay10ms(1);
			if(K1==0)
			{
				Relay=0;
				while((i<50)&&(K1==0))
				{
					Delay10ms(1);
					i++;
				}
			}
		}
		else
			Relay=1;
	}
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
