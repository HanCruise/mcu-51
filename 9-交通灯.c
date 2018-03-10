#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define GPIO_DIG     P0   //数码管段选
#define GPIO_PLACE   P1   //位选
#define GPIO_TRAFFIC P2   //交通灯

sbit RED10=   P2^0;//上下方向人行道红绿灯
sbit GREEN10= P2^1;
sbit RED11=   P2^2;//上下方向机动道红黄绿灯
sbit YELLOW11=P2^3;
sbit GREEN11= P2^4;

sbit RED00=   P3^0;//左右方向人行道红绿灯
sbit GREEN00= P3^1;
sbit RED01=   P2^5;//左右方向机动道红黄绿灯
sbit YELLOW01=P2^6;
sbit GREEN01= P2^7;

uchar code DIG_PLACE[8]=
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//位选编码，查表方式
uchar code DIG_CODE[16]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//共阴数码管0~F编码
uchar DisplayData[8];
uchar Time=0,Second;

void DigDisplay(void);
void Timer0Config(void);//定时器0配置

void main(void)
{
	Second=1;
	Timer0Config();
	while(1){
		if(Second==70) Second=1;
		if(Second<31){
			DisplayData[0]=0x00;
			DisplayData[1]=0x00;
			DisplayData[2]=DIG_CODE[(30-Second)%100/10];
			DisplayData[3]=DIG_CODE[(30-Second)%10];
			DisplayData[4]=0x00;
			DisplayData[5]=0x00;
			DisplayData[6]=DisplayData[2];
			DisplayData[7]=DisplayData[3];
			DigDisplay();
			
			GPIO_TRAFFIC=0xff; //全灭
			RED00=1;
			GREEN00=1;
			
			GREEN10= 0; //上下通行
			GREEN11= 0;		
			RED00=0;    //左右禁止
			RED01=0;
		}
		else if(Second<36){
			DisplayData[0]=0x00;
			DisplayData[1]=0x00;
			DisplayData[2]=DIG_CODE[(35-Second)%100/10];
			DisplayData[3]=DIG_CODE[(35-Second)%10];
			DisplayData[4]=0x00;
			DisplayData[5]=0x00;
			DisplayData[6]=DisplayData[2];
			DisplayData[7]=DisplayData[3];
			DigDisplay();
			
			GPIO_TRAFFIC=0xff; //全灭
			RED00=1;
			GREEN00=1;

			YELLOW01=0;//黄灯亮、红灯亮
			RED00 = 0;
      			YELLOW11=0;
			RED10	= 0;
		}
		else if(Second<66){
			DisplayData[0]=0x00;
			DisplayData[1]=0x00;
			DisplayData[2]=DIG_CODE[(65-Second)%100/10];
			DisplayData[3]=DIG_CODE[(65-Second)%10];
			DisplayData[4]=0x00;
			DisplayData[5]=0x00;
			DisplayData[6]=DisplayData[2];
			DisplayData[7]=DisplayData[3];
			DigDisplay();
			
			GPIO_TRAFFIC=0xff; //全灭
			RED00=1;
			GREEN00=1;
			
			RED10=0;   //上下禁止
			RED11=0;
			GREEN00=0; //左右通行
			GREEN01=0;
		}
		else{
			DisplayData[0]=0x00;
			DisplayData[1]=0x00;
			DisplayData[2]=DIG_CODE[(70-Second)%100/10];
			DisplayData[3]=DIG_CODE[(70-Second)%10];
			DisplayData[4]=0x00;
			DisplayData[5]=0x00;
			DisplayData[6]=DisplayData[2];
			DisplayData[7]=DisplayData[3];
			DigDisplay();
			
			GPIO_TRAFFIC=0xff; //全灭
			RED00=1;
			GREEN00=1;

			YELLOW01=0;//黄灯亮、红灯亮
			RED00 = 0;
      			YELLOW11=0;
			RED10	= 0;
		}
	}
}

void DigDisplay(void)
{
	uchar i,j;
	for(i=0;i<8;i++){
		GPIO_PLACE=DIG_PLACE[i];//先位选、再段选
		GPIO_DIG=DisplayData[i];//注意顺序，否则在该灭的位置会有影
		j=10;
		while(j--);
		GPIO_DIG=0x00;//消影
	}
}

void Timer0Config(void) //配置定时器0
{
	TMOD=0x01; //定时器0工作方式1
	TH0=0x3c;  //TH0=(65536-50000)/256,TL0=(65536-50000)%256
	TL0=0xb0;  //定时50ms,晶振频率11.926740MHz
	EA=1;      //开总中断允许
	ET0=1;     //开T0中断允许
	TR0=1;     //启动T0，开始计时
}

void Timer0() interrupt 1  //中断服务程序
{
	TH0=0x3c;//重装初值
	TL0=0xb0;
	Time++;
	if(Time==20)//定时1s
	{
		Second++;
		Time=0;
	}
}

