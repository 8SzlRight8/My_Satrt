/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{
#if 1
	{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Beep_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(Beep_GPIO_Port, &GPIO_InitStruct);
	}
#else
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
	GPIOC->BSRR |= (1<<16<<1); //配置GPIOC Pin1为复位
//	GPIOC->BSRR |= (1<<1);   //配置GPIOC Pin1为置位
	}
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
