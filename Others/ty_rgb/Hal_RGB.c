/****************************************Copyright (c)*************************
**                               版权所有 (C), 2015-2020, 涂鸦科技
**
**                                 http://www.tuya.com
**
**--------------文件信息-------------------------------------------------------
**文   件   名: Hal_RGB.c
**描        述: RGB接口处理
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
#define HAL_RGB_GLOBAL
#include "hal_rgb.h"
#include "wifi.h"

uint8_t light_r,light_g,light_b;
extern TYPE_BUFFER_S FlashBuffer;

/*****************************************************************************
函数名称 : RGB_LED_Init
功能描述 : RGB_LED初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

//自己定义的引脚	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
   
  LED1_OFF();
  LED2_OFF();

  LED_R_OFF();                       //R
  LED_G_OFF();                       //G
  LED_B_OFF();                       //B
	

  LED_E_R_OFF();                       //R
  LED_E_G_OFF();                       //G
  LED_E_B_OFF();                       //B
}
/*****************************************************************************
函数名称 : LED_Control
功能描述 : LED控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void LED_Control(uint8_t Object,uint8_t State)
{
  switch(Object)
  {
  case LED1:
    if(State == 1)
      LED1_ON();
    else
      LED1_OFF();
    break;
    
  case LED2:
    if(State == 1)
      LED2_ON();
    else
      LED2_OFF();
    break;
    
  default:
    if(State == 1)
      LED1_ON();
    else
      LED1_OFF();
    break;    
  }
}
  extern uint32_t Timer2_Value;

/*****************************************************************************
函数名称 : LED_RGB_Control
功能描述 : RGB_LED控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void LED_RGB_Control(uint8_t R, uint8_t G, uint8_t B)
{
  TIM_Cmd(TIM2, DISABLE);                                                        //使能TIMx
  Timer2_Value = 0;
  
  light_r = 0;
  light_g = 0;
  light_b = 0;
  
  
  if(R > 0)
  {
    light_r = R;
    LED_R_ON();
  }
  else
    LED_R_OFF();
  
  if(G > 0)
  {
    light_g = G;
    LED_G_ON();
  }
  else
    LED_G_OFF();
  
  if(B > 0)
  {
    light_b = B;
    LED_B_ON();
  }  
  else
    LED_B_OFF();
  
  TIM_Cmd(TIM2, ENABLE);                                                        //使能TIMx
}
/*****************************************************************************
函数名称 : RGB_Value_Set
功能描述 : RGB亮度值设置
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_Value_Set(void)
{
  if(light_r > 0)
  {
    if(Timer2_Value == light_r)
    {
      LED_R_OFF();
    }
  }

  if(light_g > 0)
  {
    if(Timer2_Value == light_g)
    {
      LED_G_OFF();
    }
  }

  if(light_b > 0)
  {
    if(Timer2_Value == light_b)
    {
      LED_B_OFF();
    }
  }
  
  if(Timer2_Value >= 270)
  {
    Timer2_Value  = 0;

    if(light_r > 0)
    {
      LED_R_ON();
    }
    
    if(light_g > 0)
    {
      LED_G_ON();
    }
    
    if(light_b > 0)
    {
      LED_B_ON();
    }  
  }
}
/*****************************************************************************
函数名称 : RGB_Power_Control
功能描述 : RGB上电控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void RGB_Power_Control(void)
{
  uint8_t colour_r,colour_g,colour_b;
  
  if(FlashBuffer.led_switch == 0)
  {
    //开关关
    LED_RGB_Control(0,0,0);
  }
  else
  {
    //开关开
    switch(FlashBuffer.work_mode)
    {
    case 0:
      LED_RGB_Control(FlashBuffer.bright_value,FlashBuffer.bright_value,FlashBuffer.bright_value);
      break;
      
    case 1:
      colour_r = hex_to_bcd(FlashBuffer.colour[0],FlashBuffer.colour[1]);
      colour_g = hex_to_bcd(FlashBuffer.colour[2],FlashBuffer.colour[3]);
      colour_b = hex_to_bcd(FlashBuffer.colour[4],FlashBuffer.colour[5]);
      LED_RGB_Control(colour_r,colour_g,colour_b);
      break;
      
    case 2:
      colour_r = hex_to_bcd(FlashBuffer.scene[0],FlashBuffer.scene[1]);
      colour_g = hex_to_bcd(FlashBuffer.scene[2],FlashBuffer.scene[3]);
      colour_b = hex_to_bcd(FlashBuffer.scene[4],FlashBuffer.scene[5]);
      LED_RGB_Control(colour_r,colour_g,colour_b);
      break;
    }
  }
}