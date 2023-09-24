#include "exti.h"

static void NVIC_Configuration(void)
 {
	// �ṹ��ʹ��
	NVIC_InitTypeDef NVIC_InitStructure;

	// EXTI0--KEY0  �ж�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// ������� 2
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					// �����ж�Դ EXTI0ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ��� 
 }
 
 
void EXTI_Key_Config(void)
{
	RCC_APB2PeriphClockCmd(KEY0_EXTI_RCC,ENABLE);
	
	// ѡ����Ϊ�ⲿ�ж���·
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	
	NVIC_Configuration();
	
	// EXTI�ṹ��
	EXTI_InitTypeDef EXTI_InitStructure;
	
	
	// ���� EXTI0
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = KEY0_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;					// �����½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
}	
	


void KEY0_IRQHandler(void)	// �ж�
{
	// �жϽ���ȥ
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET) //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
		
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}