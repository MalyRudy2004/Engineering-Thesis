/*
 * usart_init.c
 *
 *  Created on: Oct 16, 2025
 *      Author: malyrudy
 */

#include "usart_init.h"

void usart2_init()
{
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	gpio_usart_init();
	USART2 -> CR1 &= ~( USART_CR1_M1 | USART_CR1_M0 );
	USART2 -> BRR = (uint32_t)(8000000UL / 38400UL);
	USART2 -> CR2 &= ~USART_CR2_STOP;
	USART2 -> CR1 |= USART_CR1_UE;
	USART2 -> CR1 |= ( (USART_CR1_TE) | (USART_CR1_RE) );
}

int send_char(char data)
{
	while ( !(USART2 -> ISR & (USART_ISR_TXE)) );
	USART2 -> TDR = data;
	return 0;
}

int send_string(char *data)
{
	int i = 0;
	while (data[i] != '\0')
	{
		send_char(data[i]);
		i++;
	}
	return 0;
}

int read(char *data)
{
	while ( ((USART2 -> ISR & (USART_ISR_RXNE)) == 0) );
	*data = USART2 -> RDR;
	return 0;
}

void send_enter()
{
	char data[2] = "\r\n";
	send_string(data);
}

void clear_terminal()
{
	char data[8] = "\033[2J\033[H";
	send_string(data);
}

void send_backspace()
{
	send_char(backspace_code);
	send_char(space_code);
	send_char(backspace_code);
}

int map(uint8_t i)
{
	  char map[100] = "   A  B  C\n\r"
			  	  	  "1 [ ][ ][ ]\n\r"
			  	  	  "2 [ ][ ][ ]\n\r"
			  	  	  "3 [ ][ ][ ]\n\r"
			  	  	  "4 [ ][ ][ ]\n\r"
			  	  	  "5 [ ][ ][ ]\n\r";
	  map[i] = 'X';
	  send_string(map);
	  return 0;
}
