/*
这是一个按键的初始化程序
*/

// 引入 Key.h 头文件
#include "Key.h"

/*
函数名：KEY_Init
函数功能：给按键所需的I/O口初始化
*/
void KEY_Init(void){
	// 定义该结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
		// 开启 GPIOB 的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		// 需要定义的端口号为 PB1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		// IO接口工作方式为 上拉输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	// 调用库函数完成初始化
	GPIO_Init(GPIOC, &GPIO_InitStructure);			
}

/*
函数名：KEY_Listen
函数功能：监听按键所接 IO 口上输入数据
*/
u8 KEY_Listen(void){
	int n = 10000;
	// 按键是否按下
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == down){
		// 延时消抖
		while(n--);
		// 按键是否按下
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == down){
			// 等待按键松开
			while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == down);
			// 返回按下
			return down;
		}
		else{
			// 只是抖动，返回未按下
			return up;
		}
	}
	else{
		// 按键没被按下，返回未按下
		return up;
	}
}
