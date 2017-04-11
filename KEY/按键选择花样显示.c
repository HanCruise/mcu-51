#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_LED P0
#define GPIO_KEY P1

void Delay10ms(uint c);
uchar Key_Scan(void);
void LED1(void);
void LED2(void);
void LED3(void);
void LED4(void);
void LED5(void);
void LED6(void);
void LED7(void);
void LED8(void);

void main(void)
{
	uchar keynum,ledvalue=0x00;
	while(1)
	{
		keynum=Key_Scan();
		switch(keynum)
		{
			case 0xfe:LED1();break;
			case 0xfd:LED2();break;
			case 0xfb:LED3();break;
			case 0xf7:LED4();break;
			case 0xef:LED5();break;
			case 0xdf:LED6();break;
			case 0xbf:LED7();break;
			case 0x7f:LED8();break;
			default:break;
		}
	}
}

void LED1(void)
{
	uchar ledvalue=0x01,i;
	for(i=0;i<16;i++)
	{
		GPIO_LED=ledvalue;
		Delay10ms(5);
		ledvalue=_crol_(ledvalue,1);
	}
}

void LED2(void)
{
	uchar ledvalue=0x80,i;
	for(i=0;i<16;i++)
	{
		GPIO_LED=ledvalue;
		Delay10ms(5);
		ledvalue=_cror_(ledvalue,1);
	}
}

void LED3(void)
{
	GPIO_LED=0xaa;
	Delay10ms(5);
	GPIO_LED=0x55;
	Delay10ms(5);
	GPIO_LED=0xaa;
	Delay10ms(5);
	GPIO_LED=0x55;
	Delay10ms(5);
}

void LED4(void)
{
	GPIO_LED=0x55;
	Delay10ms(5);
	GPIO_LED=0xaa;
	Delay10ms(5);
	GPIO_LED=0x55;
	Delay10ms(5);
	GPIO_LED=0xaa;
	Delay10ms(5);
}

void LED5(void)
{
	GPIO_LED=0xcc;
	Delay10ms(5);
	GPIO_LED=0x33;
	Delay10ms(5);
	GPIO_LED=0xcc;
	Delay10ms(5);
	GPIO_LED=0x33;
	Delay10ms(5);
}

void LED6(void)
{
	GPIO_LED=0x33;
	Delay10ms(5);
	GPIO_LED=0xcc;
	Delay10ms(5);
	GPIO_LED=0x33;
	Delay10ms(5);
	GPIO_LED=0xcc;
	Delay10ms(5);
}

void LED7(void)
{
	LED1();
	LED2();
	LED3();
	LED4();
	LED5();
	LED6();
}

void LED8(void)
{
	GPIO_LED=0x00;
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
