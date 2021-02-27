/*
 这是使用 USART 与电脑进行通信的程序
*/

// 引入头文件
#include "Usart.h"

// 全局定义 USART1 收到的字符数组以及长度和接收是否完成
char receive_Con[1000];
u8 receive_Len = 0;
u8 receive_Sta = 0;

// 重写 printf 函数
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数                 
struct __FILE {
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x){
	x = x;
} 
//重定义fputc函数
int fputc(int ch, FILE *f){
	//循环发送,直到发送完毕
	while((USARTX->SR&0X40)==0);
    USARTX->DR = (u8) ch;
	return ch;
}
#endif

void USART1_Init(u32 baudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	// GPIO端口设置
	// 定义PA9为复用推挽输出（RX1）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 定义PA9为浮空输入（TX1）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	// USART初始化设置
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	USART_Init(USART1, &USART_InitStructure);
	
	// 使能 USART1 的接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// 使能 USART1
	USART_Cmd(USART1, ENABLE);
}
