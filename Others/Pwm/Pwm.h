/*
	这是一个利用 TIM3 通用定时器的 PWM 输出程序的头文件
*/
// 头文件的条件编译
#ifndef __Pwm_H
#define __Pwm_H

// 引入STM头文件
#include "stm32f10x.h"

// 宏定义舵机按角度旋转的函数
#define duoji(a) TIM_SetCompare1(TIM3,(u16)(1500+100*a/3));

// 定义 TIM 初始化函数和 PWM 输出函数
void pwm_GPIO_Config(void);
void pwm_Init(void);
void pwm_Out(float val);
void pwm_buzzer_start(float frequency);
void pwm_buzzer_end(void);

#endif
