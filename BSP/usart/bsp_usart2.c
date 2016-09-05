/**
  ******************************************************************************
  * @file    bsp_usart_gsm.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */   
#include "bsp_usart2.h"
#include <stdarg.h>

 /**
  * @brief  GSM_USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void GSM_USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHB1PeriphClockCmd( GSM_USART_RX_GPIO_CLK|GSM_USART_TX_GPIO_CLK, ENABLE);

  /* Enable UART clock */
  GSM_USART_CLKCMD(GSM_USART_CLK, ENABLE);
  
  /* Connect PXx to USARTx_Tx*/
  GPIO_PinAFConfig(GSM_USART_RX_GPIO_PORT,GSM_USART_RX_SOURCE, GSM_USART_RX_AF);

  /* Connect PXx to USARTx_Rx*/
  GPIO_PinAFConfig(GSM_USART_TX_GPIO_PORT,GSM_USART_TX_SOURCE,GSM_USART_TX_AF);

  /* Configure USART Tx as alternate function  */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  GPIO_InitStructure.GPIO_Pin = GSM_USART_TX_PIN  ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GSM_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as alternate function  */
  GPIO_InitStructure.GPIO_Pin = GSM_USART_RX_PIN;
  GPIO_Init(GSM_USART_RX_GPIO_PORT, &GPIO_InitStructure);
			
  /* USART1 mode config */
  USART_InitStructure.USART_BaudRate = GSM_USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(GSM_USART, &USART_InitStructure); 
  
  USART_Cmd(GSM_USART, ENABLE);	
	USART_ClearFlag(GSM_USART, USART_FLAG_TC);  
  
  /* Configure the NVIC Preemption Priority Bits */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = GSM_USART_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
  /* ʹ�ܴ���2�����ж� */
	USART_ITConfig(GSM_USART, USART_IT_RXNE, ENABLE);
}


/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART2_printf()����
 */
static char *gsm_itoa(int value, char *string, int radix)
{
  int i, d;
  int flag = 0;
  char *ptr = string;
  /* This implementation only works for decimal numbers. */
  if (radix != 10)
  {
    *ptr = 0;
    return string;
  }
  if (!value)
  {
    *ptr++ = 0x30;
    *ptr = 0;
    return string;
  }
  /* if this is a negative value insert the minus sign. */
  if (value < 0)
  {
    *ptr++ = '-';
    /* Make the value positive. */
    value *= -1;
  }
  for (i = 10000; i > 0; i /= 10)
  {
    d = value / i;
    if (d || flag)
    {
      *ptr++ = (char)(d + 0x30);
      value -= (d * i);
      flag = 1;
    }
  }
  /* Null terminate the string. */
  *ptr = 0;
  return string;
} /* NCL_Itoa */


//�жϻ��洮������
#define UART_BUFF_SIZE      383
volatile    uint16_t gsm_pBuffer = 0;
uint8_t     gsm_usart_buf[UART_BUFF_SIZE];
void GSM_USART_IRQHandler(void)
{
  if(gsm_pBuffer<UART_BUFF_SIZE)
  {
    if(USART_GetITStatus(GSM_USART, USART_IT_RXNE) != RESET)
    {
        gsm_usart_buf[gsm_pBuffer] = USART_ReceiveData(GSM_USART);
        gsm_pBuffer++;
    }
  }
}

//��ȡ���յ������ݺͳ���
char *gsm_get_rebuff(uint16_t *len)
{
    *len = gsm_pBuffer;
    return (char *)&gsm_usart_buf;
}
//�������
void gsm_clean_rebuff(void)
{
	uint16_t i=UART_BUFF_SIZE+1;
  gsm_pBuffer = 0;
	while(i) 
  {
    gsm_usart_buf[--i]=0;
  }
}

/*
 * ��������GSM_USART_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ���������õ���GSM_USART
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��GSM_USART_printf( GSM_USART, "\r\n this is a demo \r\n" );
 *            		 GSM_USART_printf( GSM_USART, "\r\n %d \r\n", i );
 *            		 GSM_USART_printf( GSM_USART, "\r\n %s \r\n", j );
 */
void GSM_USART_printf(USART_TypeDef* USARTx, char *Data,...)
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;
				case 'n':							          //���з�
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;

        case 'd':										//ʮ����
          d = va_arg(ap, int);
          gsm_itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}

/*********************************************END OF FILE**********************/
