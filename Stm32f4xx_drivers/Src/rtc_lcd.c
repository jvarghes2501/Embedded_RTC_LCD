/*
 * rtc_lcd.c
 *
 *  Created on: Jun 3, 2025
 *      Author: jesti
 */


#include<stdio.h>
#include "ds1307.h"
# define SYSTICK_TIM_CLK  16000000UL

static char * get_day_of_week (uint8_t i);
void number_to_string(uint8_t num, char *buf);
char* time_to_string(RTC_time_t *rtc_time);
char * date_to_string (RTC_date_t * rtc_date);

char * get_day_of_week (uint8_t i)
{
	char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	return days[i-1];
}

void number_to_string(uint8_t num, char *buf)
{
	if(num<10)
	{
		buf[0] = '0';
		buf[1] = num+48;
	}else if (num>=10 && num < 99)
	{
		buf[0] = (num/10) + 48;
		buf[1] = (num%10) + 48; //add 48 to convert to ASCII equivalent
	}
}
char* time_to_string(RTC_time_t *rtc_time)
{
	//format: hh:mm:ss
	static char buf[9];
	buf[2] = ':';
	buf[5] = ':';
	number_to_string(rtc_time->hours, buf);
	number_to_string(rtc_time->minutes, &buf[3]);
	number_to_string(rtc_time->seconds, &buf[6]);

	buf[8] = '\0';
	return buf;


}
char * date_to_string (RTC_date_t * rtc_date)
{
	//format: dd/mm/yy
	static char buf[9];
	buf[2] = '/';
	buf[5] = '/';
	number_to_string(rtc_date->date, buf);
	number_to_string(rtc_date->month, &buf[3]);
	number_to_string(rtc_date->year, &buf[6]);

	buf[8]='\0';
	return buf;

}
void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}
int main (void)
{
	RTC_time_t current_time;
	RTC_date_t current_date;

	if(ds1307_init()){
		printf("RTC initialization failed\n");
		while(1);
	}
	init_systick_timer(1);
	current_date.date = 3;
	current_date.day = TUESDAY;
	current_date.month = 1;
	current_date.year = 25;

	current_time.hours = 10;
	current_time.minutes = 25;
	current_time.seconds = 41;
	current_time.time_format = TIME_FORMAT_12HRS_PM;

	ds1307_set_current_date(&current_date);
	ds1307_set_current_time(&current_time);

	ds1307_get_current_date(&current_date);
	ds1307_get_current_time(&current_time);
	char *am_pm;
	if(current_time.time_format != TIME_FORMAT_24HRS){
		am_pm = (current_time.time_format) ? "PM":"AM";
		printf("Current time = %s %s\n", time_to_string (&current_time), am_pm);
	}else{
		printf("Current time = %s\n", time_to_string(&current_time));
	}

	printf("Current date = %s <%s>\n", date_to_string(&current_date), get_day_of_week(current_date.day));

	while(1);
	return 0 ;

}

void SysTick_Handler(void)
{
	RTC_time_t current_time;
	RTC_date_t current_date;

	ds1307_get_current_date(&current_date);
	ds1307_get_current_time(&current_time);
	char *am_pm;
	if(current_time.time_format != TIME_FORMAT_24HRS){
		am_pm = (current_time.time_format) ? "PM":"AM";
		printf("Current time = %s %s\n", time_to_string (&current_time), am_pm);
	}else{
		printf("Current time = %s\n", time_to_string(&current_time));
	}

	printf("Current date = %s <%s>\n", date_to_string(&current_date), get_day_of_week(current_date.day));

}

