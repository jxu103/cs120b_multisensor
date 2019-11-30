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
#include "usart_ATmega1284.h"


int main( void ){
	DDRD = 0xFE, PORTD = 0x01;
	DDRC = 0xFF, PORTC = 0x00;

	initUSART(0); // initializes USART0
	unsigned char temp;
	while (1) {
		if ( USART_HasReceived(0) ) {
                   temp = USART_Receive(0);
                   USART_Flush(0);
               }
		if ( USART_IsSendReady(0) ) {
   		   USART_Send('h', 0);
                   while(!USART_HasTransmitted(0)){}
               }
	}
	return 0;
}
