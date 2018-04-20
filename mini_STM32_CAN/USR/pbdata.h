#ifndef _pbdata__H
#define _pbdata__H

#include "stm32f10x.h"
#include "stm32f10x_it.h"	 
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stdio.h"
#include "stm32f10x_can.h"
//定义变量



extern u8  dt;


//定义函数

void delay(u32 nCount);
void delay_US(u32 nus);
void delay_mS(u32 nms);


#endif
