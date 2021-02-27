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
//�Լ���ӵ�
#define LED_E_G_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LED_E_G_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LED_E_R_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define LED_E_R_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define LED_E_B_ON()        GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LED_E_B_OFF()       GPIO_SetBits(GPIOA,GPIO_Pin_2)


/*****************************************************************************
�������� : RGB_LED_Init
�������� : RGB_LED��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void RGB_LED_Init(void);
/*****************************************************************************
�������� : LED_Control
�������� : LED����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void LED_Control(uint8_t Object,uint8_t State);
/*****************************************************************************
�������� : LED_RGB_Control
�������� : RGB_LED����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void LED_RGB_Control(uint8_t R, uint8_t G, uint8_t B);
/*****************************************************************************
�������� : RGB_Value_Set
�������� : RGB����ֵ����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void RGB_Value_Set(void);
/*****************************************************************************
�������� : RGB_Power_Control
�������� : RGB�ϵ����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void RGB_Power_Control(void);

#endif

