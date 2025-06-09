/*
 * lcd.h
 *
 *  Created on: Jun 3, 2025
 *      Author: jesti
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
void LCD_send_command(uint8_t cmd);
void LCD_send_data(uint8_t data);
void LCD_Init(void);
void LCD_clear(void);
void LCD_print_string(char * message);

#define LCD_GPIO_PORT		GPIOD
#define LCD_GPIO_RS			GPIO_PIN_NO_0
#define LCD_GPIO_RW			GPIO_PIN_NO_1
#define LCD_GPIO_EN			GPIO_PIN_NO_2
#define LCD_GPIO_D4			GPIO_PIN_NO_3
#define LCD_GPIO_D5			GPIO_PIN_NO_4
#define LCD_GPIO_D6			GPIO_PIN_NO_5
#define LCD_GPIO_D7			GPIO_PIN_NO_6
void LCD_Init(void);
/*LCD commands */
#define LCD_CMD_4DL_2N_5X8F  		0x28
#define LCD_CMD_DON_CURON    		0x0E
#define LCD_CMD_INCADD       		0x06
#define LCD_CMD_DIS_CLEAR    		0X01
#define LCD_CMD_DIS_RETURN_HOME  	0x02


#endif /* LCD_H_ */
