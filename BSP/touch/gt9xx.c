/**
  ******************************************************************************
  * @file    gt9xx.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   i2c��������������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
#include <stdio.h>
#include <string.h>
#include "bsp_i2c_touch.h"
#include "gt9xx.h"

uint8_t config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
                = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};


static int8_t GTP_I2C_Test(void);

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}


/**
  * @brief   ʹ��IIC�������ݴ���
  * @param
  *		@arg i2c_msg:���ݴ���ṹ��
  *		@arg num:���ݴ���ṹ��ĳ���
  * @retval  ������ɵĴ�����������������������0xff
  */
static int I2C_Transfer( struct i2c_msg *msgs,int num)
{
	int im = 0;
	int ret = 0;

	GTP_DEBUG_FUNC();

	for (im = 0; ret == 0 && im != num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//����flag�ж��Ƕ����ݻ���д����
		{
			ret = I2C_ReadBytes(msgs[im].addr, msgs[im].buf, msgs[im].len);		//IIC��ȡ����
		} else
		{
			ret = I2C_WriteBytes(msgs[im].addr,  msgs[im].buf, msgs[im].len);	//IICд������
		}
	}

	if(ret)
		return ret;

	return im;   													//������ɵĴ���ṹ����
}

/**
  * @brief   ��IIC�豸�ж�ȡ����
  * @param
  *		@arg client_addr:�豸��ַ
  *		@arg  buf[0~1]: ��ȡ���ݼĴ�������ʼ��ַ
  *		@arg buf[2~len-1]: �洢���������ݵĻ���buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count���Ĵ�����ַ����+��ȡ�������ֽ�����
  * @retval  i2c_msgs����ṹ��ĸ�����2Ϊ�ɹ�������Ϊʧ��
  */
static int32_t GTP_I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len)
{
    struct i2c_msg msgs[2];
    int32_t ret=-1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();
    /*һ�������ݵĹ��̿��Է�Ϊ�����������:
     * 1. IIC  д�� Ҫ��ȡ�ļĴ�����ַ
     * 2. IIC  ��ȡ  ����
     * */

    msgs[0].flags = !I2C_M_RD;					//д��
    msgs[0].addr  = client_addr;					//IIC�豸��ַ
    msgs[0].len   = GTP_ADDR_LENGTH;	//�Ĵ�����ַΪ2�ֽ�(��д�����ֽڵ�����)
    msgs[0].buf   = &buf[0];						//buf[0~1]�洢����Ҫ��ȡ�ļĴ�����ַ
    
    msgs[1].flags = I2C_M_RD;					//��ȡ
    msgs[1].addr  = client_addr;					//IIC���豸��ַ
    msgs[1].len   = len - GTP_ADDR_LENGTH;	//Ҫ��ȡ�����ݳ���
    msgs[1].buf   = &buf[GTP_ADDR_LENGTH];	//buf[GTP_ADDR_LENGTH]֮��Ļ������洢����������

    while(retries < 5)
    {
        ret = I2C_Transfer( msgs, 2);					//����IIC���ݴ�����̺�������2���������
        if(ret == 2)break;
        retries++;
    }
    if((retries >= 5))
    {
        GTP_ERROR("I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
    }
    return ret;
}



/**
  * @brief   ��IIC�豸д������
  * @param
  *		@arg client_addr:�豸��ַ
  *		@arg  buf[0~1]: Ҫд������ݼĴ�������ʼ��ַ
  *		@arg buf[2~len-1]: Ҫд�������
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count���Ĵ�����ַ����+д��������ֽ�����
  * @retval  i2c_msgs����ṹ��ĸ�����1Ϊ�ɹ�������Ϊʧ��
  */
static int32_t GTP_I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len)
{
    struct i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;

    GTP_DEBUG_FUNC();
    /*һ��д���ݵĹ���ֻ��Ҫһ���������:
     * 1. IIC���� д�� ���ݼĴ�����ַ������
     * */
    msg.flags = !I2C_M_RD;			//д��
    msg.addr  = client_addr;			//���豸��ַ
    msg.len   = len;							//����ֱ�ӵ���(�Ĵ�����ַ����+д��������ֽ���)
    msg.buf   = buf;						//ֱ������д�뻺�����е�����(�����˼Ĵ�����ַ)

    while(retries < 5)
    {
        ret = I2C_Transfer(&msg, 1);	//����IIC���ݴ�����̺�����1���������
        if (ret == 1)break;
        retries++;
    }
    if((retries >= 5))
    {

        GTP_ERROR("I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);

    }
    return ret;
}



/**
  * @brief   ʹ��IIC��ȡ�ٴ����ݣ������Ƿ�����
  * @param
  *		@arg client:�豸��ַ
  *		@arg  addr: �Ĵ�����ַ
  *		@arg rxbuf: �洢����������
  *		@arg len:    ��ȡ���ֽ���
  * @retval
  * 	@arg FAIL
  * 	@arg SUCCESS
  */
 int32_t GTP_I2C_Read_dbl_check(uint8_t client_addr, uint16_t addr, uint8_t *rxbuf, int len)
{
    uint8_t buf[16] = {0};
    uint8_t confirm_buf[16] = {0};
    uint8_t retry = 0;
    
    GTP_DEBUG_FUNC();

    while (retry++ < 3)
    {
        memset(buf, 0xAA, 16);
        buf[0] = (uint8_t)(addr >> 8);
        buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, buf, len + 2);
        
        memset(confirm_buf, 0xAB, 16);
        confirm_buf[0] = (uint8_t)(addr >> 8);
        confirm_buf[1] = (uint8_t)(addr & 0xFF);
        GTP_I2C_Read(client_addr, confirm_buf, len + 2);

      
        if (!memcmp(buf, confirm_buf, len+2))
        {
            memcpy(rxbuf, confirm_buf+2, len);
            return SUCCESS;
        }
    }    
    GTP_ERROR("I2C read 0x%04X, %d bytes, double check failed!", addr, len);
    return FAIL;
}


