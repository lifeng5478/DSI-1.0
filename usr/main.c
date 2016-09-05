#include  <includes.h>
void  AppTaskStart   (void     *p_arg);
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR  err;


    BSP_IntDisAll();                                            /* Disable all interrupts.                              */
    
    CPU_Init();                                                 /* Initialize the uC/CPU Services   CPU��ʼ��                    */
    Mem_Init();                                                 /* Initialize Memory Management Module �ڴ�����ʼ��                 */
    Math_Init();                                                /* Initialize Mathematical Module     ����ģ�ͳ�ʼ��                  */
		BSP_Tick_Init(); 
    OSInit(&err);                                               /* Init uC/OS-III.                                      */

	/* Initialize BSP functions                             */   
    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,              /* Create the start task    ������ƿ�ָ��                        */
                 (CPU_CHAR     *)"App Task Start",              //��������
                 (OS_TASK_PTR   )AppTaskStart,                  //��������
                 (void         *)0u,														//���ݲ���	
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,				//�������ȼ�
                 (CPU_STK      *)&AppTaskStartStk[0u],					//�����ջָ��/ָ����ʼ���ڵ�0λ
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],   //�����ջ����
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,		//�����ջ�ܿռ�
                 (OS_MSG_QTY    )0u,								 						//������Ϣ����������ֻ��ʹ����Ϣ���в���Ч
                 (OS_TICK       )0u,                            //ʱ��Ƭ
                 (void         *)0u,														//������չ����ָ��
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),     //ѡ��/����������ж�ջ���|��ջȫ�����������ʼ��
                 (OS_ERR       *)&err);													//���󷵻�ֵ

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    (void)&err;

    return (0u);
}
