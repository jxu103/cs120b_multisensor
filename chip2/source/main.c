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

void set_PWM(double frequency) {
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; 
		else TCCR3B |= 0x03; 
		if (frequency < 0.954) OCR3A = 0xFFFF;
		else if (frequency > 31250) OCR3A = 0x0000;
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; 
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

int main( void ){
	DDRD = 0xFE; PORTD = 0x01;
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;

	initUSART(0); // initializes USART0
	unsigned char warningFlag = 0x00;
	PWM_on();
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
		if bit 4 is set one, then lights are out
		*/
		PORTA = warningFlag;
		if((warningFlag & 0x10) == 0x10){
		set_PWM(261.63);
		}
		else{
		set_PWM(0);
		}
		
		
	}
	return 0;
}
