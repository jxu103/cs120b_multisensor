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
#include "DHT.h"

uint16_t temperature_int = 0;
uint16_t humidity_int = 0;

int main( void ){
	DDRD = 0xFE, PORTD = 0x01;

	initUSART(0); // initializes USART0
	unsigned char temp;
	while (1) {
        
        if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
			if ( USART_IsSendReady(0) ) {
				USART_Send(temperature_int,0);
            while(!USART_HasTransmitted(0)){}
        }
		}
		
        
		
	}
	return 0;
}
