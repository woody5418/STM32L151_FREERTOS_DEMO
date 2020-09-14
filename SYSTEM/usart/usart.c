/************************************************************************
* Copyright (C) 2020 Nercita
*
* 文件名称： usart.c
* 文件标识：
* 内容摘要： usart相关函数定义
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
#include "usart.h"
#include "MainConfig.h"


#if DEBUG_LOG_PRINTF
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE {
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0); //循环发送,直到发送完毕
    USART1->DR = (uint8_t) ch;
    return ch;
}
#endif

/**************************************************************************
* 函数名称: USART1_Init
* 功能描述: USART1_Init 初始化函数，(串口1功能与USB功能冲突)
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
* -----------------------------------------------
* 2020/09/07       V1.0      woody         创建
**************************************************************************/

void USART1_Init(uint32_t BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);			//使能USART1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);				//使能GPIOA时钟

    /* Connect PA9 to USART1_Tx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); 		//PA.9 复用
    /* Connect PA10 to USART1_Rx */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 		//PA10 复用

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate; //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	  //收发模式

    USART_Init(USART1, &USART_InitStructure);//初始化串口1
    USART_Cmd(USART1, ENABLE);//使能串口1
}
#endif



















