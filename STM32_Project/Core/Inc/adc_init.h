/*
 * adc_init.h
 *
 *  Created on: Oct 17, 2025
 *      Author: malyrudy
 */

#ifndef INC_ADC_INIT_H_
#define INC_ADC_INIT_H_

#include "main.h"
#include "gpio_init.h"


void adc_cal(ADC_TypeDef *adc, uint8_t *calfact);
void adc_re_cal(ADC_TypeDef *adc, uint8_t calfact);
void adc_init();
void adc_read(char output_buf[64]);

#endif /* INC_ADC_INIT_H_ */
