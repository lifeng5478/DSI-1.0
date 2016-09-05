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
    
    CPU_Init();                                                 /* Initialize the uC/CPU Services   CPU初始化                    */
    Mem_Init();                                                 /* Initialize Memory Management Module 内存管理初始化                 */
    Math_Init();                                                /* Initialize Mathematical Module     数字模型初始化                  */
		BSP_Tick_Init(); 
    OSInit(&err);                                               /* Init uC/OS-III.                                      */

	/* Initialize BSP functions                             */   
    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,              /* Create the start task    任务控制块指针                        */
                 (CPU_CHAR     *)"App Task Start",              //任务命名
                 (OS_TASK_PTR   )AppTaskStart,                  //任务函数名
                 (void         *)0u,														//传递参数	
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,				//任务优先级
                 (CPU_STK      *)&AppTaskStartStk[0u],					//任务堆栈指针/指针起始放在第0位
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],   //任务堆栈限制
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,		//任务堆栈总空间
                 (OS_MSG_QTY    )0u,								 						//任务消息队列容量，只有使能消息队列才有效
                 (OS_TICK       )0u,                            //时间片
                 (void         *)0u,														//任务扩展内容指针
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),     //选项/允许任务进行堆栈检测|堆栈全部进行清零初始化
                 (OS_ERR       *)&err);													//错误返回值

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    (void)&err;

    return (0u);
}
