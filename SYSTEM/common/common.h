/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： common.h
* 文件标识：
* 内容摘要： common相关函数声明
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
#ifndef __COMMON_H
#define __COMMON_H
#include "stm32l1xx.h"
#include "delay.h"

/*********************************** 获取STM32 ID 地址 **************************************/
#define CHIPID_STM32L1		0x1FF80050   //L1 系列的CHIP ID  地址
#define CHIPID_STM32F1		0x1FFFF7E8   //F1 系列的CHIP ID  地址
/***********************************  STM32 GPIO位带操作   **************************************/
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum)   ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)  MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射  参考手册190页
#define GPIOA_ODR_Addr  (GPIOA_BASE+0x14)
#define GPIOB_ODR_Addr  (GPIOB_BASE+0x14)
#define GPIOC_ODR_Addr  (GPIOC_BASE+0x14)
#define GPIOD_ODR_Addr  (GPIOD_BASE+0x14)
#define GPIOE_ODR_Addr  (GPIOE_BASE+0x14)
#define GPIOF_ODR_Addr  (GPIOF_BASE+0x14)
#define GPIOG_ODR_Addr  (GPIOG_BASE+0x14)
 
#define GPIOA_IDR_Addr  (GPIOA_BASE+0x10)
#define GPIOB_IDR_Addr  (GPIOB_BASE+0x10)
#define GPIOC_IDR_Addr  (GPIOC_BASE+0x10)
#define GPIOD_IDR_Addr  (GPIOD_BASE+0x10)
#define GPIOE_IDR_Addr  (GPIOE_BASE+0x10)
#define GPIOF_IDR_Addr  (GPIOF_BASE+0x10)
#define GPIOG_IDR_Addr  (GPIOG_BASE+0x10)
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)        BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)         BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)        BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)         BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)        BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)         BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)        BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)         BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)        BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)         BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)        BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)         BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)        BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)         BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


void get_chip_id(void);

#endif   /* __COMMON_H */
























