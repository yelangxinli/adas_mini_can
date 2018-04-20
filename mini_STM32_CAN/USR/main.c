#include "pbdata.h"
void RCC_Conifiguration(void);
void GPIO_Conifiguration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);
void CAN1_Config_100KHZ(void);
void CAN1_Config_500KHZ(void);
void CAN2_Config_100KHZ(void);
void CAN2_Config_500KHZ(void);
u8 Can1_Send_Msg(u8* msg,u8 len);
u8 Can2_Send_Msg(u8* msg,u8 len);


#define LED_SET() GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define LED_RST() GPIO_ResetBits(GPIOC,GPIO_Pin_11)

int fputc(int ch, FILE *F)
{
     USART_SendData(USART1,(u8)ch);
	   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET);
	   return ch;
}

RCC_ClocksTypeDef tRCC_Clocks;

u8 Can1_Send_Msg(u8* msg,u8 len)
{
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x378;			// 标准标识符 
	TxMessage.ExtId=0x12;			// 设置扩展标示符 
	TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=len;				// 要发送的数据长度
	printf("Can1_Send_Msg\r\n");
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	 
}

u8 Can2_Send_Msg(u8* msg,u8 len)
{
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=0x378;			// 标准标识符 
	TxMessage.ExtId=0x12;			// 设置扩展标示符 
	TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=len;				// 要发送的数据长度
	printf("Can2_Send_Msg\r\n");
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CAN2, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	 
}
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
//u8 canbuf[8] = {0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0};		//用于CAN SENSOR PCBA测试
u8 canbuf[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};     //用于CAN开机
int main(void)
{
//  CanRxMsg RxMessage;
	
	RCC_Conifiguration();//系统时钟初始化	
	RCC_GetClocksFreq(& tRCC_Clocks);
	GPIO_Conifiguration();//端口初始化
	USART_Configuration();
	
  NVIC_Configuration();//配置中断优先级
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2
	TIM_DeInit(TIM2);
	/* TIM2 configuration */
	TIM_TimeBaseStructure.TIM_Period = 50000-1;        //    50000*20us = 1000ms
	TIM_TimeBaseStructure.TIM_Prescaler = 1440-1;    // 分频720  72Mhz/720 = 200khz = 20us/计数      
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向，向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	 /* Clear TIM2 update pending flag[清楚TIM2溢出中断标志] */
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	/* Enable TIM2 Update interrupt [TIM2中断允许]*/
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
	/* TIM2 enable counter [允许tim2计数]*/
	//TIM_Cmd(TIM2, ENABLE);    
	//STM_EVAL_COMInit(COM1, &USART_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器2
	TIM_DeInit(TIM3);
	/* TIM2 configuration */
	TIM_TimeBaseStructure.TIM_Period = 50000-1;        //    50000*20us = 1000ms
	TIM_TimeBaseStructure.TIM_Prescaler = 1440-1;    // 分频720  36Mhz/720 = 50khz = 20us/计数      
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向，向上计数
	//TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	 /* Clear TIM2 update pending flag[清楚TIM2溢出中断标志] */
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	/* Enable TIM2 Update interrupt [TIM2中断允许]*/
	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
	/* TIM2 enable counter [允许tim2计数]*/
	//TIM_Cmd(TIM3, ENABLE);    
	//STM_EVAL_COMInit(COM1, &USART_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	//while(1)
	//{
		//printf("A");
	
	//}
	
	while(1)
	{
		CAN1_Config_100KHZ();
		CAN2_Config_100KHZ();
		Can2_Send_Msg(canbuf,8);
		delay_mS(100); 
		Can1_Send_Msg(canbuf,8);
		delay_mS(100);
		
		CAN1_Config_500KHZ();
		CAN2_Config_500KHZ();
		Can2_Send_Msg(canbuf,8);
		delay_mS(100); 
		Can1_Send_Msg(canbuf,8);
		delay_mS(100);
	}
}

