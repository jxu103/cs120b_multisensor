/*	Author: jxu103
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

#define F_CPU 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

//char String[]="12345--Hello world--"; 

int main( void )
{
	USART_Init(MYUBRR);
	while (1)
	{
	}
	return 0;
}

void uart_init(void){	
	UBRR0H = MYUBRR;
	UBRR0L = MYUBRR;
	
	#if USE_2X
		UCSR0A |= _BV(U2X0);
	#else 
		UCSR0A &= ~(_BV(U2X0));
	#endif

	//CONFIGURE: 8 BIT DATA, 1 STOP BIT, NO PARITY
	
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); //SET 8 BIT DATA FRAME
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   //ENABLE RX AND TX
}
