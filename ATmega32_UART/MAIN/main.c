/*
 * main.c
 *
 * Created: 02-May-25
 *  Author: P C Prusti
 */


#include "clockdefs.h"
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <string.h>
#include "defs.h"
#include "uart.h"


int main() 
{
	uint32_t cnt = 0;
	char buff[20] = {0};
	char* rcvstr = NULL;
	UART_Init(9600);
	
	UART_Send_String("UART DEMO \r\n");
	
	while (1)
	{
		cnt ++;
		sprintf(buff,"Counter = %ld\r\n",cnt);
		UART_Send_String(buff);
		memset(buff, 0, 20);
		_delay_ms(1000);
		UART_Send_String("Enter a string:\r\n");
		rcvstr = (char*) UART_Receive_String(TRUE);
		UART_Send_String("string: ");
		UART_Send_String(rcvstr);
		UART_Send_String("\r\n");
		
	}
}
