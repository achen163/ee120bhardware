/*	Author: Alex Chen
 *  Partner(s) Name: ls
 *	Lab Section:22
 *	Assignment: Lab #8  Exercise #4
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
unsigned short max = 0x1C3;
unsigned count = 0x00;
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
	count = max/8;
	if (my_ADC <= count) {
		PORTB = 0x01;
	}
	else if (my_ADC <= (count*2)){
		PORTB = 0x03;
	}
	else if (my_ADC <= (count*3)) {
		PORTB = 0x07;
	}
	else if (my_ADC <= (count*4)){
		PORTB = 0x0F;
        }
        else if (my_ADC <= (count*5)) {
                PORTB = 0x1F;
        }
	else if (my_ADC <= (count*6)){
                PORTB = 0x3F;
        }
        else if (my_ADC <= (count*7)) {
                PORTB = 0x7F;
        }
	else {
		PORTB = 0xFF;
	}


    }
    return 1;
}
