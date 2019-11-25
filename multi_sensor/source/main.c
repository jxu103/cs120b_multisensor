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
#include <dht.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

dht DHT;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRD 0xFF; PORTD 0x00;

    /* Insert your solution below */
    while (1) {
        int check = DHT.read11(PORTD);
    }
    return 1;
}
