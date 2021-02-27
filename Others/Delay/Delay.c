/*
	这是一个利用滴答定时器的延时程序
*/
// 引入 Delay.h 头文件
#include "Delay.h"

// 这个变量记录的是还需要进行的中断次数（一次中断为1微秒）
u32 ticking;

/*
	函数名：ticking_decrement
	函数功能：每次进入 SysTick 中断都将 ticking 减一。（将这个函数写入 SysTick 的中断处理函数中）
*/
void ticking_decrement(void){
	if(ticking != 0){
		ticking--;
	}
}

/*
	函数名：delay_us
	函数功能：微秒级延时函数
*/
void delay_us(u32 time_us){
	// 记录下需要计数的微秒数，也就是需中断次数
	ticking = time_us;
	// 开始计数
	SysTick_Config(72);
	// 只要没有进行完需要的中断
	while(ticking != 0);
	// 关闭滴答计时
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/*
	函数名：delay_ms
	函数功能：毫秒级延时函数
*/
void delay_ms(u16 time_ms){
	// 每延时1ms就将毫秒数减一
	while(time_ms-- != 0){
		// 延时1000us，即延时1ms
		delay_us(1000);
	}
}

/*
	函数名：delay_s
	函数功能：秒级延时函数
*/
void delay_s(u16 time_s){
	// 每延时1ms就将秒数减一
	while(time_s-- != 0){
		// 延时1000ms，即延时1s
		delay_ms(1000);
	}
}
