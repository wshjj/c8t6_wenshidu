/*
	这是一个利用 TIM3 通用定时器的 PWM 输出程序
*/
// 引入 Pwm.h 头文件
#include "Pwm.h"

/*
	函数名：TIM3_GPIO_Config
	函数功能：定义设置 TIM3 通道1所需的 GPIO 口
*/
void pwm_GPIO_Config(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
		// 开启 TIM3 的外设时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		// 开启 GPIOB 的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		// 需要定义的端口号为 PA6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		// IO接口工作方式为 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		// IO接口输出速度为 50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 调用库函数完成初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
	函数名：TIM3_MODE_Config
	函数功能：定义设置 TIM3 通用定时器的工作状态
*/
void pwm_Init(void){
		// 初始化 TIM3 的时间基数单位
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 59999;
		TIM_TimeBaseStructure.TIM_Prescaler = 23;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
		// 初始化 TIM3 外设
		TIM_OCInitTypeDef TIM_OCInitStructure; 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC1Init(TIM3, & TIM_OCInitStructure);
		// 使能 TIM3 在 CCR1 上的预装载寄存器
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		// 使能 TIM3 在 ARR 上的预装载寄存器
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		// 使能 TIM3 定时器
		TIM_Cmd(TIM3, ENABLE);
}

/*
	函数名：pwm_Out
	函数功能：输出固定占空比的 PWM 波形（频率50Hz，周期20ms的方波）
*/
void pwm_Out(float val){
	TIM_SetCompare1(TIM3, (u16)(val*60000));
}

/*
	函数名：pwm_buzzer_start
	函数功能：输出一定频率的脉冲，传入频率值做参数（单位：KHz）
*/
void pwm_buzzer_start(float frequency){
	// 初始化 TIM3 的时间基数单位
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 1000;
		TIM_TimeBaseStructure.TIM_Prescaler = (u8)(72/frequency);
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
		// 初始化 TIM3 外设
		TIM_OCInitTypeDef TIM_OCInitStructure; 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_Pulse = 500;
		TIM_OC1Init(TIM3, & TIM_OCInitStructure);
		// 使能 TIM3 在 CCR1 上的预装载寄存器
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		// 使能 TIM3 在 ARR 上的预装载寄存器
		TIM_ARRPreloadConfig(TIM3, ENABLE);
		// 使能 TIM3 定时器
		TIM_Cmd(TIM3, ENABLE);
}

/*
	函数名：pwm_buzzer_end
	函数功能：停止输出给蜂鸣器的脉冲，变为始终是高电平
*/
void pwm_buzzer_end(void){
	TIM_SetCompare1(TIM3,1000);
}
