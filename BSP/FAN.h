#ifndef _FAN_H
#define _FAN_H

#include "stm32f4xx.h"
void Tim3_init(void);
void PWM1_GPIO_init(void);
void PWM1_NVIC(void);
void TIM3_IRQHandler(void);
void Tim3_OC_init(void);
#endif
