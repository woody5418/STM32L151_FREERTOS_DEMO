/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： MainConfig.h
* 文件标识：
* 内容摘要： MainConfig相关函数声明
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
#ifndef __MAINCONFIG_H_
#define __MAINCONFIG_H_
#include "stm32l1xx.h"
/*****************************************
 * FREERTOS库头文件
 *****************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/*****************************************
 * String函数头文件
 *****************************************/
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"

/*****************************************
 * System 头文件
 *****************************************/
#include "common.h"
#include "delay.h"

/***********************************     版本设置    **************************************/
#define  STM32_VERSION "Nercita 2020/09/07 @ v1.0"

/***********************************    控制设备宏   **************************************/
#define DEBUG_LOG_PRINTF 1  //开启(1)/关闭(0) 串口log打印 
#if DEBUG_LOG_PRINTF
#define LOG_LEVEL		     LOG_LEVEL_VERBOSE
#else
#define LOG_LEVEL		     LOG_LEVEL_OFF
#endif
/*********************************** 开启 DEBUG 设置 **************************************/
#if (LOG_LEVEL	>= LOG_LEVEL_ERROR)
	#define	LOG_E(format,...)	\
			taskENTER_CRITICAL();printf("E:"format,##__VA_ARGS__);taskEXIT_CRITICAL();
#endif

#if (LOG_LEVEL	>= LOG_LEVEL_WARING)
	#define	LOG_W(format,...)	\
			taskENTER_CRITICAL();printf("W:"format,##__VA_ARGS__);taskEXIT_CRITICAL();
#endif

#if (LOG_LEVEL	>= LOG_LEVEL_INFO)
	#define	LOG_I(format,...)	\
			taskENTER_CRITICAL();printf("I:"format,##__VA_ARGS__);taskEXIT_CRITICAL();
#endif

#if (LOG_LEVEL	>= LOG_LEVEL_DEBUG)
	#define LOG_D(format, ...)   \
			taskENTER_CRITICAL();printf("DEBUG:(%s-%d)" format "\r\n", __func__, __LINE__, ##__VA_ARGS__);taskEXIT_CRITICAL(); 
#endif

#if LOG_LEVEL	>= LOG_LEVEL_VERBOSE
	#define	LOG_V(format,...)	\
			taskENTER_CRITICAL();printf("V:"format,##__VA_ARGS__);taskEXIT_CRITICAL();
#endif
/*********************************** 任务相关宏（优先级） **************************************/
//根据FreeRTOSConfig.h的宏configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 配置的值确定FreeRTOS能管理的最高优先级
//NVIC中断优先级的数值越小，优先级越高。 而 FreeRTOS 的任务优先级是，任务优先级数值越小，任务优先级越低。
//创建开始任务
#define START_TASK_PRIO		     1          //任务优先级
#define START_STK_SIZE 		     256        //任务堆栈大小
extern  TaskHandle_t StartTask_Handler;		//任务句柄


//创建任务1  运行状态指示灯任务
#define Runing_State_PRIO		 5            //任务优先级
#define Runing_State_STK_SIZE    128         //任务堆栈大小	
extern TaskHandle_t Runing_State_Handler;    //任务句柄

		
		
/*********************************** BSP层NVIC优先级 设置 **************************************/
//#define USART1_PRIO				14			//优先级

		
		
/***********************************   全局调用数组/变量  **************************************/
extern volatile uint8_t chipid[13];  //STM32L151 唯一ID 保存数组




#endif  /* __MAINCONFIG_H_ */



































