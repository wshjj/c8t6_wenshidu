#ifndef  __PWM_H
#define  __PWM_H
#include "sys.h"

extern float instance;

void TIM3_Init(u16 arr,u16 psc);
void TIM3_NVIC_Init (void);


#endif
