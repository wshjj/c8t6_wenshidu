/*
 这是使用 USART 与电脑进行通信的程序的头文件
*/

// 头文件的条件编译
#ifndef __Usart_H
#define __Usart_H

// 引入系统头文件
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
// 引入STM头文件
#include "stm32f10x.h"

// 全局定义 USART1 收到的字符数组以及长度
extern char receive_Con[1000];
extern u8 receive_Len;
extern u8 receive_Sta;

// 解决找不到 FILE 的问题
typedef struct __FILE FILE;

// 定义使用的第几个usart
#define USARTX USART1

// 定义 USART 初始化函数
void USART1_Init(u32 baudRate);

#endif
