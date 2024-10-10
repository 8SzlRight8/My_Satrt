#include "stm32f4xx.h"
#include "./beep/bsp_beep.h"

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/*�������˿ڳ�ʼ�� */
	BEEP_GPIO_Config(); 

	/* ����IO */
	while (1)
	{
		BEEP_TOGGLE;
		Delay(0xFFFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

