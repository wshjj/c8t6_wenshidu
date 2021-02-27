/*
	这是一个利用滴答定时器的延时程序的头文件
*/
// 头文件的条件编译
#ifndef __Delay_H
#define __Delay_H

// 引入STM头文件
#include "stm32f10x.h"

// 定义延时函数以及自减函数
void ticking_decrement(void);
void delay_us(u32 time_us);
void delay_ms(u16 time_ms);
void delay_s(u16 time_s);

#endif
