#include "stm32f4xx.h"
#include "encoder.h"
#include "BSP.H"

unsigned int tmp;
unsigned char Aold,Bold;
unsigned char st;
unsigned char  I2c_Buf_Read[256];
void encoder_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int encodingWitchPolling(void)
{
		if(A_ON&&B_ON)
				st=1;
		
		if(st)
		{
			if(A_OFF&&B_OFF)
			{
				if(Bold)
				{
					st=0;
					if(tmp==100)
						tmp=100;
					else
						tmp++;
				}
				if(Aold)
				{
					st=0;
				if(tmp==0)
					tmp=0;
				else
					tmp--;
				}
			}
		}
		Aold=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10);
		Bold=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11);

		return tmp;
}
