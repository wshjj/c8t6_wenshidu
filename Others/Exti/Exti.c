/*
 这是exti外部中断配置程序
*/

// 引入 Exti.h 头文件
#include "Exti.h"

/*
 函数名：NVIC_Init
 函数功能：配置外部中断控制器 NVIC 的参数
*/
static void NVIC_Configuration(void){
	// 定义 NVIC 结构体
	NVIC_InitTypeDef NVIC_InitStructure;
		// 中断优先级设为第一组
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		// IQR 通道为外部中断线 9-5 中断
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		// 设置先占优先级为0
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		// 设置从优先级为0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		// IQR 通道设为使能
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		// 完成初始化
		NVIC_Init(&NVIC_InitStructure);
}

/*
 函数名：EXTI_PC5_Init
 函数功能：配置 PB5 IO口为外部中断口，并设置优先级
*/
void EXTI_PC5_Init(void){
	// 定义 GPIO 结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
	// 定义 EXTI 结构体
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	// 开启 GPIOB 的外设时钟和 AFIO 时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	// NVIC 初始化
	NVIC_Configuration();
	// 需要定义的端口号为 PC5
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	// IO接口工作方式为 上拉输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	// 调用库函数完成初始化
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// 选择 PC5 用于外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
	// EXTI 选择线路5
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	// EXTI 模式选择中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	// EXTI 触发的方式为下降沿触发
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	// 选中线路的状态设为使能
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	// 完成初始化
	EXTI_Init(&EXTI_InitStructure);
}
