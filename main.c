#include "stm32f10x.h"
void USART1_Init(void)
{
  
	 GPIO_InitTypeDef GPIO_InitStrue;
	 USART_InitTypeDef USART_InitStrue;
	 NVIC_InitTypeDef NVIC_InitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能串口时钟
	 RCC_APB2Periph_GPIOA, ENABLE);//使能 GPIOA 时钟
	
	 USART_DeInit(USART1); //复位串口 1
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	 GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
   
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化
	
	 USART_InitStructure.USART_BaudRate = bound; //波特率设置
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为 8 位
	 USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	 USART_Init(USART1, &USART_InitStructure); //初始化串口
	 #if EN_USART1_RX //如果使能了接收
	 
	 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级 3 
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3 //子优先级 3
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道使能
   NVIC_Init(&NVIC_InitStructure);//中断优先级初始化 
	 
	 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
   #endif
	 
	 USART_Cmd(USART1, ENABLE);//使能串口
}
void USART1_IRQHandler(void)//串口 1 中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收中断
		{
      Res =USART_ReceiveData(USART1);//读取接收到的数据
		}
}