/*���ڼ�¼��������ʱ(����)����һ�δ���λ�ã�����ֵ��ʾ��һ���޴�������*/
static int16_t pre_x=-1;
static int16_t pre_y=-1;
/**
  * @brief   ���ڴ���򱨸津����⵽����
  * @param
  *    @arg     id: ����˳��trackID
  *    @arg     x:  ������ x ����
  *    @arg     y:  ������ y ����
  *    @arg     w:  ������ ��С
  * @retval ��
  */
static void GTP_Touch_Down(int32_t x,int32_t y,int32_t w)
{

	GTP_DEBUG_FUNC();

	/*ȡx��y��ʼֵ������Ļ����ֵ*/
  GTP_DEBUG("X:%d, Y:%d, W:%d",  x, y, w);
  pre_x = x; pre_y=y;
}


/**
  * @brief   ���ڴ���򱨸津���ͷ�
  * @param �ͷŵ��id��
  * @retval ��
  */
static void GTP_Touch_Up(void)
{
  /*�����ͷţ���pre xy ����Ϊ��*/
	pre_x = -1;
	pre_y = -1;  
  GTP_DEBUG("Touch release!");
}


/**
  * @brief   ��������������ѯ�����ڴ����жϵ���
  * @param ��
  * @retval ��
  */
static void Goodix_TS_Work_Func(void)
{
	static uint8_t IsTouch=0;
	uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
	uint8_t  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1]={GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
	uint8_t  touch_num = 0;
	uint8_t  finger = 0;

	uint8_t client_addr=GTP_ADDRESS;
	int32_t input_x = 0;
	int32_t input_y = 0;
	int32_t input_w = 0;
	int32_t ret = -1;
	
	GTP_DEBUG_FUNC();
	
	ret = GTP_I2C_Read(client_addr, point_data, 12);//10�ֽڼĴ�����2�ֽڵ�ַ
	if (ret < 0)
	{
			GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
			return;
	}
	
	finger = point_data[GTP_ADDR_LENGTH];//״̬�Ĵ�������

	GTP_DEBUG("I2C finger:%X",finger);

	if(finger == 0x00)		//û�����ݣ��˳�
	{
		if(IsTouch)
		{
			GTP_Touch_Up();
			IsTouch=0;
		}
		return;
	}

	if((finger & 0x80) == 0)//�ж�buffer statusλ
	{
			goto exit_work_func;//����δ������������Ч
	}

	touch_num = finger & 0x0f;//�������

	if (touch_num > GTP_MAX_TOUCH)
	{
			goto exit_work_func;//�������֧�ֵ����������˳�
	}
	IsTouch=1;
	input_x  = point_data[4] | (point_data[5] << 8);	//x����
	input_y  = point_data[6] | (point_data[7] << 8);	//y����
	input_w  = point_data[8] | (point_data[9] << 8);	//size

	GTP_Touch_Down(input_x, input_y, input_w);//���ݴ���

exit_work_func:
	{
			ret = GTP_I2C_Write(client_addr, end_cmd, 3);
			if (ret < 0)
			{
					GTP_INFO("I2C write end_cmd error!");
			}
	}
}


