#include <reg51.h>

#define uchar unsigned char
#define ulong unsigned long

sbit SI =P3^4; //串行输入
sbit RCK=P3^5; //输出存储器锁存时钟
sbit SCK=P3^6; //数据输入时钟

//HC595发送数据函数
void HC595SendData(uchar BT4,uchar BT3,uchar BT2,uchar BT1);

void main(void)
{
	ulong j;
	uchar i,Data;
	while(1)
	{
		//亮
		HC595SendData(0x00,0x00,0xff,0xff);
		for(j=0;j<50000;j++);
		//刷行
		Data=0x01;
		for(i=0;i<8;i++)
		{
			HC595SendData(0x00,0x00,0x00,Data);
			for(j=0;j<2000;j++);
			Data<<=1;
		}
		Data=0x01;
		for(i=0;i<8;i++)
		{
			HC595SendData(0x00,0x00,Data,0x00);
			for(j=0;j<2000;j++);
			Data<<=1;
		}
		//刷列
		Data=0x7f;
		for(i=0;i<8;i++)
		{
			HC595SendData(Data,0xff,0xff,0xff);
			for(j=0;j<2000;j++);
			Data>>=1;
			Data|=0x80;
		}
		Data=0x7f;
		for(i=0;i<8;i++)
		{
			HC595SendData(0xff,Data,0xff,0xff);
			for(j=0;j<2000;j++);
			Data>>=1;
			Data|=0x80;
		}
		//灭
		HC595SendData(0x00,0x00,0x00,0x00);
		for(j=0;j<50000;j++);
	}
}
//根据HC595级联特点，串行输入，先发送BT4，然后依次BT3,BT2,BT1,且每次由高位至至低位按位发送
//按此规律，串行输出与串行输入数据一致(数据发送由高位至低位，数据输出也由高至低)
//并行输出数据高低位由高至低：QH QG QF ~ QB QA
void HC595SendData(uchar BT4,uchar BT3,uchar BT2,uchar BT1)
{
	uchar i;
	for(i=0;i<8;i++) //Send BT4
	{
		SI=BT4>>7;
		BT4<<=1;
		SCK=0;//输入时钟先置0后置1，将数据输入锁存
		SCK=1;//直到下一位输入，再移位锁存
	}
	for(i=0;i<8;i++) //Send BT3
	{
		SI=BT3>>7;
		BT3<<=1;
		SCK=0;
		SCK=1;
	}
	for(i=0;i<8;i++) //Send BT2
	{
		SI=BT2>>7;
		BT2<<=1;
		SCK=0;
		SCK=1;
	}
	for(i=0;i<8;i++) //Send BT1
	{
		SI=BT1>>7;
		BT1<<=1;
		SCK=0;
		SCK=1;
	}
	RCK=0;//输出存储器锁存时钟置0置1再置0
	RCK=1;//将锁存数据并行输出
	RCK=0;
}
