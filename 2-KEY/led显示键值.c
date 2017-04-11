#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_LED P0
#define GPIO_KEY P1

void Delay10ms(uint c);
uchar Key_Scan(void);

void main(void)
{
	uchar keynum,ledvalue=0x00;
	while(1)
	{
		keynum=Key_Scan();
		if(keynum!=0x00)
		{
			ledvalue=keynum;
		}
		GPIO_LED=~ledvalue;
	}
}

uchar Key_Scan(void)
{
	uchar keyvalue=0x00,i;
	if(GPIO_KEY!=0xff)
	{
		Delay10ms(1);
		if(GPIO_KEY!=0xff)
		{
			keyvalue=GPIO_KEY;
			i=0;
			while((i<50)&&(GPIO_KEY!=0xff))
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
