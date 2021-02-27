/*
 这是点亮一个LED的初始化程序
*/

//引入 Led.h 头文件
#include "Led.h"

/*
函数名：LED_Init
函数功能：给点亮led所需的I/O口初始化
*/
void LED_Init(void){
	// 定义该结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
		// 开启 GPIOB 的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		// 需要定义的端口号为 PB0
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		// IO接口工作方式为 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		// IO接口输出速度为 50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 调用库函数完成初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, (BitAction)(1));
}
