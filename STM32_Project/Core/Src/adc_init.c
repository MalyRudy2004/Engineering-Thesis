/*
 * adc_init.c
 *
 *  Created on: Oct 17, 2025
 *      Author: malyrudy
 */

#include "adc_init.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void adc_cal(ADC_TypeDef *adc, uint8_t *calfact)
{
	RCC -> AHBENR |= RCC_AHBENR_ADC12EN;
	ADC12_COMMON -> CCR |= (0b01 << ADC12_CCR_CKMODE_Pos );
	adc -> CR &= ~ADC_CR_ADEN;
	adc -> CR &= ~ADC_CR_ADVREGEN;
	adc -> CR |= (0b01 << ADC_CR_ADVREGEN_Pos);
	HAL_Delay(1);
	adc -> CR &= ~ADC_CR_ADEN;
	adc -> CR &= ~ADC_CR_ADCALDIF;
	adc -> CR |= ADC_CR_ADCAL;
	while((adc -> CR & ADC_CR_ADCAL) != ADC_CR_ADCAL);
	*calfact = adc->CALFACT & ADC_CALFACT_CALFACT_S;
}

void adc_re_cal(ADC_TypeDef *adc, uint8_t calfact)
{
	adc -> CR |= ADC_CR_ADEN;
	adc -> CR &= ~ADC_CR_ADSTART;
	adc -> CALFACT &= ~ADC_CALFACT_CALFACT_S;
	adc -> CALFACT |= (calfact << ADC_CALFACT_CALFACT_S_Pos);
}

void adc_init()
{
	gpio_adc_init();

	ADC1 -> CFGR &= ~ADC_CFGR_CONT;
	ADC1 -> CFGR |= (0b10 << ADC_CFGR_RES_Pos);

	ADC2 -> CFGR &= ~ADC_CFGR_CONT;
	ADC2 -> CFGR |= (0b10 << ADC_CFGR_RES_Pos);
}

void adc_read(char output_buf[64])
{
    uint8_t data[4];
    char buf[32];
    int pos = 0;

    // --- ADC2: kanały IN4 (rank1) i IN1 (rank2) ---
    ADC2->SMPR1 &= ~(ADC_SMPR1_SMP1 | ADC_SMPR1_SMP4);
    ADC2->SMPR1 |=  ((0b100 << ADC_SMPR1_SMP1_Pos) | (0b100 << ADC_SMPR1_SMP4_Pos));

    ADC2->SQR1 &= ~(ADC_SQR1_L | ADC_SQR1_SQ1 | ADC_SQR1_SQ2);
    ADC2->SQR1 |=  ((0x1U << ADC_SQR1_L_Pos) | (0x4U << ADC_SQR1_SQ1_Pos) | (0x1U << ADC_SQR1_SQ2_Pos));

    if (!(ADC2->CR & ADC_CR_ADEN))
    {
        ADC2->CR |= ADC_CR_ADEN;
        while (!(ADC2->ISR & ADC_ISR_ADRDY));
    }

    ADC2->CR |= ADC_CR_ADSTART;
    for (int i = 0; i < 2; ++i)
    {
        while (!(ADC2->ISR & ADC_ISR_EOC));
        uint16_t raw = ADC2->DR;
        data[i] = (uint8_t)(raw & 0xFF);
    }

// --- ADC1: kanały IN1 (rank1) i IN2 (rank2)
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP1 | ADC_SMPR1_SMP2);
    ADC1->SMPR1 |=  ((0b100 << ADC_SMPR1_SMP1_Pos) | (0b100 << ADC_SMPR1_SMP2_Pos));

    ADC1->SQR1 &= ~(ADC_SQR1_L | ADC_SQR1_SQ1 | ADC_SQR1_SQ2);
    ADC1->SQR1 |=  ((0x1U << ADC_SQR1_L_Pos)| (0x1U << ADC_SQR1_SQ1_Pos) | (0x2U << ADC_SQR1_SQ2_Pos));

    if (!(ADC1->CR & ADC_CR_ADEN))
    {
        ADC1->CR |= ADC_CR_ADEN;
        while (!(ADC1->ISR & ADC_ISR_ADRDY));
    }

    ADC1->CR |= ADC_CR_ADSTART;
    for (int i = 0; i < 2; ++i)
    {
        while (!(ADC1->ISR & ADC_ISR_EOC));
        uint16_t raw = ADC1->DR;
        data[2 + i] = (uint8_t)(raw & 0xFF);
    }

    for (int i = 0; i < 4; ++i)
    {
    	uint16_t mv = ((uint16_t)data[i] * 3300U) / 255U;
    	int n = sprintf(buf, "ADC%d: %u mV\n\r", i+1, mv);
    	if (pos + n < 64)
    	{
    		memcpy(&output_buf[pos], buf, n);
    		pos += n;
    	}
    }
    output_buf[pos] = '\0';
}

//adc2 in1,4
//adc1 in1,2
