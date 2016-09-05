#ifndef _encoder_H
#define _encoder_H

#define A_ON   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 1
#define A_OFF  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == 0
#define B_ON   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 1
#define B_OFF  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == 0

extern unsigned int tmp;
void encoder_GPIO_Init(void);
int encodingWitchPolling(void);

#endif
