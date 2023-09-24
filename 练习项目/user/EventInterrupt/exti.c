#include "exti.h"
#include "Button.h"
#include "LED.h"

void EXTI_Key_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	// ѡ����Ϊ�ⲿ�ж���·
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4); // EXTI0 ������ӳ��
	

	// EXTI0--KEY0  �ж�����

	//EXTI4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//EXTI4�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���		
	
	
	
	
	// ���� EXTI0
	// GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;									    // KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
}	
	





void EXTI4_IRQHandler(void)	// �ж�
{
	
	//GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��

	// �жϽ���ȥ
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
		
		//����жϱ�־λ
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}