u8 canbuf_500KHZ[8] = {0,0,0,0,0,0xff,0xff,0xff};
int TIM2_Flag=0;
void TIM2_IRQHandler(void)
{
	//__asm("CPSID  I");//关中断
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	if(TIM2_Flag ==0)
	{
		CAN1_Config_100KHZ();
		Can1_Send_Msg(canbuf,8);
		TIM2_Flag=1;
		printf("100KHZ\r\n");
	}
	else
	{
		CAN1_Config_500KHZ();
		Can1_Send_Msg(canbuf,8);
		TIM2_Flag=0;
		printf("500KHZ\r\n");
	}
		
		//if((timeflag % 2) == 0)
		//{/*
			//GPIOC ->ODR =   GPIO_Pin_13;	//熄灭(LED共阳极)
			//USART1_Puts("light on---");
			//Uart1_sendTime2_Valud((uint16_t)TIM2->CNT);
			//USART1_Puts("\r\n");*/
			//TIM_Cmd(TIM3, ENABLE); 
		//}
		//else
		//{/*
			//GPIOC ->ODR &= ~GPIO_Pin_13 ;	//点亮(LED共阳极)
			//USART1_Puts("light off---");
			//Uart1_sendTime2_Valud((uint16_t)TIM2->CNT);
			//USART1_Puts("\r\n");*/
			//TIM_Cmd(TIM3, DISABLE); 
		//}
}
int TIM3_Flag = 0;
void TIM3_IRQHandler(void)
{
	//__asm("CPSID  I");//关中断
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	if(TIM3_Flag ==0)
	{
		CAN2_Config_100KHZ();
		Can2_Send_Msg(canbuf,8);
		TIM3_Flag=1;
		printf("100KHZ\r\n");
	}
	else
	{
		CAN2_Config_500KHZ();
		Can2_Send_Msg(canbuf,8);
		TIM3_Flag=0;
		printf("500KHZ\r\n");
	}
		
		//if((timeflag % 2) == 0)
		//{/*
			//GPIOC ->ODR =   GPIO_Pin_13;	//熄灭(LED共阳极)
			//USART1_Puts("light on---");
			//Uart1_sendTime2_Valud((uint16_t)TIM2->CNT);
			//USART1_Puts("\r\n");*/
			//TIM_Cmd(TIM3, ENABLE); 
		//}
		//else
		//{/*
			//GPIOC ->ODR &= ~GPIO_Pin_13 ;	//点亮(LED共阳极)
			//USART1_Puts("light off---");
			//Uart1_sendTime2_Valud((uint16_t)TIM2->CNT);
			//USART1_Puts("\r\n");*/
			//TIM_Cmd(TIM3, DISABLE); 
		//}
}



void RCC_Conifiguration(void)
{
  SystemInit();  	
}

void GPIO_Conifiguration(void)
{
	GPIO_InitTypeDef     GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO  , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//串口1端口映射
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE); 
	//串口IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//指示灯IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;

   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 NVIC_InitStructure.NVIC_IRQChannel =CAN1_RX0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
		
	 NVIC_InitStructure.NVIC_IRQChannel =CAN2_RX1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(void)
{	
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		USART_Init(USART1, &USART_InitStructure);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART1, ENABLE);
		USART_ClearFlag(USART1,USART_FLAG_TC);
}

void CAN1_Config_500KHZ(void)
{
  GPIO_InitTypeDef  			GPIO_InitStructure;
  CAN_InitTypeDef     		CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;

  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  /* CANx Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* CAN register init */
  CAN_DeInit(CAN1);
	
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

	/* 波特率500K */
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 12;

  CAN_Init(CAN1, &CAN_InitStructure);

	/* No filter */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
	CAN_ITConfig(CAN1, CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0 | CAN_IT_ERR, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);
}

void CAN1_Config_100KHZ(void)
{
  GPIO_InitTypeDef  			GPIO_InitStructure;
  CAN_InitTypeDef     		CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;

  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  /* CANx Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1 , ENABLE);
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* CAN register init */
  CAN_DeInit(CAN1);
	
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

	/* 波特率500K */
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 60;

  CAN_Init(CAN1, &CAN_InitStructure);

	/* No filter */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
	CAN_ITConfig(CAN1, CAN_IT_FMP0 | CAN_IT_FF0 | CAN_IT_FOV0 | CAN_IT_ERR, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);
}


void CAN2_Config_500KHZ(void)
{
  GPIO_InitTypeDef  			GPIO_InitStructure;
  CAN_InitTypeDef     		CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  /* CANx Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* CAN register init */
  CAN_DeInit(CAN2);
	
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

 /* 波特率500K */
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 12;

  CAN_Init(CAN2, &CAN_InitStructure);

	/* No filter */
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN2, CAN_IT_FMP1 | CAN_IT_FF1 | CAN_IT_FOV1 | CAN_IT_ERR, ENABLE);
}

void CAN2_Config_100KHZ(void)
{
  GPIO_InitTypeDef  			GPIO_InitStructure;
  CAN_InitTypeDef     		CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  /* CANx Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* CAN register init */
  CAN_DeInit(CAN2);
	
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

 /* 波特率500K */
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 60;

  CAN_Init(CAN2, &CAN_InitStructure);

	/* No filter */
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN2, CAN_IT_FMP1 | CAN_IT_FF1 | CAN_IT_FOV1 | CAN_IT_ERR, ENABLE);
}











