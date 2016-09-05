#include "LED.H"
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_Instructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Instructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Instructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOH, &GPIO_Instructure);
	LED1_ON;
	LED2_ON;
	LED3_ON;
}
