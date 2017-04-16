					 
半步八拍工作方式：                                                           	 
正转：A/  A/B  B  AB  A  AB/  B/  A/B/
反转：A/B/  B/  AB/  A  AB  B  A/B  A/                                      								
UDN2916电流控制真值表：
     I0    I1    输出电流
     L	    L	   最大
     H	    L	   最大*2/3
     L	    H	   最大*1/3
     H      H      0

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


// 函数功能：产生脉冲控制步进机
// 正转：A/  A/B  B  AB  A  AB/  B/  A/B/
// I0 I1 均为0 以最大电流输出（没有四分） 均为1不输出电流
void Go()
{	 
   // A/  A拍反向电流
   PH1 = 0;	 //PH1为0 A组线圈为反向电流
   I01 = 0;
   I11 = 0;	 //以最大电流输出（没细分）
	
   PH2 = 1;      //PH2为1 B组线圈为正向电流
   I02 = 1;
   I12 = 1;      //关闭电流输出
   delay(speed);

   // A/B AB拍 A为反向电流  B为正向电流
   PH1 = 0;     //PH1为0 A组线圈为反向电流
   I01 = 0;
   I11 = 0;

   PH2 = 1;     //PH2为1 B组线圈为正向电流
   I02 = 0;
   I12 = 0;
   delay(speed);

   // B  B拍 B为正向电流
   PH1 = 1;
   I01 = 1;
   I11 = 1;
	
   PH2 = 1;
   I02 = 0;
   I12 = 0;
   delay(speed);

   //AB  AB拍 均为正向电流
   PH1 = 1;
   I01 = 0;
   I11 = 0;

   PH2 = 1;  
   I02 = 0;
   I12 = 0;
   delay(speed);

   // A
   PH1 = 1;
   I01 = 0;
   I11 = 0;

   PH2 = 0; 
   I02 = 1;
   I12 = 1;
   delay(speed);

   // AB/
   PH1 = 1;
   I01 = 0;
   I11 = 0;

   PH2 = 0;  
   I02 = 0;
   I12 = 0;            
   delay(speed);

   //  B/
   PH1 = 0;
   I01 = 1;
   I11 = 1;

   PH2 = 0; 
   I02 = 0;
   I12 = 0;	                 
   delay(speed);

   //   A/B/
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
  	for(i =0 ; i <= 70; i++);
}

void main()
{
  while(1)
  {
    Go();  //步进电机运行	
  }
}
