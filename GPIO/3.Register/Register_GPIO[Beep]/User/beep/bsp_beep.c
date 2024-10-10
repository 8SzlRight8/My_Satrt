/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   蜂鸣器函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./beep/bsp_beep.h"   

 /**
  * @brief  初始化控制蜂鸣器的IO
  * @param  无
  * @retval 无
  */
void BEEP_GPIO_Config(void)
{		
	/*开启 GPIOC 时钟，使用外设时都要先开启它的时钟*/
	RCC->AHB1ENR |= (1<<2);  //使能GPIOC的时钟
	
	/* LED 端口初始化 */
	//设置端口模式
	GPIOC->MODER  &= ~( 0x03<< (2*1));	 //清空设置
	GPIOC->MODER |= (1<<2*1);   //设置GPIOC Pin1为输出模式
	
	//设置端口输出类型
	GPIOC->OTYPER &= ~(1<<1*1); //清空设置
	GPIOC->OTYPER |= (0<<1*1);  //设置GPIOC Pin1为推挽模式
	
	//设置端口输出速度
	GPIOC->OSPEEDR &= ~(0x03<<2*1); //清空速度配置
	GPIOC->OSPEEDR |= (0<<2*1);  //设置GPIOC Pin1端口输出速度为2MHz
	
	//设置端口上拉/下拉
	GPIOC->PUPDR &= ~(0x03<<2*1);  //清掉之前配置
	GPIOC->PUPDR |= (1<<2*1);   //配置GPIOC Pin1成上拉模式
	
	//设置端口置位/复位
	GPIOC->BSRRH |= (1<<16<<1); //配置GPIOC Pin1为复位0
//	GPIOC->BSRRL |= (1<<1);   //配置GPIOC Pin1为置位1

}
/*********************************************END OF FILE**********************/
