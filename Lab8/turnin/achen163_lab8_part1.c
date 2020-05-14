/*	Author: Alex Chen
 *  Partner(s) Name: ls
 *	Lab Section:22
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned short my_ADC = 0x00;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	my_ADC = ADC;
	PORTB = (char)my_ADC;
	PORTD = (char)(my_ADC >> 8);
    }
    return 1;
}
