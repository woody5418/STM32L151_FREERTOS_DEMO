/************************************************************************
* Copyright (C) Copyright 2014-2015,Nercita,Beijing,China
*
* 文件名称： main.c
* 文件标识：
* 内容摘要： main相关函数定义
* 其它说明： https://github.com/woody5418/STM32L151_FREERTOS_DEMO
* 当前版本： V1.0
* 作    者： woody   QQ：2490006131
* 完成日期： 2020.09.07
*	< STM32L151ZET6 >
			FLASH SIZE	:512Kbytes
			RAM SIZE	:80Kbytes
			EEPROM  	:16K
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
* 修改记录2：…
************************************************************************/
#include "MainConfig.h"
#include "usart.h"
#include "app.h"


TaskHandle_t StartTask_Handler;  //任务句柄 创建启动任务

/**************************************************************************
* 函数名称: start_task
* 功能描述: 启动任务，也就是最高优先级任务，这里用来创建其他任务
* 输入参数: pvParameters 是在创建该任务时传递的形参
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();      					//进入临界区
    app_Init();									//任务创建函数
    vTaskDelete(StartTask_Handler);             //删除开始任务
    taskEXIT_CRITICAL();       					//退出临界区
}


/**************************************************************************
* 函数名称: main
* 功能描述: 主函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
int main(void)
{
	/* 在启动调度前，为了防止初始化 STM32 外设时有中断服务程序执行，这里禁止全局中断 除了 NMI 和 HardFault) 。
	这样做的好处是：
	1. 防止执行的中断服务程序中有 FreeRTOS 的 API 函数。
	2. 保证系统正常启动，不 受别的中断影响。
	3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
	在移植文件 port.c 中的函数 prvStartFirstTask 中会重新开启全局中断。通过指令 cpsie i 开启， ，__set_PRIMASK(
	和 cpsie i 是等效的。*/
	__set_PRIMASK(1);

    /* 保证睡眠模式下调试器继续可以连接使用 */
    DBGMCU_Config(DBGMCU_SLEEP, ENABLE);

    /*	由于 ST 固件库的启动文件已经执行了 CPU 系统时钟的初始化，所以不必再次重复配置系统时钟。
    	启动文件配置了 CPU 主时钟频率、内部 Flash 访问速度和可选的外部 SRAM FSMC 初始化。
    	系统时钟缺省配置为 32MHz ，如果需要更改，可以修改 system_stm32l1xx.c 文件*/
    /* 优先级分组设置为 4 ，可配置 0~15 级抢占式优先级， 0 级子优先级，即不存在子优先级。*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
    delay_init();			//延时初始化代码
#if DEBUG_LOG_PRINTF
    USART1_Init(115200);
#endif
    bsp_Init();				//所有硬件固件初始化
#if DEBUG_LOG_PRINTF
    DEBUG_LOG_PRF(STM32_VERSION);
#endif	
	
    /* 创建任务 */
    xTaskCreate((TaskFunction_t	)start_task,		  	//任务函数
                (const char* 	)"start_task",		  	//任务名称
                (uint16_t 		)START_STK_SIZE,	  	//任务堆栈大小
                (void* 		  	)NULL,				  	//传递给任务函数的参数
                (UBaseType_t 	)START_TASK_PRIO, 	  	//任务优先级
                (TaskHandle_t*  )&StartTask_Handler); 	//任务句柄

    vTaskStartScheduler();    							//开启任务调度
    /*
     如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
     heap 空间不足造成创建失败，此要加大 FreeRTOSConfig.h 文件中定义的 heap 大小：
     #define configTOTAL_HEAP_SIZE ( ( size_t ) ( 8 * 1024 ) )
    */
    while(1);
}


/***************************************************************************************************/

void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()).  */

}

void vApplicationIdleHook(void)
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}

void vApplicationMallocFailedHook(void)
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    for(;;);
}
























