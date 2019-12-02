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
	DDRD = 0xFE, PORTD = 0x01;
	DDRC = 0xFF, PORTC = 0x00;

	initUSART(0); // initializes USART0
	unsigned char temp = 0x00;
	while (1) {
		temp = USART_Receive(0);
		PORTC = temp;
	}
	return 0;
}
