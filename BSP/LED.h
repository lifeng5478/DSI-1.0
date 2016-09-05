#include "stm32f4xx.h"
#define LED1_ON  GPIO_SetBits(GPIOH,GPIO_Pin_10);
#define LED2_ON  GPIO_SetBits(GPIOH,GPIO_Pin_11);
#define LED3_ON  GPIO_SetBits(GPIOH,GPIO_Pin_12);

#define LED1_OFF  GPIO_ResetBits(GPIOH,GPIO_Pin_10);
#define LED2_OFF  GPIO_ResetBits(GPIOH,GPIO_Pin_11);
#define LED3_OFF  GPIO_ResetBits(GPIOH,GPIO_Pin_12);

void LED_Configuration(void);
