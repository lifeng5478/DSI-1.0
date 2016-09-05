/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <includes.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES  
*********************************************************************************************************
*/

                                                                /* ----------------- APPLICATION GLOBALS -------------- */
                                                                /* ------------ FLOATING POINT TEST TASK -------------- */
static  OS_TCB       App_TaskEq0FpTCB;
static  CPU_STK      App_TaskEq0FpStk[APP_CFG_TASK_EQ_STK_SIZE];
static  OS_TCB       LED_Task_TCB;
static  CPU_STK      LED_Task_Stk[LED_TASK_STK_SIZE];
static  OS_TCB       ENCODER_Task_TCB;
static  CPU_STK      ENCODER_Task_STK[ENCODER_TASK_STK_SIZE];

OS_TMR      MyTmr;
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern void SpeedTest(void);
extern void MainTask(void);
//static void KeyFresh(OS_TMR *p_tmr, void *p_arg);
static  void  AppTaskCreate         (void);
//static  void  AppObjCreate          (void);

static  void  App_TaskEq0Fp         (void  *p_arg);             /* Floating Point Equation 0 task.   */
static void LED_Task  (void  *p_arg);
static void ENCODER_Task  (void  *p_arg);

/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

 void  AppTaskStart (void *p_arg)
{

    OS_ERR  err;


   (void)p_arg;
                                        /* Initialize Tick Services.                            */
//		App_OS_SetAllHooks();
	 
    BSP_Init();   
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running  无任务运行时计算CPU占用          */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
                                            /* Create Applicaiton kernel objects                    */
    AppTaskCreate();                                            /* Create Application tasks      进入任务创建函数                       */
//		OSTmrCreate((OS_TMR              *)&MyTmr,
//               (CPU_CHAR            *)"MyTimer",          
//               (OS_TICK              )0,                
//               (OS_TICK              )1,                
//               (OS_OPT               )OS_OPT_TMR_PERIODIC,
//               (OS_TMR_CALLBACK_PTR  )KeyFresh,          
//               (void                *)0,
//               (OS_ERR              *)err);
//  OSTmrStart((OS_TMR *)&MyTmr,(OS_ERR *)err);
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */

//        LED1_ON;
//        OSTimeDlyHMSM(0u, 0u, 0u, 200u,
//                      OS_OPT_TIME_HMSM_STRICT,
//                      &err);
//				LED1_OFF;
			GT9xx_GetOnePiont();
        OSTimeDlyHMSM(0u, 0u, 0u,20u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}

//static void KeyFresh(OS_TMR *p_tmr, void *p_arg)
//{
//	(void) p_arg;
//	GT9xx_GetOnePiont();
//}
/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    OS_ERR  os_err;
    
                                                                /* ------------- CREATE FLOATING POINT TASK ----------- */
    OSTaskCreate((OS_TCB      *)&App_TaskEq0FpTCB,
                 (CPU_CHAR    *)"FP  Equation 1",
                 (OS_TASK_PTR  ) App_TaskEq0Fp, 
                 (void        *) 0,
                 (OS_PRIO      ) APP_CFG_TASK_EQ_PRIO,
                 (CPU_STK     *)&App_TaskEq0FpStk[0],
                 (CPU_STK_SIZE ) App_TaskEq0FpStk[APP_CFG_TASK_EQ_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) APP_CFG_TASK_EQ_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&os_err);
								 
								 
    OSTaskCreate((OS_TCB      *)&LED_Task_TCB,
                 (CPU_CHAR    *)"LED_SysTemCheck",
                 (OS_TASK_PTR  ) LED_Task, 
                 (void        *) 0,
                 (OS_PRIO      ) LED_TASK_PRIO,
                 (CPU_STK     *)&LED_Task_Stk[0],
                 (CPU_STK_SIZE ) LED_Task_Stk[LED_TASK_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) LED_TASK_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&os_err);								 
								 
								// static  OS_TCB       ENCODER_Task_TCB;
//static  CPU_STK      ENCODER_Task_STK[ENCODER_TASK_STK_SIZE];
		 OSTaskCreate((OS_TCB      *)&ENCODER_Task_TCB,
                 (CPU_CHAR    *)"ENCODER_Task",
                 (OS_TASK_PTR  ) ENCODER_Task, 
                 (void        *) 0,
                 (OS_PRIO      ) ENCODER_TASK_PRIO,
                 (CPU_STK     *)&ENCODER_Task_STK[0],
                 (CPU_STK_SIZE ) ENCODER_Task_STK[ENCODER_TASK_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) ENCODER_TASK_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&os_err);		
}



/*
*********************************************************************************************************
*                                             App_TaskEq0Fp()
*
* Description : This task finds the root of the following equation.
*               f(x) =  e^-x(3.2 sin(x) - 0.5 cos(x)) using the bisection mehtod
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskEq0Fp' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  App_TaskEq0Fp (void  *p_arg)
{          
	  OS_ERR  err;

//  SpeedTest();
  MainTask();
    while (DEF_TRUE) {    
			/* Task body, always written as an infinite loop.       */

        OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}


static void LED_Task  (void  *p_arg)
{
	OS_ERR  err;
	    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
	      LED1_ON;
        OSTimeDlyHMSM(0u, 0u, 0u, 200u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
				LED1_OFF;
			  OSTimeDlyHMSM(0u, 0u, 0u, 200u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}

//const char  *temp0;
	int temp0;
extern int slider0;
extern int Text1;
unsigned char *temp1;
static void ENCODER_Task  (void  *p_arg)
{
	OS_ERR  err;
	    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		temp0=	encodingWitchPolling();
		SLIDER_SetValue(slider0,temp0);
        OSTimeDlyHMSM(0u, 0u, 0u, 2u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);

    }
}
