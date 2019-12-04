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

int8_t temperature_int = 0;
int8_t humidity_int = 0;
unsigned char temperature = 0x00;
unsigned char rh = 0x00;

unsigned short AD_convert = 0x0000;
unsigned short MAX = 0xFF;

void ADC_init(){
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

void output_temperature(unsigned char temperature) {
	if(temperature >= 28) {
		PORTC = 0xFF;
	}
	else if(temperature >= 27) {
		PORTC = 0x7F;
	}
	else if(temperature >= 26) {
		PORTC = 0x3F;
	}
	else if(temperature >= 25) {
		PORTC = 0x1F;
	}
	else if(temperature >= 24) {
		PORTC = 0x0F;
	}
	else if(temperature >= 23) {
		PORTC = 0x07;
	}
	else if(temperature >= 22) {
		PORTC = 0x03;
	}
	else if(temperature >= 21) {
		PORTC = 0x01;
	}
}

int main( void ){
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0xFE; PORTD = 0x01;

	initUSART(0); // initializes USART0
	unsigned char warningFlag = 0x00;
	ADC_init();
	while (1) {
        warningFlag = 0x00;
		//get temperature and humidity level
        if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
			temperature = temperature_int;
			rh = humidity_int;
			output_temperature(temperature);
		}
		else {
			PORTC = 0xFF;
		}
	
		/*
		set warningFlags
		if bit 0 is set one, then low temperature (below 20C)
		if bit 1 is set one, then high temperature (above 24C)
		If bit 2 is set one, then low RH (below 20%)
		if bit 3 is set one, then high RH (above 60%)
		if bit 4 is set one, then lights are out;
		*/
		AD_convert = ADC;
		if(AD_convert >= MAX/2) {
			warningFlag |= 0x10;
		}
		if(temperature < 20) {
			warningFlag |= 0x01;
		}
		else if(temperature > 24) {
			warningFlag |= 0x02;
		}
		if(rh < 20) {
			warningFlag |= 0x04;
		}
		else if(rh > 60) {
			warningFlag |= 0x08;
		}
		
		
		USART_Send(warningFlag,0);
		_delay_ms(1500);
		
	}
	return 0;
}

