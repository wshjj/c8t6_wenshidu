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
�������� : Get_RGB2_State
�������� : RGB2״̬
������� : ��
���ز��� : RGB2����״̬
ʹ��˵�� : ��
*****************************************************************************/
uint8_t Get_RGB2_State(void);

/*****************************************************************************
�������� : KEY_Init
�������� : KEY��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void KEY_Init(void);

/*****************************************************************************
�������� : Key_Scan
�������� : ɨ�谴��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Key_Scan(void);

#endif

