/*
 这是一个按键的初始化程序的头文件
*/

// 头文件的条件编译
#ifndef __Key_H
#define __Key_H

// 引入STM头文件
#include "stm32f10x.h"

// 定义按键的按下
#define up 1
#define down 0

// 定义led的初始化函数
void KEY_Init(void);
u8 KEY_Listen(void);

#endif
