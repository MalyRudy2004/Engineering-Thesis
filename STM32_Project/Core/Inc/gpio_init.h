/*
 * gpio_init.h
 *
 *  Created on: Oct 14, 2025
 *      Author: malyrudy
 */

#ifndef INC_GPIO_INIT_H_
#define INC_GPIO_INIT_H_

#include "main.h"
#include "stm32f303x8.h"


typedef enum MODER {
	INPUT = 0x0,
	OUTPUT = 0x1,
	ALTERNATE = 0x2,
	ANALOG = 0x3
}MODER;

typedef enum OTYPER {
	PUSHPULL = 0x0,
	OPENDRAIN = 0x1
}OTYPER;

typedef enum OSPEEDR {
	LOW = 0x0,
	MEDIUM = 0x1,
	HIGH = 0x3
}OSPEEDR;

typedef enum PUPDR {
	NOPULL = 0x0,
	PULLUP = 0x1,
	PULLDOWN = 0x2
}PUPDR;

typedef enum STATE{
	OFF = 0x0,
	ON = 0x1
}STATE;


void clock_enable();
void gpio_init(GPIO_TypeDef *port, uint8_t pin, enum MODER mode, enum OTYPER type, enum OSPEEDR speed, enum PUPDR pupd);

// -------------------------------------------------- COMPARATORS
// -------------------------------------------------- PB1 COMP1
// -------------------------------------------------- PB6 COMP2
// -------------------------------------------------- PB7 COMP3
// -------------------------------------------------- PB0 COMP4
#define COMP1pin 1
#define COMP1mask (1 << COMP1pin)
#define COMP2pin 6
#define COMP2mask (1 << COMP2pin)
#define COMP3pin 7
#define COMP3mask (1 << COMP3pin)
#define COMP4pin 0
#define COMP4mask (1 << COMP4pin)
void gpio_comp_init();

// -------------------------------------------------- ANALOG TO DIGITAL CONVERTER
// -------------------------------------------------- PA2 ADC1 -- wrong, vcp conected here, reschedule manualy for PA7	//ADC2 IN4
// -------------------------------------------------- PA3 ADC2 -- reschedule it for PA4 for balance						//ADC2 IN1
// -------------------------------------------------- PA0 ADC3															//ADC1 IN1
// -------------------------------------------------- PA1 ADC4															//ADC1 IN2
#define ADC1pin 7
#define ADC2pin 4
#define ADC3pin 0
#define ADC4pin 1
void gpio_adc_init();

// -------------------------------------------------- USART TO PC
// -------------------------------------------------- PA2 VCP_TX
// -------------------------------------------------- PA15 VCP_RX
#define USARTTXpin 2
#define USARTRXpin 15
#define AF7 0b0111
void gpio_usart_init();

#endif /* INC_GPIO_INIT_H_ */
