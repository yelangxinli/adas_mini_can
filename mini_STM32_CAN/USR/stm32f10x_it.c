/**
  ******************************************************************************
  * @file GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"	 
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "pbdata.h"

void NMI_Handler(void)
{
}

void USART1_IRQHandler(void){
	 u16 k;

if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //ÅÐ¶ÏÖÐ¶Ï±êÊ¶Î»
	{
   k= USART_ReceiveData(USART1);
	 USART_SendData(USART1, k);
	 while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET);  
		USART_ClearFlag(USART1,USART_FLAG_TC);
}  	
}

void USART2_IRQHandler(void)
{
	 u16 k;

if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //ÅÐ¶ÏÖÐ¶Ï±êÊ¶Î»
	{
   k= USART_ReceiveData(USART2);
	 USART_SendData(USART2, k);
	 while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)== RESET);
  
		USART_ClearFlag(USART2,USART_FLAG_TC);

}
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}
/*
void TIM3_IRQHandler(void)
{
     TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	 if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7) == Bit_RESET)
	 {

     if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_10) == Bit_RESET)
		 {
			 //LEDÏ¨Ã
			  GPIO_SetBits(GPIOD, GPIO_Pin_10 );   
     }
		 else
		 {
			 //LED·¢¹â
			  GPIO_ResetBits(GPIOD, GPIO_Pin_10  );  
     }
    }	
  }

*/


/****************************************************************************
* Ãû    ³Æ£ºvoid EXTI9_5_IRQHandler(void)
* ¹¦    ÄÜ£ºEXTI9-5ÖÐ¶Ï´¦Àí³ÌÐò
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºÎÞ 
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus( EXTI_Line7) == SET)
	{
     EXTI_ClearITPendingBit(EXTI_Line7);
		 delay_mS(10);
	 if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7) == Bit_RESET)
	 {

     if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_10) == Bit_RESET)
		 {
			 //LEDÏ¨Ã
			  GPIO_SetBits(GPIOD, GPIO_Pin_10 );   
     }
		 else
		 {
			 //LED·¢¹â
			  GPIO_ResetBits(GPIOD, GPIO_Pin_10  );  
     }
    }	
  }
}

/****************************************************************************
* Ãû    ³Æ£ºvoid EXTI1_IRQHandler(void)
* ¹¦    ÄÜ£ºEXTI2ÖÐ¶Ï´¦Àí³ÌÐò
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºÎÞ 
****************************************************************************/
void EXTI1_IRQHandler(void)
{
    
}

/****************************************************************************
* Ãû    ³Æ£ºvoid EXTI2_IRQHandler(void)
* ¹¦    ÄÜ£ºEXTI2ÖÐ¶Ï´¦Àí³ÌÐò
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºÎÞ 
****************************************************************************/
void EXTI2_IRQHandler(void)
{
    
}

/****************************************************************************
* Ãû    ³Æ£ºvoid EXTI3_IRQHandler(void)
* ¹¦    ÄÜ£ºEXTI3ÖÐ¶Ï´¦Àí³ÌÐò
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºÎÞ 
****************************************************************************/
void EXTI3_IRQHandler(void)
{
   
}




/*
void USB_LP_CAN1_RX0_IRQHandler(void)
{
   CanRxMsg RxMessage;
	 CanTxMsg TxMessage;
	//CAN½ÓÊÕ
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	
	TxMessage.StdId =RxMessage.StdId;
	TxMessage.ExtId =RxMessage.ExtId;
	TxMessage.IDE   =RxMessage.IDE;
	TxMessage.RTR   =RxMessage.RTR;
	TxMessage.DLC   =RxMessage.DLC;
	
	TxMessage.Data[0] = RxMessage.Data[0];
	TxMessage.Data[1] = RxMessage.Data[1];
	TxMessage.Data[2] = RxMessage.Data[2];
	TxMessage.Data[3] = RxMessage.Data[3];
	TxMessage.Data[4] = RxMessage.Data[4];
	TxMessage.Data[5] = RxMessage.Data[5];
	TxMessage.Data[6] = RxMessage.Data[6];
	TxMessage.Data[7] = RxMessage.Data[7];
	//CAN·¢ËÍ
  CAN_Transmit(CAN1,&TxMessage);
	
	
}
*/



void CAN1_RX0_IRQHandler(void)
{
  	CanRxMsg RxMessage;
	int i=0;
    CAN_Receive(CAN1, 0, &RxMessage);
	for(i=0;i<8;i++)
	printf("CAN1rxbuf[%d]:%d\r\n",i,RxMessage.Data[i]);
}



void CAN2_RX1_IRQHandler(void)
{
  	CanRxMsg RxMessage;
	int i=0;
    CAN_Receive(CAN2, 1, &RxMessage);
	for(i=0;i<8;i++)
	printf("CAN2rxbuf[%d]:%d\r\n",i,RxMessage.Data[i]);
}












