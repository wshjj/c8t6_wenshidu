/****************************************Copyright (c)*************************
**                               ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                                 http://www.tuya.com
**
**--------------�ļ���Ϣ-------------------------------------------------------
**��   ��   ��: Hal_Key.c
**��        ��: �����ӿڴ���
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
#define HAL_KEY_GLOBAL

#include "hal_key.h"
#include "hal_rgb.h"
#include "user_timer.h"
#include "wifi.h"

typedef void (* KEY_HANDLE)(void);
typedef struct
{
  uint8_t Status;
  uint32_t Press_Time;
  KEY_HANDLE Short_Press_Handle;
  KEY_HANDLE Long_Press_Handle;
} KEY_STATE_T;

static KEY_STATE_T Key_State[2];
extern TYPE_BUFFER_S FlashBuffer;
uint8_t wifi_test_mode = 0;                                                  //����ģʽ

/*****************************************************************************
�������� : Key1_ShortPress_Handle
�������� : Key1�̰�������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key1_ShortPress_Handle(void)
{
  uint8_t colour_r,colour_g,colour_b;
  
  //��ǰ����ģʽʧ��
  if(wifi_test_mode == 1)
    return;
  
  if(FlashBuffer.led_switch == 0)
  {
    FlashBuffer.led_switch = 1;
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
  else
  {
    FlashBuffer.led_switch = 0;
    LED_RGB_Control(0,0,0);
  }
  
  //mcu_dp_bool_update(DPID_LED_SWITCH,FlashBuffer.led_switch);
}
/*****************************************************************************
�������� : Key1_LongPress_Handle
�������� : Key1����������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key1_LongPress_Handle(void)
{
  //��λwifi
  mcu_reset_wifi();
}
/*****************************************************************************
�������� : Key2_ShortPress_Handle
�������� : Key2�̰�������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key2_ShortPress_Handle(void)
{
  
}
/*****************************************************************************
�������� : Key2_LongPress_Handle
�������� : Key2����������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Key2_LongPress_Handle(void)
{
  volatile uint32_t t;
  
  wifi_test_mode = 0;
  LED_RGB_Control(0,0,0);
  
  //
  LED_RGB_Control(255,0,0);
  for(t = 0; t < 0x400000; t ++);
  //
  LED_RGB_Control(0,255,0);
  for(t = 0; t < 0x400000; t ++);
  //
  LED_RGB_Control(0,0,255);
  for(t = 0; t < 0x400000; t ++);
  //
  LED_RGB_Control(255,255,255);
  //
  wifi_test_mode = 1;
  mcu_start_wifitest();
  //
  for(t = 0; t < 0x400000; t ++);
  LED_RGB_Control(0,0,0);
}
/*****************************************************************************
�������� : KEY_Init
�������� : KEY��ʼ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(GPIO_KEY1_CLK | GPIO_KEY2_CLK, ENABLE);
  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
  GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
  GPIO_Init(GPIO_KEY2_PORT, &GPIO_InitStructure);
  //
  memset(Key_State,0,sizeof(Key_State));
  //
  Key_State[0].Long_Press_Handle = Key1_LongPress_Handle;
  Key_State[1].Long_Press_Handle = Key2_LongPress_Handle;
  //
  Key_State[0].Short_Press_Handle = Key1_ShortPress_Handle;
  Key_State[1].Short_Press_Handle = Key2_ShortPress_Handle;
}
/*****************************************************************************
�������� : Get_Key
�������� : ��ȡ����
������� : ��
���ز��� : ReadKey:����ֵ
ʹ��˵�� : ��
*****************************************************************************/
static uint8_t Get_Key(void) 
{
  uint8_t ReadKey = 0;
  
  if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT,GPIO_KEY1_PIN))
  {
    ReadKey |= PRESS_KEY1;
  }
  
  if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT,GPIO_KEY2_PIN))
  {
    ReadKey |= PRESS_KEY2;
  }
  
  return ReadKey;
}
/*****************************************************************************
�������� : Get_Key_Press_Time
�������� : ��ȡ��������ʱ��
������� : last_time:�ϴΰ���ʱ��
���ز��� : 2�ΰ���֮���ֵ
ʹ��˵�� : ��
*****************************************************************************/
static uint32_t Get_Key_Press_Time(uint32_t last_time)
{
  uint32_t time;
  
  time = Get_Count_Value();
  if(time >= last_time)
  {
    time -= last_time;
  }
  else
  {
    //Time2���
    time += ~last_time;
  } 

  return time;
}
/*****************************************************************************
�������� : Key_Scan
�������� : ɨ�谴��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Key_Scan(void)
{
  uint8_t i;
  uint32_t time;
  uint8_t key;
  
  key = Get_Key();
  for(i = 0; i < MAX_KEY; i ++)
  {
    switch(Key_State[i].Status)
    {
      case KEY_NO:
        //�а�������
        if((key >> i) & 0x01)
        {
          Key_State[i].Status = KEY_DOWN;
          Key_State[i].Press_Time = Get_Count_Value();
        }
        break;
        
      case KEY_DOWN:
        if(((key >> i) & 0x01) == 0)
        {
          Key_State[i].Status = KEY_UP;
        }
        break;
                
      case KEY_LONG:
        if(((key >> i) & 0x01) == 0)
        {
          Key_State[i].Press_Time = 0;
          Key_State[i].Status = KEY_NO;
        }
        break;  
    }

    if((Key_State[i].Status == KEY_DOWN) || (Key_State[i].Status == KEY_LONG))
    {
      time = Get_Key_Press_Time(Key_State[i].Press_Time);
      if(time >= TIME_PRESS_LONG)
      {
        //һֱ����
        Key_State[i].Press_Time = Get_Count_Value();
        Key_State[i].Status = KEY_LONG;
        if(Key_State[i].Long_Press_Handle)
        {
          Key_State[i].Long_Press_Handle();
        }
      }          
    }
    else if(Key_State[i].Status == KEY_UP)
    {
      //�ɿ�
     time = Get_Key_Press_Time(Key_State[i].Press_Time);
    
      Key_State[i].Press_Time = 0;
      Key_State[i].Status = KEY_NO;
      if((time >= TIME_PRESS_SHORT) && (time < TIME_PRESS_LONG))
      {
        //�̰�
        if(Key_State[i].Short_Press_Handle)
        {
          Key_State[i].Short_Press_Handle();
        }
      }
      else if(time >= TIME_PRESS_LONG)
      {
        //����
        if(Key_State[i].Long_Press_Handle)
        {
          Key_State[i].Long_Press_Handle();
        }
      }
    }
  }
}




