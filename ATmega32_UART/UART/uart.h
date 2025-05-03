/*
 *uart.h
 *
 * Created: 02-May-25
 *  Author: P C Prusti
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

extern void UART_Init(uint32_t baud_rate);
extern uint8_t UART_Receive(void);
extern void UART_Transmit(uint8_t ch);
extern void UART_Send_String(char *str);
extern char* UART_Receive_String(uint8_t en_echo);

#endif /* UART_H_ */