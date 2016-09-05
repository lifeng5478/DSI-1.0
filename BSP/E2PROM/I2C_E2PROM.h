#ifndef __I2C_EE_H
#define	__I2C_EE_H

#include "stm32f4xx.h"



/* AT24C01/02ÿҳ��8���ֽ� */
#define I2C_PageSize           8

/* AT24C04/08A/16Aÿҳ��16���ֽ� */
//#define I2C_PageSize           16			

/* STM32 I2C ����ģʽ */
#define I2C_Speed              400000

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
#define I2C_OWN_ADDRESS7      0X0B   

/*I2C�ӿ�*/

/*�ȴ���ʱʱ��*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/*��Ϣ���*/
#define EEPROM_DEBUG_ON         0



/* 
 * AT24C02 2kb = 2048bit = 2048/8 B = 256 B
 * 32 pages of 8 bytes each
 *
 * Device Address
 * 1 0 1 0 A2 A1 A0 R/W
 * 1 0 1 0 0  0  0  0 = 0XA0
 * 1 0 1 0 0  0  0  1 = 0XA1 
 */

/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */



void I2C_EE_Init(void);
void I2C_EE_BufferWrite(char* pBuffer, char WriteAddr, u16 NumByteToWrite);
uint32_t I2C_EE_ByteWrite(char* pBuffer, char WriteAddr);
uint32_t I2C_EE_PageWrite(char* pBuffer, char WriteAddr, u8 NumByteToWrite);
uint32_t I2C_EE_BufferRead(char* pBuffer, char ReadAddr, u16 NumByteToRead);
void I2C_EE_WaitEepromStandbyState(void);


#endif

