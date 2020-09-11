/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： ledtask.c
* 文件标识：
* 内容摘要： ledtask相关函数定义
* 其它说明：
* 当前版本：
* 作    者： woody
* 完成日期： 2020.09.07
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
* 修改记录2：…
************************************************************************/
#include "ledtask.h"
#include "led.h"

static uint8_t runtimes=0;

TaskHandle_t Runing_State_Handler;     //任务句柄

/**************************************************************************
* 函数名称: Runing_State
* 功能描述: 系统正常运行指示灯任务 一秒亮一次
* 输入参数: pvParameters 是在创建该任务时传递的形参
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void  Runing_State(void *pvParameters)
{
    while(1) {
        Reversal_LED();
		DEBUG_LOG_PRF("Runing_State: %d",runtimes++);
		if(runtimes == 0XFF) 
			runtimes=0;
        vTaskDelay(100);   //延时1s
#if DEBUG_LOG_PRINTF  
		/* 检测任务堆栈使用大小的一种方式，通过设置FreeRTOS的宏INCLUDE_uxTaskGetStackHighWaterMark开启
		 * uxTaskGetStackHighWaterMark()主要用来查询指定任务的运行历史中， 其栈空间还差多少就要溢出。
		 * 这个值被称为栈空间的“高水线(High Water Mark)”。需要先设置大堆栈，然后合理化设置实际堆栈。*/
		DEBUG_LOG_PRF("Reference task stack size = %d", 
			((int )Runing_State_STK_SIZE-(int)uxTaskGetStackHighWaterMark(NULL))*2);
#endif
	}
}

/**************************************************************************
* 函数名称: LEDTaskSuspend
* 功能描述: 挂起运行指示灯任务
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void LEDTaskSuspend(void)
{
    LED_Control(0);		//挂起LED任务的时候需要设置一下LED灯的状态
    vTaskSuspend(Runing_State_Handler);  //挂起运行指示灯任务
}

/**************************************************************************
* 函数名称: LEDTaskResume
* 功能描述: 挂起运行指示灯任务
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void LEDTaskResume(void)
{
    LED_Control(0);		//恢复LED任务的时候需要设置一下LED灯的状态
    vTaskResume(Runing_State_Handler); //恢复运行指示灯任务
}

/**************************************************************************
* 函数名称: Creat_LED_Task
* 功能描述: 创建任务函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void Creat_LED_Task(void)
{
    //动态方式创建运行状态灯任务
    xTaskCreate((TaskFunction_t	)Runing_State,		      //任务函数
                (const char* 	)"Runing_State",	      //任务名称
                (uint16_t 		)Runing_State_STK_SIZE,	  //任务栈大小
                (void* 		  	)NULL,				      //传递给任务函数的参数
                (UBaseType_t 	)Runing_State_PRIO, 	  //任务优先级
                (TaskHandle_t*  )&Runing_State_Handler);  //任务句柄
}
















