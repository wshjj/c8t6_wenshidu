/*
 这是点亮一个LED的初始化程序的头文件
*/

// 头文件的条件编译
#ifndef __Led_H
#define __Led_H

// 引入STM头文件
#include "stm32f10x.h"

// 定义开关的开断
#define ON 0
#define OFF 1

// 定义led开启和关闭的接口
#define FJ(a) GPIO_WriteBit(GPIOA, GPIO_Pin_3, (BitAction)(a));

// 定义led的初始化函数
void LED_Init(void);

#endif
