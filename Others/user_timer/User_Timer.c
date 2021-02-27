/****************************************Copyright (c)*************************
**                               版权所有 (C), 2015-2020, 涂鸦科技
**
**                                 http://www.tuya.com
**
**--------------文件信息-------------------------------------------------------
**文   件   名: User_Timer.c
**描        述: Timer用户函数
**使 用 说 明 : 无
**
**
**--------------当前版本修订---------------------------------------------------

** 版  本: v2.0
** 日　期: 2016年3月29日
** 描　述: 1:优化代码结构
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
函数名称 : TIM2_IRQHandler
功能描述 : TIM2中断处理
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void TIM2_IRQHandler(void)   				
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //?ì2éTIM3?üD??D??·￠éúó?·?
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //??3yTIMx?üD??D??±ê?? 
    Timer2_Value ++;
    
    RGB_Value_Set();
  }
}  

/*****************************************************************************
函数名称 : Get_Count_Value
功能描述 : 获取Tim2值
输入参数 : 无
返回参数 : Time2计数值
使用说明 : 无
*****************************************************************************/
uint32_t Get_Count_Value(void)
{
  return Timer_Count_Value;
}
/*****************************************************************************
函数名称 : TIM2_Count_Init
功能描述 : TIM2计数初始化
输入参数 : arr:计数初始值/pse:预分频值
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void TIM2_Count_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                          //时钟使能
  TIM_DeInit(TIM2);
  
  //50us
   
  //定时器TIM2初始化
  TIM_TimeBaseStructure.TIM_Period = 35;                                       //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
  TIM_TimeBaseStructure.TIM_Prescaler = 99;                                    //设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                       //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                   //TIM向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                               //根据指定的参数初始化TIMx的时间基数单位

  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                                      //使能指定的TIM2中断,允许更新中断

  //中断优先级NVIC设置
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                               //TIM2中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                            //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                                               //初始化NVIC寄存器 
  
  Timer2_Value = 0;

  TIM_Cmd(TIM2, DISABLE);                                                        //使能TIMx
}
/*****************************************************************************
函数名称 : TIM2_IRQHandler
功能描述 : TIM2中断处理
输入参数 : 无
返回参数 : 无
使用说明 : 无
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
函数名称 : Get_Time3_Value
功能描述 : 获取Tim3值
输入参数 : 无
返回参数 : Time2计数值
使用说明 : 无
*****************************************************************************/
uint32_t Get_Time3_Value(void)
{
  return Timer3_Value;
}
/*****************************************************************************
函数名称 : TIM3_Count_Init
功能描述 : TIM3计数初始化
输入参数 : arr:计数初始值/pse:预分频值
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void TIM3_Count_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                          //时钟使能
  TIM_DeInit(TIM3);
   
  //定时器TIM2初始化
  TIM_TimeBaseStructure.TIM_Period = arr;                                       //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                                    //设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                       //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                   //TIM向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                               //根据指定的参数初始化TIMx的时间基数单位

  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                                      //使能指定的TIM2中断,允许更新中断

  //中断优先级NVIC设置
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                               //TIM2中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                     //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;                            //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                                               //初始化NVIC寄存器 
  
  Timer_Count_Value = 0;
  Timer3_Value = 0;

  TIM_Cmd(TIM3, ENABLE);                                                        //使能TIMx
}
