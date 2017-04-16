  标题:  步进电机试验二（双四拍方式）																														
  通过本例程了解步进马达使用及驱动程序编写										
  双四拍工作方式：                                                           	
  正转：A/B   AB   AB/  A/B/      								               
  反转：A/B/  AB/  AB   A/B
  UDN2916电流控制真值表：
	 I0    I1      输出电流
	  L     L        最大
	  H     L	       最大*2/3
	  L	    H	       最大*1/3
    H     H        0	                                                                        	                          						

#include "reg52.h"

#define speed 2
//定义Motor管脚
sbit PH1 = P1^0;
sbit PH2 = P1^1;
sbit I01 = P1^2;
sbit I11 = P1^3;
sbit I02 = P1^4;
sbit I12 = P1^5;

void delay(int time);

函数功能：产生脉冲控制步进机
正转：A/B   AB   AB/  A/B/ 
void Go(void)
{
    // A/B
    PH1 = 0;  //PH1为0 则A线圈为反向电流
    I01 = 0;
    I11 = 0;

    PH2 = 1;  //PH2为1 则B线圈为正向电流
    I02 = 0;
    I12 = 0;
    delay(speed);

    // AB
    PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
    I11 = 0;

    PH2 = 1;
    I02 = 0;
    I12 = 0;
    delay(speed);

    // AB/
    PH1 = 1;  //PH1为1 则A线圈为正向电流
    I01 = 0;
    I11 = 0;
	
    PH2 = 0;   //PH2为0 则B线圈为反向电流
    I02 = 0;
    I12 = 0;
    delay(speed);

    // A/B/
    PH1 = 0;
    I01 = 0;
    I11 = 0;

    PH2 = 0;  
    I02 = 0;
    I12 = 0;         
    delay(speed);	
}

void delay(int time)
{ 
  int i,j;
  for(j=0; j <= time; j++)
  	for(i =0 ; i <= 120; i++);
}

void main(void)
{
  while(1)
  {  
    Go();  //步进电机运行	
  }
}
