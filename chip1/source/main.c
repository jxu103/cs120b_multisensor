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
#include "io.h"

uint16_t temperature_int = 0;
uint16_t humidity_int = 0;
unsigned char temperature = 0x00;
unsigned char rh = 0x00;

/*
if bit 0 is set one, then low temperature (below 20C)
if bit 1 is set one, then high temperature (above 24C)
If bit 2 is set one, then low RH (below 20%)
if bit 3 is set one, then high RH (above 60%)
*/
unsigned char warningFlag = 0x00;

void print_LCD(unsigned char temperature, unsigned char rh) {
	unsigned char* LCD_template = "Current:           Temp:  . C    Humidity:    %";
	LCD_DisplayString(1, LCD_template);
	
}

int main( void ){
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFE; PORTD = 0x01;

	initUSART(0); // initializes USART0
	LCD_init();
	
	unsigned char temp;
	while (1) {
        
		//get temperature and humidity level
        if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
			temperature = temperature_int / 10;
			rh = humidity_int / 10;
		}
		
		print_LCD(temperature,rh);

		//check levels, output level and send out warnings if needed
		warningFlag = 0x00;
		if(temperature < 20 ) {
			warningFlag = warningFlag || 0x01;
		}
		else if(temperature > 24) {
			warningFlag = warningFlag || 0x02;
		}

		if(rh < 20) {
			warningFlag = warningFlag || 0x04;
		}
		else if(rh > 60) {
			warningFlag = warningFlag || 0x08;
		}
		
        if(USART_IsSendReady(0)) {
			USART_Send(warningFlag,0);
			while(!USART_HasTransmitted(0));
		}
		
	}
	return 0;
}
