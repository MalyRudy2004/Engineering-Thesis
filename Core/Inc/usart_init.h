/*
 * usart_init.h
 *
 *  Created on: Oct 16, 2025
 *      Author: malyrudy
 */

#ifndef INC_USART_INIT_H_
#define INC_USART_INIT_H_

#include "main.h"
#include "stm32f303x8.h"
#include "gpio_init.h"

//----------------------- ROOM MAP
#define A1 15
#define A1pos "pos: A1\n\r\0"
#define B1 18
#define B1pos "pos: B1\n\r\0"
#define C1 21
#define C1pos "pos: C1\n\r\0"
#define A2 28
#define A2pos "pos: A2\n\r\0"
#define B2 31
#define B2pos "pos: B2\n\r\0"
#define C2 34
#define C2pos "pos: C2\n\r\0"
#define A3 41
#define A3pos "pos: A3\n\r\0"
#define B3 44
#define B3pos "pos: B3\n\r\0"
#define C3 47
#define C3pos "pos: C3\n\r\0"
#define A4 54
#define A4pos "pos: A4\n\r\0"
#define B4 57
#define B4pos "pos: B4\n\r\0"
#define C4 60
#define C4pos "pos: C4\n\r\0"
#define A5 67
#define A5pos "pos: A5\n\r\0"
#define B5 70
#define B5pos "pos: B5\n\r\0"
#define C5 73
#define C5pos "pos: C5\n\r\0"
#define backspace_code 8
#define space_code 32

void usart2_init();
int send_char(char data);
int send_string(char *data);
int read(char *data);
void send_enter();
void clear_terminal();
void send_backspace();
int map(uint8_t i);


#endif /* INC_USART_INIT_H_ */
