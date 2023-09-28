#include "exti.h"


u16 USART1_RX_STA=0;       //����״̬���
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.


static void NVCI_Config()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							// ������� 2
	
	// �ṹ��ʹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	// EXTI0--KEY0  NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = KEY0_EXTI_IRQ;					// �����ж�Դ EXTI4ͨ��  KEY0_EXTI_IRQ----EXTI0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		// ��ռ���ȼ�1  pree
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					// �����ȼ�1		sub
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							// ʹ��
	NVIC_Init(&NVIC_InitStructure);															// ��װ���
	// USART0 NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;						//	����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//	��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;						//	�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//	IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);															//	��װ���		
}


void EXTI_Key_Config(void)
{
	
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); //ѡ����Ϊ�ⲿ�ж���·  EXTI0 ������ӳ��
	NVCI_Config();		// NVCI����
	
	// EXTI�ṹ��
	EXTI_InitTypeDef EXTI_InitStructure;
	// ���� EXTI0
	GPIO_EXTILineConfig(KEY0_EXTI_PORTSOURCE, KEY0_EXTI_PINSOURCE); // EXTI0 ������ӳ��
	EXTI_InitStructure.EXTI_Line = KEY0_EXTI_LINE;									// KEY0 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;							// EXTI0 Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;					// �����½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;												// ʹ��
	EXTI_Init(&EXTI_InitStructure);																	// ��װ���
}	

void EXTI_USART1_Config(void)
{
	NVCI_Config();		// NVCI����
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);// �²⣺ �����ж� ��������ж�
}





void KEY0_IRQHandler(void)	// �ж�
{
	if (EXTI_GetITStatus(KEY0_EXTI_LINE) != RESET)			 //ȷ���Ƿ������ EXTI Line �ж�
	{
		if(IsKeyPressed(KEY0_PORT,KEY0_PIN))
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
			delay_ms(1000);
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY0_EXTI_LINE);
	}
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 r;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		if (USART_ReceiveData(USART1) == 1)
		{
			GPIO_WriteBit(LED0_PORT, LED0_PIN, !GPIO_ReadOutputDataBit(LED0_PORT, LED0_PIN));		// ȡ��
		}
	} 
} 	

 


