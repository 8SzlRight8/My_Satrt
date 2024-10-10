# My_Start

2024.10.09

----



## 简明

==>> 用来记录学习STM32的驱动部分，从寄存器、标准库、hal库 三个部分进行学习记录。主要是对如下外设进行学习：

​	1）GPIO

​	2）USART （以及其对应协议）

​	3）TIMER

​	4）ADC/DAC

​	....

以及协议等 SPI 、IIC 、 、、、等常见协议进行学习

==>> 希望在三个月以内将最必要的学完，多看招聘看需求  



## 一、GPIO【GPIOC_1】


### 1、标准库（寄存器）

~~~c
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启控制蜂鸣器的GPIO的端口时钟*/
    RCC_AHB1PeriphClockCmd( BEEP_GPIO_CLK, ENABLE);   

    /*选择要控制蜂鸣器的GPIO*/															   
    GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;	

    /*设置GPIO模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    /*设置GPIO速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

    /*调用库函数，初始化控制蜂鸣器的GPIO*/
    GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);			 

    /* 关闭蜂鸣器*/
    GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);	 

//------------------------------------------------------------------
/***** 在标准库中使用寄存器进行控制 ****/
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
	GPIOC->BSRRH |= (1<<16<<1); //配置GPIOC Pin1为复位
//	GPIOC->BSRRL |= (1<<1);   //配置GPIOC Pin1为置位
~~~



### 2、Hal库（寄存器）

~~~c
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

//-------------------------------------------------------------------------
/***** 在HAL库中使用寄存器进行控制 ****/
【注意】：HAL库中只有GPIOC->BSRR，没有 GPIOC->BSRRH 和 GPIOC->BSRRL 。
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
~~~





### 3、纯寄存器+看数据手册

~~~c




~~~



### 4、配置步骤疑惑记录

#### 1、标准库

~~~c
1）使能时钟
    RCC_AHB1PeriphClockCmd( BEEP_GPIO_CLK, ENABLE);

2）写入参数寄存器，没有外部中断标志（标准库中有没有外部中断配置）
    2.1 标准库函数 GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) 解析
/**********************************************************************/
    
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* Check the parameters */ //检测，需要定义宏定义为1才行
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /* ------------------------- Configure the port pins ---------------- */
  /*-- GPIO Mode Configuration --*/
  //直接写GPIO寄存器，没有关EXIT，所以需要专门的EXIT函数
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}
~~~



#### 2、Hal库

Disable：禁用外部时钟
BYPASS Clock Resource：外部有源晶振（旁路时钟源）
Crystal/Ceramic Resonator:外部无源晶振（陶瓷晶振）

![image-20241010103832935](C:\Users\20477\AppData\Roaming\Typora\typora-user-images\image-20241010103832935.png)

~~~c
// 0x01U ：加U了就是无符号；加l就是long
    
//先开启时钟
__HAL_RCC_GPIOC_CLK_ENABLE();   //配置 RCC->AHB1ENR 寄存器

void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t temp = 0x00U;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));

  /* Configure the port pins */
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = 0x01U << position;  //对应的IO每循环一次都有一个位置
    /* Get the current IO position */
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition; //要么是pin，要么是0

    if(iocurrent == ioposition) //如果此次的IO口为需要设置的IO Pin口，则执行下面配置
    {
      /*--------------------- GPIO Mode Configuration ------------------------*/
      // 1）GPIO Register
      /* In case of Output or Alternate function mode selection */
      if(((GPIO_Init->Mode & GPIO_MODE) == MODE_OUTPUT) || \
          (GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
      {
        /* Check the Speed parameter */
        assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
        /* Configure the IO Speed */
        temp = GPIOx->OSPEEDR; 
        temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U)); //清空临时temp中的所有OSPEEDER的数据
        temp |= (GPIO_Init->Speed << (position * 2U));   //修改temp中的速度配置
        GPIOx->OSPEEDR = temp;   //设置速度进寄存器

        /* Configure the IO Output Type */
        temp = GPIOx->OTYPER; 
        temp &= ~(GPIO_OTYPER_OT_0 << position) ;
        temp |= (((GPIO_Init->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << position);
        GPIOx->OTYPER = temp;
       }

      if((GPIO_Init->Mode & GPIO_MODE) != MODE_ANALOG)
      {
        /* Check the parameters */
        assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
        
        /* Activate the Pull-up or Pull down resistor for the current IO */
        temp = GPIOx->PUPDR;
        temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
        temp |= ((GPIO_Init->Pull) << (position * 2U));
        GPIOx->PUPDR = temp;
      }

      /* In case of Alternate function mode selection */
      if((GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
      {
        /* Check the Alternate function parameter */
        assert_param(IS_GPIO_AF(GPIO_Init->Alternate));
        /* Configure Alternate function mapped with the current IO */
        temp = GPIOx->AFR[position >> 3U];
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
        temp |= ((uint32_t)(GPIO_Init->Alternate) << (((uint32_t)position & 0x07U) * 4U));
        GPIOx->AFR[position >> 3U] = temp;
      }

      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
      temp = GPIOx->MODER;
      temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
      temp |= ((GPIO_Init->Mode & GPIO_MODE) << (position * 2U));
      GPIOx->MODER = temp;

      /*--------------------- EXTI Mode Configuration ------------------------*/
      // 1）先配置 SYSCFG Register
      // 2）在配置 EXTI Register
      /* Configure the External Interrupt or event for the current IO */
      if((GPIO_Init->Mode & EXTI_MODE) != 0x00U)
      {
        /* Enable SYSCFG Clock */
        __HAL_RCC_SYSCFG_CLK_ENABLE();

        temp = SYSCFG->EXTICR[position >> 2U];
        temp &= ~(0x0FU << (4U * (position & 0x03U)));
        temp |= ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4U * (position & 0x03U)));
        SYSCFG->EXTICR[position >> 2U] = temp;

        /* Clear Rising Falling edge configuration */
        temp = EXTI->RTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & TRIGGER_RISING) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->RTSR = temp;

        temp = EXTI->FTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & TRIGGER_FALLING) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->FTSR = temp;

        temp = EXTI->EMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & EXTI_EVT) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->EMR = temp;

        /* Clear EXTI line configuration */
        temp = EXTI->IMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & EXTI_IT) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->IMR = temp;
      }
    }
  }
}
~~~





#### 3、寄存器

~~~c

~~~





