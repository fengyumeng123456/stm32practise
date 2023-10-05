#include "RTC.h"

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

void RTC_Init()
{
	printf("RTC_Init=%d\r\n",1);
	// ע�� RTCʹ�õ�RTCCLKʱ��Դ��APBʹ�õ���PCLK1ʱ��Դ�����߲�һ��һ����
	// ʹ��PWR����ʱ��  BKP�󱸼Ĵ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) == 0x0825)	// �ѳ�ʼ��
	{
		printf("Rif=%d\r\n",1);
		RTC_WaitForSynchro();			 				// �ȴ����һ�ζ� RTC �Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE); // ʹ�� RTC ���ж�
		RTC_WaitForLastTask();				 		// �ȴ����һ�ζ� RTC �Ĵ�����д�������
	}
	else 	// û��ʼ���������书�ܽ��г�ʼ��
	{
		printf("Rif=%d\r\n",0);
		BKP_DeInit();
		
		// ���ú궨���Ժ����ʱ��Դ
		RCC_LSICmd(ENABLE);				// �ڲ�����ʱ�� ����  40khz
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);   // ����RTCʱ��ԴΪLSI
		RCC_RTCCLKCmd(ENABLE);		// RTCʱ��ʹ��
		RTC_WaitForLastTask(); 
		RTC_WaitForSynchro(); 						// �ȴ� RTC �Ĵ���ͬ��
		RTC_WaitForLastTask();						// �ȴ����һ�ζ� RTC �Ĵ�����д�������
		
		
		RTC_EnterConfigMode();						// ��������
		RTC_SetPrescaler(9999); 						// ���� RTC Ԥ��Ƶ��ֵ  40k/40k = 1

		//RTC_WaitForLastTask(); 						// ----��ѭ��    �ȴ����һ�ζ� RTC �Ĵ�����д�������

		RTC_SetCounter(1696478761); // ����һ��ʱ�� unixʱ��� 2023-10-05 12:06:01
		RTC_ExitConfigMode(); 						// �˳�����ģʽ
		

		BKP_WriteBackupRegister(BKP_DR1, 0x0825); //��ָ���ĺ󱸼Ĵ�����д���û���������
		RTC_ITConfig(RTC_IT_SEC, ENABLE); // ʹ�� RTC ���ж�
	}
	
}




// ����Ƿ�Ϊ����
int isLeapYear(int year)
{
    if (year % 4 != 0) {
        return 0;
    } else if (year % 100 != 0) {
        return 1;
    } else if (year % 400 != 0) {
        return 0;
    } else {
        return 1;
    }
}

// ��ȡÿ���µ�����
int getDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year) && month == 2) {
        return 29;
    }
    return daysInMonth[month - 1];
}

void UnixtimeToTime(u32 timestamp, int* year, int* month, int* day, int* hour, int* minute, int* second)
{
    *second = timestamp % SECONDS_PER_MINUTE;
    timestamp /= SECONDS_PER_MINUTE;
    *minute = timestamp % SECONDS_PER_MINUTE;
    timestamp /= SECONDS_PER_MINUTE;
    *hour = timestamp % SECONDS_PER_HOUR;
    timestamp /= SECONDS_PER_HOUR;

    unsigned int years = timestamp / (SECONDS_PER_DAY * (isLeapYear(*year) ? 366 : 365));
    timestamp -= years * (SECONDS_PER_DAY * (isLeapYear(*year) ? 366 : 365));
    
    *year = years + 1970;

    *month = 1;
    while (timestamp >= getDaysInMonth(*month, *year) * SECONDS_PER_DAY) {
        timestamp -= getDaysInMonth(*month, *year) * SECONDS_PER_DAY;
        (*month)++;
    }

    *day = timestamp / SECONDS_PER_DAY + 1; // +1 because day of the month starts from 1
}

void showTimeToScreen()
{
	#include "animations.h"
	int year;int month; int day; int hour; int minute;int second;
	u8 showRTCString[7];
	UnixtimeToTime(RTC_GetCounter(),&year,&month,&day,&hour,&minute,&second);
	sprintf(showRTCString, "%d��%d��%d��", year, month,day);
	LCD_ShowString(30,300,100,16,16,showRTCString);
	
}