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
#ifndef __LEDTASK_H
#define __LEDTASK_H
#include "stm32l1xx.h"
#include "MainConfig.h" 




void Creat_LED_Task(void);
void LEDTaskSuspend(void);
void LEDTaskResume(void);
void LEDTaskResume(void);

#endif  /* __LEDTASK_H */


































