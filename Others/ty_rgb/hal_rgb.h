#ifndef _HAL_RGB_LED_H
#define _HAL_RGB_LED_H

#include "stm32f10x.h"

#define         LED1           1
#define         LED2           2


#define LED2_ON()        GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define LED2_OFF()       GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define LED1_ON()        GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define LED1_OFF()       GPIO_SetBits(GPIOB,GPIO_Pin_6)


#define LED_G_ON()        GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define LED_G_OFF()       GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define LED_R_ON()        GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define LED_R_OFF()       GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define LED_B_ON()        GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LED_B_OFF()       GPIO_SetBits(GPIOB,GPIO_Pin_9)

/*
#define LED_G_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED_G_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LED_R_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define LED_R_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LED_B_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LED_B_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_2)
*/
//自己添加的
#define LED_E_G_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED_E_G_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LED_E_R_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define LED_E_R_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LED_E_B_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LED_E_B_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_2)


/*****************************************************************************
函数名称 : RGB_LED_Init
功能描述 : RGB_LED初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_LED_Init(void);
/*****************************************************************************
函数名称 : LED_Control
功能描述 : LED控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void LED_Control(uint8_t Object,uint8_t State);
/*****************************************************************************
函数名称 : LED_RGB_Control
功能描述 : RGB_LED控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void LED_RGB_Control(uint8_t R, uint8_t G, uint8_t B);
/*****************************************************************************
函数名称 : RGB_Value_Set
功能描述 : RGB亮度值设置
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_Value_Set(void);
/*****************************************************************************
函数名称 : RGB_Power_Control
功能描述 : RGB上电控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_Power_Control(void);

#endif

