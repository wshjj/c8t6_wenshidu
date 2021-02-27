/****************************************Copyright (c)*************************
**                               ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                                 http://www.tuya.com
**
**--------------�ļ���Ϣ-------------------------------------------------------
**��   ��   ��: User_Timer.c
**��        ��: Timer�û�����
**ʹ �� ˵ �� : ��
**
**
**--------------��ǰ�汾�޶�---------------------------------------------------

** ��  ��: v2.0
** �ա���: 2016��3��29��
** �衡��: 1:�Ż�����ṹ
**
**-----------------------------------------------------------------------------
******************************************************************************/
#define HAL_USER_TIMER_GLOBAL
#include "user_timer.h"

#include "wifi.h"

uint32_t Timer2_Value = 0;
uint32_t Timer_Count_Value = 0;
static uint32_t Timer3_Value = 0;
uint8_t Timer4_Value = 0;
static uint8_t System_Sec_Flag = 0;


/*****************************************************************************
�������� : TIM2_IRQHandler
�������� : TIM2�жϴ���
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void TIM2_IRQHandler(void)   				
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //?��2��TIM3?��D??D??���騦����?��?
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //??3yTIMx?��D??D??����?? 
    Timer2_Value ++;
    
    RGB_Value_Set();
  }
}  

/*****************************************************************************
�������� : Get_Count_Value
�������� : ��ȡTim2ֵ
������� : ��
���ز��� : Time2����ֵ
ʹ��˵�� : ��
*****************************************************************************/
uint32_t Get_Count_Value(void)
{
  return Timer_Count_Value;
}
/*****************************************************************************
�������� : TIM2_Count_Init
�������� : TIM2������ʼ��
������� : arr:������ʼֵ/pse:Ԥ��Ƶֵ
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void TIM2_Count_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                          //ʱ��ʹ��
  TIM_DeInit(TIM2);
  
  //50us
   
  //��ʱ��TIM2��ʼ��
  TIM_TimeBaseStructure.TIM_Period = 35;                                       //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
  TIM_TimeBaseStructure.TIM_Prescaler = 99;                                    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                       //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                   //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                               //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                                      //ʹ��ָ����TIM2�ж�,��������ж�

  //�ж����ȼ�NVIC����
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                               //TIM2�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //��ռ���ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                            //�����ȼ�3��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //IRQͨ����ʹ��
  NVIC_Init(&NVIC_InitStructure);                                               //��ʼ��NVIC�Ĵ��� 
  
  Timer2_Value = 0;

  TIM_Cmd(TIM2, DISABLE);                                                        //ʹ��TIMx
}
/*****************************************************************************
�������� : TIM2_IRQHandler
�������� : TIM2�жϴ���
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void TIM3_IRQHandler(void)   				
{
  static uint8_t cnt = 0;
  static uint8_t color = 0;
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    
    Timer_Count_Value ++;

    if(Timer_Count_Value % 250 == 0) 
    {
      Timer3_Value ++;
      if(Timer3_Value == 12)
      {
        Timer3_Value = 0;
      }  
    }
  }
}  

/*****************************************************************************
�������� : Get_Time3_Value
�������� : ��ȡTim3ֵ
������� : ��
���ز��� : Time2����ֵ
ʹ��˵�� : ��
*****************************************************************************/
uint32_t Get_Time3_Value(void)
{
  return Timer3_Value;
}
/*****************************************************************************
�������� : TIM3_Count_Init
�������� : TIM3������ʼ��
������� : arr:������ʼֵ/pse:Ԥ��Ƶֵ
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void TIM3_Count_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                          //ʱ��ʹ��
  TIM_DeInit(TIM3);
   
  //��ʱ��TIM2��ʼ��
  TIM_TimeBaseStructure.TIM_Period = arr;                                       //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                                    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                       //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                   //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                               //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                                      //ʹ��ָ����TIM2�ж�,��������ж�

  //�ж����ȼ�NVIC����
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                               //TIM2�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //��ռ���ȼ�0��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;                            //�����ȼ�3��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //IRQͨ����ʹ��
  NVIC_Init(&NVIC_InitStructure);                                               //��ʼ��NVIC�Ĵ��� 
  
  Timer_Count_Value = 0;
  Timer3_Value = 0;

  TIM_Cmd(TIM3, ENABLE);                                                        //ʹ��TIMx
}
