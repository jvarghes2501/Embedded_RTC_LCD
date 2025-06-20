/*
 * STM32F407xx.h
 *
 *  Created on: Apr 17, 2025
 *      Author: jesti
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_
#include <stdint.h>
#include <stddef.h>

/*
 * ARM cortex Mx processor NVIC register addresses
 */
# define NVIC_ISER0	((volatile uint32_t*) 0xE000E100)
# define NVIC_ISER1	((volatile uint32_t*) 0xE000E104)
# define NVIC_ISER2	((volatile uint32_t*) 0xE000E108)
# define NVIC_ISER3	((volatile uint32_t*) 0xE000E10c)


# define NVIC_ICER0	((volatile uint32_t*) 0xE000E180)
# define NVIC_ICER1	((volatile uint32_t*) 0xE000E184)
# define NVIC_ICER2	((volatile uint32_t*) 0xE000E188)
# define NVIC_ICER3	((volatile uint32_t*) 0xE000E18c)

# define NVIC_PR_BASE_ADDR 		((volatile uint32_t*) 0xE000E400)
# define PR_BITS_IMPLEMENTED 	4
/*
 * Flash and SRAM memory base addresses
 */
# define FLASH_BASEADDR		0x08000000U
# define SRAM1_BASEADDR		0x20000000U
# define SRAM2_BASEADDR		0x20001C00U
# define ROM_BASEADDR		0x1FFF0000U
# define SRAM				SRAM1_BASEADDR



/*
 * AHBx and APBx bus peripheral base addresses
 */
# define APB1PERIPH_BASEADDR	0x40000000U
# define APB2PERIPH_BASEADDR	0x40010000U
# define AHB1PERIPH_BASEADDR	0x40020000U
# define AHB2PERIPH_BASEADDR	0x50000000U


/*
 * Peripherals base addresses attached to AHB1 bus
 */
# define GPIOA_BASEADDR		(AHB1PERIPH_BASEADDR + 0x0000)
# define GPIOB_BASEADDR		(AHB1PERIPH_BASEADDR + 0x0400)
# define GPIOC_BASEADDR		(AHB1PERIPH_BASEADDR + 0x0800)
# define GPIOD_BASEADDR		(AHB1PERIPH_BASEADDR + 0x0C00)
# define GPIOE_BASEADDR		(AHB1PERIPH_BASEADDR + 0x1000)
# define GPIOF_BASEADDR		(AHB1PERIPH_BASEADDR + 0x1400)
# define GPIOG_BASEADDR		(AHB1PERIPH_BASEADDR + 0x1800)
# define GPIOH_BASEADDR		(AHB1PERIPH_BASEADDR + 0x1C00)
# define GPIOI_BASEADDR		(AHB1PERIPH_BASEADDR + 0x2000)
# define RCC_BASEADDR		(AHB1PERIPH_BASEADDR + 0x3800)
/*
 * Peripherals base addresses attached to the APB1 bus
 */
# define I2C1_BASEADDR		(APB1PERIPH_BASEADDR + 0x5400)
# define I2C2_BASEADDR		(APB1PERIPH_BASEADDR + 0x5800)
# define I2C3_BASEADDR		(APB1PERIPH_BASEADDR + 0x5C00)

# define SPI2_BASEADDR		(APB1PERIPH_BASEADDR + 0x3800)
# define SPI3_BASEADDR		(APB1PERIPH_BASEADDR + 0x3C00)

# define USART2_BASEADDR	(APB1PERIPH_BASEADDR + 0x4400)
# define USART3_BASEADDR	(APB1PERIPH_BASEADDR + 0x4800)
# define UART4_BASEADDR		(APB1PERIPH_BASEADDR + 0x4C00)
# define UART5_BASEADDR		(APB1PERIPH_BASEADDR + 0x5000)


/*
 * Peripherals base addresses attached to the APB2 bus
 */
# define EXTI_BASEADDR		(APB2PERIPH_BASEADDR + 0x3C00)
# define SPI1_BASEADDR		(APB2PERIPH_BASEADDR + 0x3000)
# define SYSCFG_BASEADDR	(APB2PERIPH_BASEADDR + 0x3800)
# define USART1_BASEADDR	(APB2PERIPH_BASEADDR + 0x1000)
# define USART6_BASEADDR	(APB2PERIPH_BASEADDR + 0x1400)


/*
 * Peripheral structure definitions
 */

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_RegDef_t;

typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;
}RCC_RegDef_t;

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED1[2];
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;

}SYSCFG_RegDef_t;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t  CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_RegDef_t;


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
}I2C_RegDef_t;

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef_t;

/*
 * Peripheral definitions
 */

