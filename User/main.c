#include "stm32f10x.h"
#include <stdio.h>
#include "Led.h"
#include "Delay.h"
#include "ty_uart.h"
#include "oled.h"
#include "dht11.h"
#include "hal_key.h"
#include "hal_rgb.h"
#include "user_timer.h"
#include "wifi.h"
//#include "system.h"
//#include "sht3x.h"
//#include "typedefs.h"

TYPE_BUFFER_S FlashBuffer;

void wifi_work_state_led(void)
{
    uint8_t wifi_state = mcu_get_wifi_work_state();
    static uint8_t count = 0;

    switch(wifi_state)
    {
    case SMART_CONFIG_STATE:
      if(Get_Time3_Value() % 2 == 0)
      {
        LED_Control(LED1,1);
      }
      else
      {
        LED_Control(LED1,0);
      }
      break;
      
    case AP_STATE:
      if(Get_Time3_Value() == 0)
      {
        LED_Control(LED1,1);
      }
      else if(Get_Time3_Value() == 6)
      {
        LED_Control(LED1,0);
      }
      break;
      
    case WIFI_NOT_CONNECTED:
        LED_Control(LED1,0);
      break;
      
    case WIFI_CONNECTED:
      LED_Control(LED1,1);
      break;
      
    default:
      LED_Control(LED1,0);
      break;
    }
}

uint8_t temperature = 0u;  	    //温度
uint8_t humidity = 0u;          //湿度
	
int main (void){
	char str1[10]="";
	char str2[10]="";

	//LED_Init();
	// OLED 初始化
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Refresh();
	OLED_Clear();
	// OLED 显示欢迎
	OLED_ShowString(0,20,"Welcome!",24);
	OLED_Refresh();
	delay_ms(500);
	while(DHT11_Init());
	USART1_Init(9600);
  USART3_Init(9600);
  TIM2_Count_Init();
  TIM3_Count_Init(99,719);//1ms
  KEY_Init();
  RGB_LED_Init();
	wifi_protocol_init();
	RGB_Power_Control();
	OLED_Clear();
	
	OLED_ShowString(60,0,"C",24);
	OLED_ShowString(60,30,"%",24);
	
	while(1){
		wifi_uart_service();
    
    Key_Scan();
    
    wifi_work_state_led();
		
		DHT11_Read_Data(&temperature,&humidity);
		sprintf(str1,"%4d",temperature);
		sprintf(str2,"%4d",humidity);
		OLED_ShowString(0,0,(unsigned char*)str1,24);
		OLED_ShowString(0,30,(unsigned char*)str2,24);
		OLED_Refresh();
		delay_ms(50);
	}
}
