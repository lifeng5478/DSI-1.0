/**
  ******************************************************************************
  * @file    bsp_touchpad.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ݰ���Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "bsp_touchpad.h"

#define TPAD_ARR_MAX_VAL 	0XFFFFFFFF	//��ʱ��������ֵ

volatile uint32_t tpad_default_val=0;//����û����ʱ��ʱ������ֵ

static void TPAD_Reset(void);
static uint16_t  TPAD_Get_Val(void);
static uint16_t  TPAD_Get_MaxVal(uint8_t n);
static void TIMx_CHx_Cap_Init(uint32_t arr,uint16_t psc); 


/********************************************************
*
* ��ʼ����������
* ��ÿ��ص�ʱ����������ȡֵ.
* ����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ��
*
*********************************************************/
uint8_t TPAD_Init(void)
{
	uint16_t buf[10];
	uint16_t temp;
	uint8_t j,i;
	TIMx_CHx_Cap_Init(TPAD_ARR_MAX_VAL,20-1);//20=180M/9M��180MΪϵͳʱ�ӣ�9MΪĿ��ʱ��
	for(i=0;i<10;i++)//������ȡ10��
	{				 
		buf[i]=TPAD_Get_Val();
	//	Delay_ms(10);	    
	}				    
	for(i=0;i<9;i++)//����
	{
		for(j=i+1;j<10;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	temp=0;
	for(i=2;i<8;i++)temp+=buf[i];//ȡ�м��8�����ݽ���ƽ��
	tpad_default_val=temp/6;
	//printf("tpad_default_val:%d\r\n",tpad_default_val);	
	if(tpad_default_val>TPAD_ARR_MAX_VAL/2)return 1;//��ʼ����������TPAD_ARR_MAX_VAL/2����ֵ,������!
	return 0;		     	    					   
}

/****************************************
*
* Ϊ���ݰ����ŵ�
* �����ʱ����־������
*
*****************************************/
static void TPAD_Reset(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	
 	GPIO_InitStructure.GPIO_Pin = TPAD_TIM_CH_PIN;				 //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���� 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
 	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
	
 	GPIO_ResetBits ( TPAD_TIM_CH_PORT, TPAD_TIM_CH_PIN );						 //PA.1���0,�ŵ�

	//Delay_ms(5);
	
	TIM_ClearITPendingBit(TPAD_TIMx, TPAD_TIM_IT_CCx|TIM_IT_Update); //����жϱ�־
	TIM_SetCounter(TPAD_TIMx,0);		//��0
	
	GPIO_InitStructure.GPIO_Pin = TPAD_TIM_CH_PIN; //PA1 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���� 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//���������� 
	GPIO_Init(TPAD_TIM_CH_PORT,&GPIO_InitStructure); //��ʼ��PA5 

}

/****************************************************
*
* �õ���ʱ������ֵ
* �����ʱ,��ֱ�ӷ��ض�ʱ���ļ���ֵ.
*
*****************************************************/
static uint16_t TPAD_Get_Val(void)
{				   
	TPAD_Reset();
	while(TIM_GetFlagStatus ( TPAD_TIMx, TPAD_TIM_IT_CCx ) == RESET)//�ȴ�����������
	{
		if(TIM_GetCounter(TPAD_TIMx)>TPAD_ARR_MAX_VAL-500)return TIM_GetCounter(TPAD_TIMx);//��ʱ��,ֱ�ӷ���CNT��ֵ
	};	
	return TPAD_TIM_GetCaptureX(TPAD_TIMx );	  
} 	 

/****************************************************
*
* ��ȡn��,ȡ���ֵ
* n��������ȡ�Ĵ���
* ����ֵ��n�ζ������������������ֵ
*
*****************************************************/
static uint16_t TPAD_Get_MaxVal(uint8_t n)
{
	uint16_t temp=0;
	uint16_t res=0;
	while(n--)
	{
		temp=TPAD_Get_Val();//�õ�һ��ֵ
		if(temp>res)res=temp;
	};
	return res;
}  

/*******************************************************************************
*
* ɨ�败������
* mode:0,��֧����������(����һ�α����ɿ����ܰ���һ��);1,֧����������(����һֱ����)
* ����ֵ:0,û�а���;1,�а���;			
*
*******************************************************************************/
#define TPAD_GATE_VAL 	100	//����������ֵ,Ҳ���Ǳ������tpad_default_val+TPAD_GATE_VAL,����Ϊ����Ч����.
uint8_t TPAD_Scan(uint8_t mode)
{
	static uint8_t keyen=0;	//0,���Կ�ʼ���;>0,�����ܿ�ʼ���	 
	uint8_t res=0;
	uint8_t sample=3;		//Ĭ�ϲ�������Ϊ3��	 
	uint16_t rval;
	if(mode)
	{
		sample=6;	//֧��������ʱ�����ò�������Ϊ6��
		keyen=0;	//֧������	  
	}
	rval=TPAD_Get_MaxVal(sample); 
	//printf("scan_rval=%d\n",rval);
	if(rval>(tpad_default_val+TPAD_GATE_VAL)&&rval<(10*tpad_default_val))//����tpad_default_val+TPAD_GATE_VAL,��С��10��tpad_default_val,����Ч
	{						
		if(keyen==0)res=1;	//keyen==0,��Ч 
		//printf("rval:%d\r\n",rval);		     	    					   
		keyen=3;				//����Ҫ�ٹ�3��֮����ܰ�����Ч   
	} 
	if(keyen)keyen--;		   							   		     	    					   
	return res;
}	 

/***********************************
*
* ��ʱ�����벶������
*
***********************************/
static void TIMx_CHx_Cap_Init(uint32_t arr,uint16_t psc)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(TPAD_TIM_CLK,ENABLE);  	  //TIM2ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(TPAD_TIM_GPIO_CLK, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(TPAD_TIM_CH_PORT,TPAD_TIM_SOURCE,TPAD_TIM_AF); //GPIOA1����λ��ʱ��5
	
	GPIO_InitStructure.GPIO_Pin = TPAD_TIM_CH_PIN;				 //PA1 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//���������� 
	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);	 //����Ϊ��������
	
	//��ʼ��TIM
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ   
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ�� 	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TPAD_TIMx, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	//��ʼ��ͨ��
	TIM_ICInitStructure.TIM_Channel = TPAD_TIM_Channel_X; //CC1S=01 	ѡ������� IC2ӳ�䵽TI5��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC2F=0000 ���������˲��� ���˲�
	TIM_ICInit(TPAD_TIMx, &TIM_ICInitStructure);//��ʼ��I5 IC2

	TIM_Cmd ( TPAD_TIMx, ENABLE ); 	//ʹ�ܶ�ʱ��5
		
}


/*********************************************END OF FILE**********************/
