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
		switch(keynum)
		{
			case 0xfe:ledvalue=0x01;break;
			case 0xfd:ledvalue=0x02;break;
			case 0xfb:ledvalue=0x04;break;
			case 0xf7:ledvalue=0x08;break;
			case 0xef:ledvalue=0x10;break;
			case 0xdf:ledvalue=0x20;break;
			case 0xbf:ledvalue=0x40;break;
			case 0x7f:ledvalue=0x80;break;
			default:break;
		}
		GPIO_LED=ledvalue;
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
