#include "pbdata.h"

u8 dt=0;

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);


}


void delay_US(u32 nus)
{
  u32 temp;
	SysTick->LOAD = 9*nus;
	SysTick->VAL = 0X00;
  SysTick->CTRL = 0X01;
	do
	{
    temp =  SysTick->CTRL;
  }while((temp&0x01)&&(!(temp&(1<<16))));
	
	SysTick->CTRL = 0X00;
	SysTick->VAL = 0X00;
				
}


void delay_mS(u32 nms)
{
  u32 temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL = 0X00;
  SysTick->CTRL = 0X01;
	do
	{
    temp =  SysTick->CTRL;
  }while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL = 0X00;
	SysTick->VAL = 0X00;
				
}

