/*
 * ds1307.c
 *
 *  Created on: Jun 3, 2025
 *      Author: jesti
 */
#include "ds1307.h"
#include "driver/inc/stm32f407xx_gpio_driver.h"
#include <string.h>
#include "driver/inc/stm32f407xx_i2c_driver.h"

I2C_Handle_t DS1307_I2CHandle;
static void DS1307_write(uint8_t value, uint8_t reg_addr);
static void DS1307_read(uint8_t reg_addr);
static uint8_t binary_to_bcd(uint8_t value);
static uint8_t bcd_to_binary(uint8_t value);

static void DS1307_write(uint8_t value, uint8_t reg_addr)
{
	uint8_t tx_data[2];
	tx_data[0] = reg_addr;
	tx_data[1] = value;

	I2C_MasterSendData(&DS1307_I2CHandle, tx_data, 2, DS1307_I2C_ADDRESS, 0);

}
static void DS1307_read(uint8_t reg_addr)
{
	uint8_t rx_Data;
	I2C_MasterSendData(&DS1307_I2CHandle, &reg_addr, 1, DS1307_I2C_ADDRESS, 0);
	I2C_MasterReceiveData(&DS1307_I2CHandle, &rx_Data, 1, DS1307_I2C_ADDRESS, 0);
	return rx_Data;
}

static uint8_t binary_to_bcd(uint8_t value)
{
	uint8_t m, n, bcd;
	bcd = value;
	if(value >= 10)
	{
		m = value/10;
		n = value % 10;
		bcd = (uint8_t)((m<<4)|n);
	}
	return bcd;
}
static uint8_t bcd_to_binary(uint8_t value)
{
	uint8_t m, n, bin;
	m = (uint8_t)((value >> 4) * 10);
	n = value & (uint8_t)0x0F;
	bin = m + n;
	return bin;
}

// if return 0 => initialization success
//if return 1 => initialization failed
uint8_t ds1307_init(void)
{
	// Initialize the I2C pins:
	GPIO_Handle_t I2C_SDA_PIN, I2C_SCL_PIN;
	memset(&I2C_SDA_PIN, 0, sizeof(I2C_SDA_PIN));
	memset(&I2C_SCL_PIN, 0, sizeof(I2C_SCL_PIN));

	I2C_SDA_PIN.pGPIOx = DS1307_I2C_GPIO_PORT;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinNumber = DS1307_I2C_SDA_PIN;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPE_OD;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinPull_up_down_control = DS1307_I2C_PUPD;
	I2C_SDA_PIN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&I2C_SDA_PIN);

	I2C_SCL_PIN.pGPIOx = DS1307_I2C_GPIO_PORT;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinNumber = DS1307_I2C_SCL_PIN;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPE_OD;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinPull_up_down_control = DS1307_I2C_PUPD;
	I2C_SCL_PIN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&I2C_SCL_PIN);

	//Configure the I2C peripheral
	DS1307_I2CHandle.pI2Cx = DS1307_I2C;
	DS1307_I2CHandle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	DS1307_I2CHandle.I2C_Config.I2C_SCLSpeed = DS1307_I2C_SPEED;
	I2C_Init(&DS1307_I2CHandle);

	// enable the I2C peripheral control
	I2C_PeripheralControl(DS1307_I2C, ENABLE);

	//to write into RTC module set the clock halt flag to 0
	DS1307_write(0x00, DS1307_ADDR_SEC);

	// read the clock halt bit to check if it was set
	uint8_t clock_halt_state = DS1307_write(DS1307_ADDR_SEC);

	return ((clock_halt_state >> 7) & 0x1);

}
void ds1307_set_current_time(RTC_time_t *rtc_time)
{
	uint8_t seconds,minutes, hours; //these have to be in BCD format to be accepted by the RTC module
	seconds = binary_to_bcd(rtc_time->seconds);
	seconds &=~(1<<7); // make the clock halt flag is 0
	DS1307_write(seconds, DS1307_ADDR_SEC);

	minutes = binary_to_bcd(rtc_time->minutes);
	DS1307_write(minutes, DS1307_ADDR_MIN);

	hours = binary_to_bcd(rtc_time->hours);
	if(rtc_time->time_format == TIME_FORMAT_24HRS)
	{
		hours &= ~( 1<<6);
	}else{
		hours|= (1<<6);
		if(rtc_time->time_format == TIME_FORMAT_12HRS_PM)
		{
			hours |= (1<<5);
		}
		else if (rtc_time->time_format == TIME_FORMAT_12HRS_AM)
		{
			hours &= ~(1<<5);
		}
	}

	DS1307_write(hours, DS1307_ADDR_HRS);


}
void ds1307_get_current_time(RTC_time_t *rtc_time)
{
	uint8_t seconds, minutes, hours;

	seconds = DS1307_read(DS1307_ADDR_SEC);
	seconds &= ~(1<<7);
	rtc_time->seconds = bcd_to_binary(seconds);

	minutes = DS1307_read(DS1307_ADDR_MIN);
	rtc_time->minutes = bcd_to_binary(minutes);

	hours = DS1307_read(DS1307_ADDR_HRS);

	if(hours & (1<<6))
	{
		//12 hour format
		if ((hours & (1<<5)))
		{
			rtc_time->time_format = TIME_FORMAT_12HRS_PM;
		}
		else{
			rtc_time->time_format = TIME_FORMAT_12HRS_AM;
			hours &= ~(0x3 << 5);
		}
	}
	else{
		//24 hour format
		rtc_time->time_format = TIME_FORMAT_24HRS;
	}
	rtc_time->hours = bcd_to_binary (hours);



}

void ds1307_set_current_date(RTC_date_t *rtc_date)
{
	uint8_t date,day, month, year; //these have to be in BCD format to be accepted by the RTC module
	date = binary_to_bcd(rtc_date->date);
	day = binary_to_bcd(rtc_date->day);
	month = binary_to_bcd(rtc_date->month);
	year = binary_to_bcd(rtc_date->year);

	DS1307_write(date, DS1307_ADDR_DATE);
	DS1307_write(day, DS1307_ADDR_DAY);
	DS1307_write(month, DS1307_ADDR_MONTH);
	DS1307_write(year, DS1307_ADDR_YEAR);


}
void ds1307_get_current_date(RTC_date_t *rtc_date)
{

}
