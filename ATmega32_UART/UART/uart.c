/*
 * uart.c
 *
 * Created: 02-May-25
 *  Author: P C Prusti
 */ 

#include "clockdefs.h"
#include <avr/io.h>
#include <stdint.h>
#include "defs.h"

#define UBRR(USART_BAUDRATE) (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

char rxbuff[50];

void UART_Init(uint32_t baud_rate)
{
	UBRRL = UBRR(baud_rate);			/* Load lower 8-bits of the baud rate value */
	UBRRH = (UBRR(baud_rate) >> 8);	/* Load upper 8-bits*/
	UCSRB |= (1 << RXEN) | (1 << TXEN);			/* Turn on transmission and reception */
	UCSRC |= (1<<URSEL) | (1 << UCSZ0) | (1 << UCSZ1);		/* Use 8-bit character sizes */
	
}

uint8_t UART_Receive()
{
	while ((UCSRA & (1 << RXC)) == 0);			/* Wait till data is received */
	return(UDR);								/* Return the byte*/
}

void UART_Transmit(uint8_t ch)
{
	while (! (UCSRA & (1<<UDRE)));				/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_Send_String(char *str)
{
	while (NULL != (*str))						/* Send string till null */
	{
		UART_Transmit(*(str++));
	}
}

char* UART_Receive_String(uint8_t en_echo)
{
	char data = UART_Receive();
	
	if(TRUE == en_echo)
	{
		UART_Transmit(data);
	}
	
	uint8_t counter = 0;
	
	while(data != '\r')
	{
		rxbuff[counter] = data;
		data = UART_Receive();
		if(TRUE == en_echo)
		{
			UART_Transmit(data);
		}
		counter++;
	}
	
	rxbuff[counter] = '\0';
	counter = 0;
	return rxbuff;
}
