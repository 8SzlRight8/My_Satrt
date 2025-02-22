#include "stm32f4xx.h"
#include "./beep/bsp_beep.h"

void Delay(__IO u32 nCount); 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/*蜂鸣器端口初始化 */
	BEEP_GPIO_Config(); 

	/* 控制IO */
	while (1)
	{
		BEEP_TOGGLE;
		Delay(0xFFFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