/**
  * @brief   ������оƬ���¸�λ
  * @param ��
  * @retval ��
  */
 int8_t GTP_Reset_Guitar(void)
{
    GTP_DEBUG_FUNC();
#if 1
    I2C_ResetChip();
    return 0;
#else 		//�����λ
    int8_t ret = -1;
    int8_t retry = 0;
    uint8_t reset_command[3]={(uint8_t)GTP_REG_COMMAND>>8,(uint8_t)GTP_REG_COMMAND&0xFF,2};

    //д�븴λ����
    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, reset_command, 3);
        if (ret > 0)
        {
            GTP_INFO("GTP enter sleep!");

            return ret;
        }

    }
    GTP_ERROR("GTP send sleep cmd failed.");
    return ret;
#endif

}



 /**
   * @brief   ����˯��ģʽ
   * @param ��
   * @retval 1Ϊ�ɹ�������Ϊʧ��
   */
//int8_t GTP_Enter_Sleep(void)
//{
//    int8_t ret = -1;
//    int8_t retry = 0;
//    uint8_t reset_comment[3] = {(uint8_t)(GTP_REG_COMMENT >> 8), (uint8_t)GTP_REG_COMMENT&0xFF, 5};//5
//
//    GTP_DEBUG_FUNC();
//
//    while(retry++ < 5)
//    {
//        ret = GTP_I2C_Write(GTP_ADDRESS, reset_comment, 3);
//        if (ret > 0)
//        {
//            GTP_INFO("GTP enter sleep!");
//
//            return ret;
//        }
//
//    }
//    GTP_ERROR("GTP send sleep cmd failed.");
//    return ret;
//}


int8_t GTP_Send_Command(uint8_t command)
{
    int8_t ret = -1;
    int8_t retry = 0;
    uint8_t command_buf[3] = {(uint8_t)(GTP_REG_COMMAND >> 8), (uint8_t)GTP_REG_COMMAND&0xFF, GTP_COMMAND_READSTATUS};

    GTP_DEBUG_FUNC();

    while(retry++ < 5)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, command_buf, 3);
        if (ret > 0)
        {
            GTP_INFO("send command success!");

            return ret;
        }

    }
    GTP_ERROR("send command fail!");
    return ret;
}

/**
  * @brief   ���Ѵ�����
  * @param ��
  * @retval 0Ϊ�ɹ�������Ϊʧ��
  */
int8_t GTP_WakeUp_Sleep(void)
{
    uint8_t retry = 0;
    int8_t ret = -1;

    GTP_DEBUG_FUNC();

    while(retry++ < 10)
    {
        ret = GTP_I2C_Test();
        if (ret > 0)
        {
            GTP_INFO("GTP wakeup sleep.");
            return ret;
        }
        GTP_Reset_Guitar();
    }

    GTP_ERROR("GTP wakeup sleep failed.");
    return ret;
}

static int32_t GTP_Get_Info(void)
{
    uint8_t opr_buf[6] = {0};
    int32_t ret = 0;

    uint16_t abs_x_max = GTP_MAX_WIDTH;
    uint16_t abs_y_max = GTP_MAX_HEIGHT;
    uint8_t int_trigger_type = GTP_INT_TRIGGER;
        
    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+1) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+1) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 6);
    if (ret < 0)
    {
        return FAIL;
    }
    
    abs_x_max = (opr_buf[3] << 8) + opr_buf[2];
    abs_y_max = (opr_buf[5] << 8) + opr_buf[4];
    
    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+6) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+6) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 3);
    if (ret < 0)
    {
        return FAIL;
    }
    int_trigger_type = opr_buf[2] & 0x03;
    
    GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
            abs_x_max,abs_y_max,int_trigger_type);
    
    return SUCCESS;    
}

