#ifndef USART_H			
#define USART_H

#define F_CPU 8000000UL						/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>				


#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */

void USART_Init(unsigned long);				/* USART initialize function */
char USART_Receive();						/* Data receiving function */
void USART_Transmit(char);					/* Data transmitting function */
void USART_SendString(char*);				/* Send string of USART data function */


#endif									
