#ifndef __EXTI_H__
#define __EXTI_H__

#include "stm32f10x.h"

#include "Button.h"
#include "LED.h"

#include "SysTick.h"


// #ifdef __BUTTON_H__
// KEY0 �ж϶���
#define KEY0_EXTI_PORT 					KEY0_PORT
#define KEY0_EXTI_PIN 					KEY0_PIN
// ��buttonͷ�ļ�����---#define KEY0_EXTI_RCC 					(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO)	// ������Ӧ��GPIO AFIOʱ��
#define KEY0_EXTI_PORTSOURCE 		KEY0_PORTSOURCE		// ��button.h ����  �ж�Դ������ӳ����
#define KEY0_EXTI_PINSOURCE  		KEY0_PINSOURCE
#define KEY0_EXTI_LINE 					EXTI_Line4				// EXTIͨ��ѡ�� 0
#define KEY0_EXTI_IRQ 					EXTI4_IRQn				// �жϺ�  	NVIC��
#define KEY0_IRQHandler 				EXTI4_IRQHandler	// �жϺ�����
// #endif	/* __BUTTON_H__ */

static void  NVCI_Config();
void EXTI_Key_Config(void);

void KEY0_IRQHandler(void);						// KEY0 �жϺ���



#endif