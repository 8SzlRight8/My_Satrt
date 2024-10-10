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
	/*���� GPIOC ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ��*/
	RCC->AHB1ENR |= (1<<2);  //ʹ��GPIOC��ʱ��
	
	/* LED �˿ڳ�ʼ�� */
	//���ö˿�ģʽ
	GPIOC->MODER  &= ~( 0x03<< (2*1));	 //�������
	GPIOC->MODER |= (1<<2*1);   //����GPIOC Pin1Ϊ���ģʽ
	
	//���ö˿��������
	GPIOC->OTYPER &= ~(1<<1*1); //�������
	GPIOC->OTYPER |= (0<<1*1);  //����GPIOC Pin1Ϊ����ģʽ
	
	//���ö˿�����ٶ�
	GPIOC->OSPEEDR &= ~(0x03<<2*1); //����ٶ�����
	GPIOC->OSPEEDR |= (0<<2*1);  //����GPIOC Pin1�˿�����ٶ�Ϊ2MHz
	
	//���ö˿�����/����
	GPIOC->PUPDR &= ~(0x03<<2*1);  //���֮ǰ����
	GPIOC->PUPDR |= (1<<2*1);   //����GPIOC Pin1������ģʽ
	
	//���ö˿���λ/��λ
	GPIOC->BSRR |= (1<<16<<1); //����GPIOC Pin1Ϊ��λ
//	GPIOC->BSRR |= (1<<1);   //����GPIOC Pin1Ϊ��λ
	}
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
