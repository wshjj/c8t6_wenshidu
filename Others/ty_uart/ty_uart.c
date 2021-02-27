/****************************************Copyright (c)*************************
**                               版权所有 (C), 2015-2020, 涂鸦科技
**
**                                 http://www.tuya.com
**
**--------------文件信息-------------------------------------------------------
**文   件   名: User_Uart.c
**描        述: uart用户函数
**使 用 说 明 : 无
**
**
**--------------当前版本修订---------------------------------------------------

** 版  本: v2.0
** 日　期: 2016年3月29日
** 描　述: 1:优化代码结构
**
**-----------------------------------------------------------------------------
******************************************************************************/
#define HAL_USER_UART_GLOBAL

#include "wifi.h"

//#define         DEBUG_IN_USART1                                               //通过USB-TTL调试


/*****************************************************************************
函数名称 : USART1_Init
功能描述 : USART1初始化
输入参数 : BaudRate:波特率
返回参数 : 初始化成功/失败
使用说明 : 无
*****************************************************************************/
uint8_t USART1_Init(uint32_t BaudRate)
{
  USART_InitTypeDef USART_InitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  if(BaudRate > 115200) 
  {                                            //波特率太高，错误返回
    return(ERROR);
  }
  
  // Enable GPIOA clocks 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // Enable USART1 clocks 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  /*
  *  USART1_TX -> PA9 , USART1_RX -> PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure); 
  //
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  //
  USART_ClearFlag(USART1,USART_FLAG_TC);
  
  //Enable the USART1 Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                             //指定中断源
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                            //指定响应优先级别
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //允许中断
  NVIC_Init(&NVIC_InitStructure);                                               //写入设置
  
  USART_Cmd(USART1, ENABLE);
  
  return(SUCCESS);
}
/*****************************************************************************
函数名称 : USART3_Init
功能描述 : USART3初始化
输入参数 : BaudRate:波特率
返回参数 : 初始化成功/失败
使用说明 : 无
*****************************************************************************/
uint8_t USART3_Init(uint32_t BaudRate)
{
  USART_InitTypeDef USART_InitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  if(BaudRate > 115200) 
  {                                            //波特率太高，错误返回
    return(ERROR);
  }
  
  // Enable GPIOA clocks 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // Enable USART1 clocks 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
  /*
  *  USART3_TX -> PB10 , USART13_RX -> PB11
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);		   
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure); 
  //
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  //
  USART_ClearFlag(USART3,USART_FLAG_TC);
  
  //Enable the USART3 Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;                             //指定中断源
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                            //指定响应优先级别
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //允许中断
  NVIC_Init(&NVIC_InitStructure);                                               //写入设置
  
  USART_Cmd(USART3, ENABLE);
  
  return(SUCCESS);
}
extern uint8_t Timer4_Value;
uint16_t uart_input_count;
uint8_t uart_input_finish;
/*****************************************************************************
函数名称 : USART1_IRQHandler
功能描述 : USART1串口中断函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void USART1_IRQHandler(void)
{
  uint8_t ch;
  
  //接收中断
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    ch = USART_ReceiveData(USART1);
    
#ifdef DEBUG_IN_USART1
    //将接收到字节数据传入uart_receive_input
    uart_receive_input(ch);
#endif
  }
}

/*****************************************************************************
函数名称 : USART1_IRQHandler
功能描述 : USART1串口中断函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void USART3_IRQHandler(void)
{
  uint8_t ch;
  
  //接收中断
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    ch = USART_ReceiveData(USART3);

#ifndef DEBUG_IN_USART1
    //将接收到字节数据传入uart_receive_input
    uart_receive_input(ch);                                                      //使能TIMx
#endif
  }
}
/*****************************************************************************
函数名称 : Uart_PutChar
功能描述 : 串口发送函数
输入参数 : ch:待发送数据
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void Uart_PutChar(uint8_t ch)
{
#ifdef DEBUG_IN_USART1
  //发送
  USART_SendData(USART1,ch);
  //
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
#else
  //发送
  USART_SendData(USART3,ch);
  //
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
#endif
}
