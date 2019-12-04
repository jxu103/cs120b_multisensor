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
#include <util/delay.h>
#include "usart_ATmega1284.h"



int main( void ){
	DDRD = 0xFE; PORTD = 0x01;
	DDRA = 0xFF; PORTA = 0x00;

	initUSART(0); // initializes USART0
	unsigned char warningFlag = 0x00;
	while (1) {
		//receive warning info
		if(USART_HasReceived(0)) {
			warningFlag = USART_Receive(0);
			USART_Flush(0);
		}
		/*
		if bit 0 is set one, then low temperature (below 20C)
		if bit 1 is set one, then high temperature (above 24C)
		If bit 2 is set one, then low RH (below 20%)
		if bit 3 is set one, then high RH (above 60%)
		*/
		PORTC = warningFlag;
		
	}
	return 0;
}
