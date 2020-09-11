# 版本更新，修改，移植说明文档


#### 说明: 
	1.遵循markdown书写语法，详细的可以参考菜鸟教程学习：https://www.runoob.com/markdown/md-tutorial.html
	2.cJason选择使用Keil内置的Jansson，具体的可以参考API文档：http://jansson.readthedocs.io/en/latest/apiref.html
	3.FreeRTOSv10.3.1版本选择最新的版本：https://www.freertos.org/a00104.html
	4.修改此工程需要添加日期、功能删减、修改人员、联系方式等说明

参考资料：下载地址：https://www.st.com/zh/microcontrollers-microprocessors/stm32l151re.html#
	STM32Lxx参考手册.pdf
	数据手册_L151.pdf
	
	
## 版本号 V1.0


	作    者 ：woody
	联系方式 ：QQ 2490006131
	修改时间 ：2020/09/07
	最新样例 ：https://github.com/woody5418/STM32L151_FREERTOS_DEMO
	功能说明 ：STM32L151大容量支持
			   FreeRTOSv10.3.1 最新版本支持
			   cJson支持（keil自带的jansson）
			   添加Cortex-M3 特有的位绑定操作GPIO存放在common.h
			   添加串口1的DEBUG模式，在MainConfig.h选择是否启用，默认串口波特率115200
			   所有Application层任务创建的优先级、堆栈大小、句柄，以及BSP层的NVIC设置抢占优先级要求都存放在MainConfig.h
			   驱动、任务、主函数封层编写，不允许合成一个.c文件，各层之间使用接口函数，添加完整接口说明
			   延时函数选择使用滴答时钟（未经严格测试）
			   低功耗模式选择低功耗睡眠模式，详情可以参考手册113页，理论上频率越低，功耗越低
			   
			   
			   

