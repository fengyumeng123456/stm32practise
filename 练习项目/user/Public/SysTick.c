#include "SysTick.h"


void delay_init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
}

void delay_us(u32 nus)
{     
    u32 temp;   
    SysTick->LOAD = nus * 9; // 72MHz / 8 = 9MHz
    SysTick->VAL=0x00; // ��ռ�����
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; // ��ʼ����
    do
    {
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&!(temp&(1<<16))); // �ȴ�ʱ�䵽��   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // �رռ�����
    SysTick->VAL =0X00; // ��ռ�����
}

void delay_ms(u16 nms)
{     
    u32 temp;   
    SysTick->LOAD = nms * 9000; // 72MHz / 8 = 9MHz
    SysTick->VAL=0x00; // ��ռ�����
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; // ��ʼ����
    do
    {
        temp=SysTick->CTRL;
    }
    while((temp&0x01)&&!(temp&(1<<16))); // �ȴ�ʱ�䵽��   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; // �رռ�����
    SysTick->VAL =0X00; // ��ռ�����
}
