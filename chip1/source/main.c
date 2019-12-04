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

void print_LCD(uint16_t temperature, uint16_t rh) {
	
	//print temperature
	//print 10s
	unsigned char count = 0;
	while(temperature >= 100) {
		count ++;
		temperature -= 100;
	}
	LCD_Cursor(20);
	LCD_WriteData(count + '0');
	
	//print 1s
	count = 0;
	while(temperature >= 10) {
		count ++;
		temperature -= 10;
	}
	LCD_Cursor(21);
	LCD_WriteData(count + '0');
	
	//print decimals
	LCD_Cursor(24);
	LCD_WriteData((unsigned char)temperature + '0');
	
	
	//print temperature
	//print 100s
	count = 0;
	while(rh >= 100) {
		count ++;
		rh -= 100;
	}
	LCD_Cursor(20);
	LCD_WriteData(count + '0');
	
	//print 10s
	count = 0;
	while(rh >= 10) {
		count ++;
		rh -= 10;
	}
	LCD_Cursor(21);
	LCD_WriteData(count + '0');
	
	//print 1s
	LCD_Cursor(22);
	LCD_WriteData((unsigned char)rh + '0');
}

int main( void ){
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0xFE; PORTD = 0x01;

	initUSART(0); // initializes USART0
	LCD_init();
	unsigned char* LCD_template = "Current:  Temp:  . C    Humidity:    %";
	LCD_DisplayString(1, LCD_template);
	_delay_ms(1000);
	while (1) {
        
		//get temperature and humidity level
        if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
			temperature = temperature_int / 10;
			rh = humidity_int / 10;
			print_LCD(temperature_int, humidity_int);
		}
		else {
			LCD_ClearScreen();
			LCD_DisplayString(1,"Sensor Error");
		}
		_delay_ms(2000);
		
	}
	return 0;
}

