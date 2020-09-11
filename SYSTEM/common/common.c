/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： common.c
* 文件标识：
* 内容摘要： common相关函数定义
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
#include "common.h"
#include "MainConfig.h"


//STM32L151 唯一ID 保存数组 最后一Byte要满足字符串以0X00结尾，作为debug打印使用
volatile uint8_t chipid[13];

/**************************************************************************
* 函数名称: GET_STM32_ID
* 功能描述: 获取96位ID
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
static void GET_STM32_ID(uint8_t *idnum)
{
    for(uint8_t i = 0; i < 12; i++)  idnum[i] = *(uint8_t *)(CHIPID_STM32L1 + i);
}
/**************************************************************************
* 函数名称: get_chip_id
* 功能描述: 获取CHIP ID保存到全局数组
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void get_chip_id(void)
{
    GET_STM32_ID((uint8_t *)chipid);					//获取唯一ID
#if DEBUG_LOG_PRINTF
    DEBUG_LOG_PRF("CHIPID:");  							//串口打印CHIPID
    for(uint8_t i = 0; i < 12; i++) printf("%02x", chipid[i]);
    printf("\r\n");
#endif
}

/**************************************************************************
* 函数名称: PreSleepProcessing
* 功能描述: 进入低功耗模式前需要处理的事情,详见Document说明
* 输入参数: ulExpectedIdleTime：低功耗模式运行时间
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void vPreSleepProcessing(uint32_t ulExpectedIdleTime)
{
#if DEBUG_LOG_PRINTF
	//DEBUG_LOG_PRF("pre:%d",ulExpectedIdleTime);
#endif
    // 可以考虑在此处加入关闭外设时钟来进一步降低功耗 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,DISABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,DISABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,DISABLE);	
	
	PWR_EnterSleepMode( PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI ); //低功耗睡眠模式
}

/**************************************************************************
* 函数名称: PostSleepProcessing
* 功能描述: 退出低功耗模式以后需要处理的事情
* 输入参数: ulExpectedIdleTime：低功耗模式运行时间
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void vPostSleepProcessing(uint32_t ulExpectedIdleTime)
{
#if DEBUG_LOG_PRINTF
	//DEBUG_LOG_PRF("post:%d",ulExpectedIdleTime);
#endif
	//退出低功耗模式以后打开那些被关闭的外设时钟，此处只是演示性代码
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
}







