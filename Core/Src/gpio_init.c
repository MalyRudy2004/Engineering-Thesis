/*
 * gpio_init.c
 *
 *  Created on: Oct 14, 2025
 *      Author: malyrudy
 */
#include "gpio_init.h"

void clock_enable()
{
	RCC -> AHBENR |= ( (RCC_AHBENR_GPIOBEN) | (RCC_AHBENR_GPIOAEN) );
}


void gpio_init(GPIO_TypeDef *port, uint8_t pin, enum MODER mode, enum OTYPER type, enum OSPEEDR speed, enum PUPDR pupd)
{
	uint32_t tmp;

	tmp = port -> OTYPER;
	tmp &= ~(0x1 << pin);
	tmp |= (type << pin);
	port -> OTYPER = tmp;

	tmp = port -> OSPEEDR;
	tmp &= ~(0x3 << (2 * pin));
	tmp |= (speed << (2 * pin));
	port -> OSPEEDR = tmp;

	tmp = port -> PUPDR;
	tmp &= ~(0x3 << (2 * pin));
	tmp |= (pupd << (2 * pin));
	port -> PUPDR = tmp;

	tmp = port -> MODER;
	tmp &= ~( 0x3 << (2 * pin));
	tmp |= (mode << (2 * pin));
	port -> MODER = tmp;

}


void gpio_comp_init()
{
	gpio_init(GPIOB, COMP1pin, INPUT, OPENDRAIN, HIGH, NOPULL);
	gpio_init(GPIOB, COMP2pin, INPUT, OPENDRAIN, HIGH, NOPULL);
	gpio_init(GPIOB, COMP3pin, INPUT, OPENDRAIN, HIGH, NOPULL);
	gpio_init(GPIOB, COMP4pin, INPUT, OPENDRAIN, HIGH, NOPULL);
}


void gpio_adc_init()
{
	gpio_init(GPIOA, ADC1pin, ANALOG, PUSHPULL, LOW, NOPULL);
	gpio_init(GPIOA, ADC2pin, ANALOG, PUSHPULL, LOW, NOPULL);
	gpio_init(GPIOA, ADC3pin, ANALOG, PUSHPULL, LOW, NOPULL);
	gpio_init(GPIOA, ADC4pin, ANALOG, PUSHPULL, LOW, NOPULL);
}


void gpio_usart_init()
{
	gpio_init(GPIOA, USARTTXpin, ALTERNATE, PUSHPULL, HIGH, NOPULL);
	gpio_init(GPIOA, USARTRXpin, ALTERNATE, PUSHPULL, HIGH, PULLUP);
	GPIOA -> AFR[0] |= (AF7 << GPIO_AFRL_AFRL2_Pos);
	GPIOA -> AFR[1] |= (AF7 << GPIO_AFRH_AFRH7_Pos);
}


