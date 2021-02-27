#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   

////IO操作函数											   
#define	DHT11_DQ_OUT PAout(6) //数据端口
#define	DHT11_DQ_IN  PAin(6)  //数据端口

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    

void DHT11_IO_OUT(void);
void DHT11_IO_IN(void);

#endif