/*******************************************************
Function:
    Initialize gtp.
Input:
    ts: goodix private data
Output:
    Executive outcomes.
        0: succeed, otherwise: failed
*******************************************************/
 int32_t GTP_Init_Panel(void)
{
    int32_t ret = -1;

    int32_t i = 0;
    uint8_t check_sum = 0;
    int32_t retry = 0;

    uint8_t cfg_info[] = CTP_CFG_GROUP1;
    uint8_t cfg_info_len =CFG_GROUP_LEN(cfg_info) ;

    uint8_t cfg_num =0x80FE-0x8047+1 ;		//��Ҫ���õļĴ�������

    GTP_DEBUG_FUNC();


    I2C_Touch_Init();

    ret = GTP_I2C_Test();
    if (ret < 0)
    {
        GTP_ERROR("I2C communication ERROR!");
    }

    GTP_Read_Version(); 


    memset(&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    memcpy(&config[GTP_ADDR_LENGTH], cfg_info, cfg_info_len);

    //����Ҫд��checksum�Ĵ�����ֵ
    check_sum = 0;
    for (i = GTP_ADDR_LENGTH; i < cfg_num+GTP_ADDR_LENGTH; i++)
    {
        check_sum += config[i];
    }
    config[ cfg_num+GTP_ADDR_LENGTH] = (~check_sum) + 1; 	//checksum
    config[ cfg_num+GTP_ADDR_LENGTH+1] =  1; 						//refresh ���ø��±�־

    //д��������Ϣ
    for (retry = 0; retry < 5; retry++)
    {
        ret = GTP_I2C_Write(GTP_ADDRESS, config , cfg_num + GTP_ADDR_LENGTH+2);
        if (ret > 0)
        {
            break;
        }
    }
    Delay(0xfffff);				//�ӳٵȴ�оƬ����

#if 0	//����д������ݣ�����Ƿ�����д��
    //���������������д����Ƿ���ͬ
	{
    	    uint16_t i;
    	    uint8_t buf[200];
    	     buf[0] = config[0];
    	     buf[1] =config[1];    //�Ĵ�����ַ

    	    GTP_DEBUG_FUNC();

    	    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));

    	    //�汾��д��0x00�󣬻���и�λ����λΪ0x41
    	     config[GTP_ADDR_LENGTH] = 0x41;

    	    for(i=0;i<cfg_num+GTP_ADDR_LENGTH;i++)
    	    {

    	    	if(config[i] != buf[i])
    	    	{
    	    		GTP_DEBUG("Config fail ! i = %d ",i);
    	    		break;
    	    	}
    	    }
    	    if(i==cfg_num+GTP_ADDR_LENGTH)
	    		GTP_DEBUG("Config success ! i = %d ",i);
	}
#endif
    GTP_Get_Info();

//    GT91xx_Config_Read_Proc();
//    GTP_Send_Command(GTP_COMMAND_UPDATE);
//    Delay(0xfffff);				//�ӳٵȴ�оƬ����
//
//    GTP_Send_Command(GTP_COMMAND_CALCULATE);
//    Delay(0xfffff);				//�ӳٵȴ�оƬ����
//    GTP_Send_Command(GTP_COMMAND_UPDATE);
//    Delay(0xfffff);				//�ӳٵȴ�оƬ����
//
//    GTP_Send_Command(GTP_COMMAND_DIFFERENCE);
//    Delay(0xfffff);				//�ӳٵȴ�оƬ����

    return 0;
}


/*******************************************************
Function:
    Read chip version.
Input:
    client:  i2c device
    version: buffer to keep ic firmware version
Output:
    read operation return.
        2: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Read_Version(void)
{
    int32_t ret = -1;
    uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //�Ĵ�����ַ

    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
    if (ret < 0)
    {
        GTP_ERROR("GTP read version failed");
        return ret;
    }

    if (buf[5] == 0x00)
    {
        GTP_INFO("IC Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);
    }
    else
    {
        GTP_INFO("IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    }
    return ret;
}

/*******************************************************
Function:
    I2c test Function.
Input:
    client:i2c client.
Output:
    Executive outcomes.
        2: succeed, otherwise failed.
*******************************************************/
static int8_t GTP_I2C_Test( void)
{
    uint8_t test[3] = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
    uint8_t retry = 0;
    int8_t ret = -1;

    GTP_DEBUG_FUNC();
  
    while(retry++ < 5)
    {
        ret = GTP_I2C_Read(GTP_ADDRESS, test, 3);
        if (ret > 0)
        {
            return ret;
        }
        GTP_ERROR("GTP i2c test failed time %d.",retry);
    }
    return ret;
}


#include "GUI.h"

void GT9xx_GetOnePiont(void)
{
	GUI_PID_STATE State;
	GTP_DEBUG_FUNC();
	
	__disable_irq();
	
	Goodix_TS_Work_Func();
	
	__enable_irq();
	
	if((pre_x==-1) || (pre_y==-1))
	{
		State.x = -1;
		State.y = -1;
		State.Pressed = 0;
		State.Layer = 0;
		GUI_PID_StoreState(&State);
		return;
	}
	State.Pressed = 1;
	State.x = pre_x;
	State.y =pre_y;
	State.Layer = 0;
	GUI_PID_StoreState(&State);
}
//MODULE_DESCRIPTION("GTP Series Driver");
//MODULE_LICENSE("GPL");