# define GPIOA		((GPIO_RegDef_t*)GPIOA_BASEADDR)
# define GPIOB		((GPIO_RegDef_t*)GPIOB_BASEADDR)
# define GPIOC		((GPIO_RegDef_t*)GPIOC_BASEADDR)
# define GPIOD		((GPIO_RegDef_t*)GPIOD_BASEADDR)
# define GPIOE		((GPIO_RegDef_t*)GPIOE_BASEADDR)
# define GPIOF		((GPIO_RegDef_t*)GPIOF_BASEADDR)
# define GPIOG		((GPIO_RegDef_t*)GPIOG_BASEADDR)
# define GPIOH		((GPIO_RegDef_t*)GPIOH_BASEADDR)
# define GPIOI		((GPIO_RegDef_t*)GPIOI_BASEADDR)

# define RCC 				((RCC_RegDef_t*)RCC_BASEADDR)
# define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)
# define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

# define SPI1					((SPI_RegDef_t*)SPI1_BASEADDR)
# define SPI2					((SPI_RegDef_t*)SPI2_BASEADDR)
# define SPI3					((SPI_RegDef_t*)SPI3_BASEADDR)

# define I2C1					((I2C_RegDef_t*)I2C1_BASEADDR)
# define I2C2					((I2C_RegDef_t*)I2C2_BASEADDR)
# define I2C3					((I2C_RegDef_t*)I2C3_BASEADDR)

# define USART1					((USART_RegDef_t)*USART1_BASEADDR)
# define USART2					((USART_RegDef_t) *USART2_BASEADDR)
# define USART3					((USART_RegDef_t) *USART3_BASEADDR)
# define USART6 				((USART_RegDef_t) *USART6_BASEADDR)

/*
 * Enable the clock for GPIOx peripherals
 */
#define GPIOA_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<0))
#define GPIOB_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<1))
#define GPIOC_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<2))
#define GPIOD_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<3))
#define GPIOE_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<4))
#define GPIOF_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<5))
#define GPIOG_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<6))
#define GPIOH_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<7))
#define GPIOI_CLOCK_ENABLE()	(RCC->AHB1ENR |= (1<<8))

/*
 * reset gpiox registers
 */
#define GPIOA_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); }while(0) // do while 0 used to fit multiple statements into a macro
#define GPIOB_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOF_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<5)); (RCC->AHB1RSTR &= ~(1<<5)); }while(0)
#define GPIOG_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<6)); (RCC->AHB1RSTR &= ~(1<<6)); }while(0)
#define GPIOH_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); }while(0)
#define GPIOI_REG_RESET()		do{(RCC->AHB1RSTR|=(1<<8)); (RCC->AHB1RSTR &= ~(1<<8)); }while(0)

/*
 * Enable the clock for I2Cx peripherals
 */
#define I2C1_CLOCK_ENABLE()	(RCC->APB1ENR |= (1<<21))
#define I2C2_CLOCK_ENABLE()	(RCC->APB1ENR |= (1<<22))
#define I2C3_CLOCK_ENABLE()	(RCC->APB1ENR |= (1<<23))


/*
 * Enable the clock for SPIx peripherals
 */
#define SPI1_CLOCK_ENABLE()	(RCC->APB2ENR |= (1<<12))
#define SPI2_CLOCK_ENABLE()	(RCC->APB1ENR |= (1<<14))
#define SPI3_CLOCK_ENABLE()	(RCC->APB1ENR |= (1<<15))
#define SPI4_CLOCK_ENABLE()	(RCC->APB2ENR |= (1<<13))


/*
 * Enable the clock for USARTx peripherals
 */
# define USART1_CLOCK_ENABLE()	(RCC->APB2ENR|=(1<<4))
# define USART2_CLOCK_ENABLE()	(RCC->APB1ENR|=(1<<17))
# define USART3_CLOCK_ENABLE()	(RCC->APB1ENR|=(1<<18))
# define USART6_CLOCK_ENABLE()	(RCC->APB1ENR|=(1<<5))

# define UART4_CLOCK_ENABLE()	(RCC->APB1ENR|=(1<<19))
# define UART5_CLOCK_ENABLE()	(RCC->APB1ENR|=(1<<20))

/*
 * Enable the clock for SYSCFG peripheral
 */
# define SYSCFG_CLOCK_ENABLE()	(RCC->APB2ENR|=(1<<14))



/*
 * Disable the clock for GPIOx peripherals
 */
#define GPIOA_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_CLOCK_DISABLE()	(RCC->AHB1ENR &= ~(1<<8))

/*
 * Disable the clock for I2Cx peripherals
 */
#define I2C1_CLOCK_DISABLE()	(RCC->APB1ENR &= ~(1<<21))
#define I2C2_CLOCK_DISABLE()	(RCC->APB1ENR &= ~(1<<22))
#define I2C3_CLOCK_DISABLE()	(RCC->APB1ENR &= ~(1<<23))


/*
 * Disable the clock for SPIx peripherals
 */
