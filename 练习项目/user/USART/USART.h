#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"

#define USART1_REC_LEN		200  	//�����������ֽ��� 200

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���


// �������
#define USART_TX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_TX_Port  					GPIOA
#define USART_TX_PIN 						GPIO_Pin_2
// ��������
#define USART_RX_CLK  					( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 )
#define USART_RX_Port  					GPIOA
#define USART_RX_PIN 						GPIO_Pin_3


void USART1_Init(u32 bound);




#endif