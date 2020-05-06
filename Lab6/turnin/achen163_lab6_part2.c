/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States {start, light0, light1, light2, press, release} state;
unsigned char tmpB = 0x00;
unsigned char count = 0x00;
unsigned char tmpA = 0x00;
void tick() {
	switch (state){
		case start:
			state = light0;
			break;
		case light0:
			count = 0;
			if ((tmpA & 0x01) == 0x01) {
				state = press;
			}
			else {
				state = light1;
			}
			break;
		case light1:
			if ((tmpA & 0x01) == 0x01) {
				state = press;
			}
			else {
				state = light2;
			}
			break;
		case light2: 
			if ((tmpA & 0x01) == 0x01) {
				state = press;
			}
			else {
				state = light0;
			}
			break;
		case press: 
			if ((tmpA & 0x01) == 0x01) {
				state = press;
			}
			else{
				state = release;
			}
			break;

		case release:
			if( count < 1) {
				if ((tmpA & 0x01) == 0x01) {
					state = press;
					count++;
				}
			}
			else if (count ==1) {
				if ((tmpA & 0x01)==0x00 ) {
					state = light0;
				}
			}
			else {
				state = release;	
			}
			
			break;
		default:
			state = start;
			break;

	}

	switch (state) {
		case start:
			break;
		case light0:
			tmpB = 0x01;
			break;
		case light1:
			tmpB = 0x02;
			break;
		case light2:
			tmpB = 0x04;
			break;
		case press:
			break;
		case release:
			break;
		default:
			break;
	}
PORTB = tmpB;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
	TimerSet(300);
	TimerOn();
	state = start;
    /* Insert your solution below */
    while (1){
	tmpA = ~PINA;
	tick();
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
