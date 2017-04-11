#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_LED P0
sbit K1=P1^0;
sbit K2=P1^1;

void Delay10ms(uint c);
uchar Key_Scan(void);

void main(void)
{
	uchar keynum,ledvalue=0x01;
	while(1)
	{
		keynum=Key_Scan();
		if(keynum==1)
		{
			ledvalue=_cror_(ledvalue,1);
		}
		else if(keynum==2)
		{
			ledvalue=_crol_(ledvalue,1);
		}
		GPIO_LED=ledvalue;
	}
}

uchar Key_Scan(void)
{
	uchar keyvalue=0x00,i;
	if(K1==0)
	{
		Delay10ms(1);
		if(K1==0)
		{
			keyvalue=1;
			i=0;
			while((i<50)&&(K1==0))
			{
				Delay10ms(1);
				i++;
			}
		}
	}
	else if(K2==0)
	{
		Delay10ms(1);
		if(K2==0)
		{
			keyvalue=2;
			i=0;
			while((i<50)&&(K2==0))
			{
				Delay10ms(1);
				i++;
			}
		}
	}
	return keyvalue;
}

void Delay10ms(uint c)
{
	uchar a,b;
	for(;c>0;c--)
		for(a=38;a>0;a--)
			for(b=130;b>0;b--);
}
