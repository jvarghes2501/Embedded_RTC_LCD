/*
 * lcd.c
 *
 *  Created on: Jun 3, 2025
 *      Author: jesti
 */

#include "lcd.h"
static void write_data_lines(uint8_t value);
static void LCD_enable(void);
static void mdelay(uint32_t count);
static void udelay(uint32_t count);

void LCD_send_command(uint8_t cmd)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET); //RS = 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET); //RnW = 0 to write to LCD

	write_data_lines(cmd >> 4);
	write_data_lines(cmd & 0x0F);
}

void LCD_send_data(uint8_t data)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_SET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write_data_lines(data >> 4);//higher 4 bits
	write_data_lines(data & 0x0F); // lower 4 bits


}

static void LCD_enable(void)
{
	//sends a pulse
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100);//wait for the instruction to finish processing on the LCD

}
void LCD_Init(void)
{
	//configure the GPIO pins used for LCD connection
	GPIO_Handle_t LCD_pin;
	LCD_pin.pGPIOx = LCD_GPIO_PORT;
	LCD_pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	LCD_pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPE_PP;
	LCD_pin.GPIO_PinConfig.GPIO_PinPull_up_down_control = GPIO_NO_PUPD;
	LCD_pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&LCD_pin);

	LCD_pin.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&LCD_pin);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);

	//wait 40ms for LCD screen to become functional
	mdelay(40);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET); //RS = 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET); //RnW = 0 to write to LCD
	write_data_lines(0x3);

	mdelay(5);

	write_data_lines(0x3);

	udelay(150);

	write_data_lines(0x3);
	write_data_lines(0x3);

	write_data_lines(LCD_CMD_4DL_2N_5X8F);

	write_data_lines(0x3);//command for display and curson being ON

	write_data_lines(LCD_CMD_DON_CURON);

	write_data_lines(LCD_CMD_DIS_CLEAR); // clear the display


	write_data_lines(LCD_CMD_DIS_CLEAR); // clear the display
	mdelay(2);







}

static void write_data_lines(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, ((value>>0)&0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, ((value>>1)&0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, ((value>>2)&0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, ((value>>3)&0x1));

	LCD_enable();


}

void LCD_clear(void)
{
	LCD_send_data(LCD_CMD_DIS_CLEAR); //sends the command to clear the display

	mdelay(2);
}

void LCD_return_home(void)
{
	LCD_send_data(LCD_CMD_DIS_RETURN_HOME); //sends the command to return cursor to home in the display

	mdelay(2);
}

static void mdelay(uint32_t count)
{
	for (uint32_t i = 0; i <(count * 1000); i++);
}

static void udelay(uint32_t count)
{
	for (uint32_t i = 0; i <(count); i++);
}

void LCD_print_string(char * message)
{
	do
	{
		LCD_send_data((uint8_t) *message++);
	}
	while(*message != '\0');
}
