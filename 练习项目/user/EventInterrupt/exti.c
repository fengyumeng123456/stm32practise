#include "exti.h"

extern float  ADC_ConvertedValue; // from ADC
extern int KEY0DelayTime;
extern int KEY0PressNumber;

static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							

	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI4--KEY0 
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);														
	// EXTI3--KEY1
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQ;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI2--KEY2
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);															
	// EXTI0--WKUP
	NVIC_InitStructure.NVIC_IRQChannel = WKUP_EXTI_IRQ;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
	NVIC_Init(&NVIC_InitStructure);		
	// USART
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	// TIM6
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;						//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;				//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	// ADC PA1
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;							//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
}



void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);										
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); 
	NVCI_Config();																
}	

void EXTI_USART1_Config(u32 b)
{
	USART1_Init(b);
	NVCI_Config();		// NVCI
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}


// 中断函数定义

void USART1_IRQHandler(void)                
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		// 接收中断
	{
		
		buffer[writeIndex++] = USART_ReceiveData(USART1);		// 将数据存储到缓冲区
		
		
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位
		if(writeIndex >=128) writeIndex = 0;
	}
} 	



void KEY0_IRQHandler(void)	
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)		
	{
		if(KEY0DelayTime == 0)
		{
			TIM_Cmd(BASIC_TIM6, ENABLE);
		}
		else if(KEY0DelayTime <= 500)
		{
			// 双击
			ToggleLED(0);
			ToggleLED(1);
			
			TIM_Cmd(BASIC_TIM6, DISABLE);
			KEY0DelayTime = 0;
		}
		
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}

void KEY1_IRQHandler(void)
{
		if (EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY1_PORT,KEY1_PIN))
		{
			
		}
		
			EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}

void KEY2_IRQHandler(void)
{
	if (EXTI_GetITStatus(KEY2_EXTI_LINE) != RESET)			
	{
		if(IsKeyPressed(KEY2_PORT,KEY2_PIN))
		{
			Beep_Music();
		}
	EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
	}
}

void WKUP_IRQHandler(void)
{

	if (EXTI_GetITStatus(WKUP_EXTI_LINE) != RESET)		
	{
		
	}
	EXTI_ClearITPendingBit(WKUP_EXTI_LINE);
}

void TIM6_IRQHandler(void)
{
	KEY0DelayTime++;
	if(KEY0DelayTime>600)
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			// 长按
			ToggleLED(1);
			
			TIM_Cmd(BASIC_TIM6, DISABLE);
			KEY0DelayTime = 0;
		}
		else
		{
			// 短按
			ToggleLED(0);
			
			TIM_Cmd(BASIC_TIM6, DISABLE);
			KEY0DelayTime = 0;
		}
	}
}

void ADC_IRQHandler(void)
{
	if (ADC_GetITStatus(ADCx,ADC_IT_EOC)==SET)
	{
		u16 temp;
		// 读取 ADC 的转换值
		temp = ADC_GetConversionValue(ADCx);
		ADC_ConvertedValue = (float)temp / 4096 * 3.3;  // 2^12  3.3参考电压
	}
	ADC_ClearITPendingBit(ADCx,ADC_IT_EOC);
}

