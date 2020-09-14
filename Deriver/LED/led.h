/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： led.h
* 文件标识：
* 内容摘要： led相关函数声明
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
#ifndef __LED_H
#define __LED_H
#include "MainConfig.h" 

#define  LED_AHBPeriph_PORT		RCC_AHBPeriph_GPIOA
#define  LED_GPIO_PORT			GPIOA
#define  LED_GPIO_PIN			GPIO_Pin_0

#define LED_RED PAout(0)// PA0	

void bsp_InitLED(void);//初始化
void LED_Control(uint8_t valed);
void Reversal_LED(void);

#endif  /* _LED_H */

























