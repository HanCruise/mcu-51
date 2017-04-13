//此例程采用单个共阳数码管
#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_DIG P0
#define GPIO_KEY P1
//共阴数码管编码
uchar code DIG_CODE[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                         0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

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
			case 0xfe:ledvalue=DIG_CODE[1];break;
			case 0xfd:ledvalue=DIG_CODE[2];break;
			case 0xfb:ledvalue=DIG_CODE[3];break;
			case 0xf7:ledvalue=DIG_CODE[4];break;
			case 0xef:ledvalue=DIG_CODE[5];break;
			case 0xdf:ledvalue=DIG_CODE[6];break;
			case 0xbf:ledvalue=DIG_CODE[7];break;
			case 0x7f:ledvalue=DIG_CODE[8];break;
			default:break;
		}
		GPIO_DIG=~ledvalue;
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