#define SPI1_CLOCK_DISABLE()	(RCC->APB2ENR &= ~(1<<12))
#define SPI2_CLOCK_DISABLE()	(RCC->APB1ENR &= ~(1<<14))
#define SPI3_CLOCK_DISABLE()	(RCC->APB1ENR &= ~(1<<15))
#define SPI4_CLOCK_DISABLE()	(RCC->APB2ENR &= ~(1<<13))


/*
 * Disable the clock for USARTx peripherals
 */
# define USART1_CLOCK_DISABLE()	(RCC->APB2ENR&=~(1<<4))
# define USART2_CLOCK_DISABLE()	(RCC->APB1ENR&=~(1<<17))
# define USART3_CLOCK_DISABLE()	(RCC->APB1ENR&=~(1<<18))
# define USART6_CLOCK_DISABLE()	(RCC->APB1ENR&=~(1<<5))

# define UART4_CLOCK_DISABLE()	(RCC->APB1ENR&=~(1<<19))
# define UART5_CLOCK_DISABLE()	(RCC->APB1ENR&=~(1<<20))


/*
 * Disable the clock for SYSCFG peripheral
 */
# define SYSCFG_CLOCK_DISABLE()	(RCC->APB2ENR&=~(1<<14))


/*
 * IRQ numbers of STM32F407 family
 */
#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI5_9 		23
#define IRQ_NO_EXTI10_15 	40
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51
#define IRQ_NO_SPI4			84
#define IRQ_NO_SPI5			85
#define IRQ_NO_SPI6			86
#define IRQ_NO_I2C1_EV		31
#define IRQ_NO_I2C1_ER		32
#define IRQ_NO_I2C2_EV		33
#define IRQ_NO_I2C2_ER		34
#define IRQ_NO_I2C3_EV		72
#define IRQ_NO_I2C3_ER		73


/*
 * Bit position definition for SPI_CR1 reg
 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_DFF			11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

/*
 * Bit position definition for SPI_CR2 reg
 */
#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF		    4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7

/*
 * Bit position definition for SPI_SR reg
 */
# define SPI_SR_RXNE		0
# define SPI_SR_TXE			1
# define SPI_SR_CHSIDE		2
# define SPI_SR_UDR			3
# define SPI_SR_CRCERR		4
# define SPI_SR_MODF		5
# define SPI_SR_OVR			6
# define SPI_SR_BSY			7
# define SPI_SR_FRE			8

/*
 * Bit positions definition for I2C peripheral
 */
//bit position definition for I2C_CR1
#define I2C_CR1_PE			0
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_SWRST		15

//bit position definition for I2C_CR2
# define I2C_CR2_FREQ		0
# define I2C_CR2_ITERREN	8
# define I2C_CR2_ITEVTEN	9
# define I2C_CR2_ITBUFEN	10

//bit position definition for I2C_OAR1
#define I2C_OAR1_ADD0		0
#define I2C_OAR1_ADD71		1
#define I2C_OAR1_ADD98		8
#define I2C_OAR1_ADDMODE	15

// bit position definition for I2C_SR1
#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF	 	4
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_TIMEOUT		14

// bit position definition for I2C_SR2
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_DUALF		7
//bit position definition for I2C_CCR
# define I2C_CCR_CCR		0
# define I2C_CCR_DUTY		14
# define I2C_CCR_FS			15


/*
 * bit position definition for USART
 */

//USART CR1 config

#define USART_CR1_RE		2
#define USART_CR1_TE		3
#define USART_CR1_IDLEIE	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE		7
#define USART_CR1_PEIE		8
#define USART_CR1_PS		9
#define USART_CR1_PCE		10
#define USART_CR1_M			12

//USART CR2 config

#define USART_CR2_STOP		13
#define USART_CR2_CLKEN		11
#define USART_CR2_CPOL		10
#define USART_CR2_CPHA		9

//USART CR3 config
#define USART_CR3_EIE		0
#define USART_CR3_IREN		1
#define USART_CR3_IRLP		2
#define USART_CR3_HDSEL		3
#define USART_CR3_NACK		4
#define USART_CR3_SCEN		5
#define USART_CR3_DMAR		6
#define USART_CR3_DMAT		7
#define USART_CR3_RTSE		8
#define USART_CR3_CTSE		9
#define USART_CR3_CTSIE		10
#define USART_CR3_ONEBIT	11

//USART SR config
#define USART_SR_PE			0
#define USART_SR_FE			1
#define USART_SR_NE			2
#define USART_SR_ORE		3
#define USART_SR_IDLE		4
#define USART_SR_RXNE		5
#define USART_SR_TC			6
#define USART_SR_TXE		7
#define USART_SR_LBD		8
#define USART_SR_CTS		9

//Generic macros
#define ENABLE 		1
#define DISABLE 	0
#define SET 		1
#define RESET		0


//#include "stm32f407xx_gpio_driver.h"
//#include "stm32f407xx_i2c_driver.c"
//#include "stm32f407xx_SPI_driver.h"


#endif /* INC_STM32F407XX_H_ */
