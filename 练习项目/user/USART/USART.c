#include "USART.h"

void USART1_Init(u32 bound)
{
	RCC_APB2PeriphClockCmd(USART_TX_CLK,ENABLE);
	
	// GPIO�ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	// �������
	GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    			// �����������
	GPIO_Init(USART_TX_Port,&GPIO_InitStructure);  			
	// ��������
	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  // ģ������
	GPIO_Init(USART_RX_Port,&GPIO_InitStructure); 
	
	
	// USART�ṹ��
	USART_InitTypeDef USART_InitStructure;
	// ����1
	USART_InitStructure.USART_BaudRate = bound;								 	//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure);		// ��װ���
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	USART_ClearFlag(USART1, USART_FLAG_TC);				// ��� USARTx �Ĵ������־λ
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);// �²⣺��������ж�
	
	
	
}