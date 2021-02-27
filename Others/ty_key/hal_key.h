#ifndef __HAL_KEY_H__
#define __HAL_KEY_H__

#include "stm32f10x.h"

#define GPIO_KEY1_CLK    RCC_APB2Periph_GPIOA
#define GPIO_KEY1_PORT   GPIOA
#define GPIO_KEY1_PIN    GPIO_Pin_11

#define GPIO_KEY2_CLK    RCC_APB2Periph_GPIOA
#define GPIO_KEY2_PORT   GPIOA
#define GPIO_KEY2_PIN    GPIO_Pin_12


#define MAX_KEY         2
#define PRESS_KEY1      0x01
#define PRESS_KEY2      0x02

#define KEY_NO          0x00
#define KEY_DOWN        0x10  	
#define KEY_UP          0x20   
#define KEY_LONG        0x40

#define TIME_PRESS_LONG         (3 * 1000)
#define TIME_PRESS_SHORT        50


/*****************************************************************************
函数名称 : Get_RGB2_State
功能描述 : RGB2状态
输入参数 : 无
返回参数 : RGB2开关状态
使用说明 : 无
*****************************************************************************/
uint8_t Get_RGB2_State(void);

/*****************************************************************************
函数名称 : KEY_Init
功能描述 : KEY初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void KEY_Init(void);

/*****************************************************************************
函数名称 : Key_Scan
功能描述 : 扫描按键
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void Key_Scan(void);

#endif

