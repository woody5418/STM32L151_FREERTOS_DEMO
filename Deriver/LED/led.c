/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： led.c
* 文件标识：
* 内容摘要： led相关函数定义
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
#include "led.h"


/**************************************************************************
* 函数名称: LED_Init
* 功能描述: LED I/O初始化函数
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void bsp_InitLED(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(LED_AHBPeriph_PORT, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;

    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

/**************************************************************************
* 函数名称: LED_Control
* 功能描述: 控制LED输出函数
* 输入参数: 1 / 0
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void LED_Control(uint8_t valed)
{
    if(valed == 1)	GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);  	//输出高
    if(valed == 0)	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);	//输出低
}

/**************************************************************************
* 函数名称: Reversal_LED
* 功能描述: GPIO翻转
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/
void Reversal_LED(void)
{
    LED_RED = !LED_RED;
}












