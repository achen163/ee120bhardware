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

enum States {start, light0, light0wait, light1, light1wait, light2, light2wait, reset} state;
unsigned char tmpB = 0x00;
//unsigned char count = 0x01;
unsigned char tmpA = 0x00;
void tick() {
	switch (state){
		case start:
			state = light0;
			break;
		case light0:
			if ((tmpA & 0x01) == 0x01) {
				state = light0wait;
			}
			else {
				state = light1;
			}
			break;
		case light0wait:
			if ((tmpA & 0x01) == 0x01) {
				state = light0wait;
			}
			else {
				state = reset;
			}
			break;
		case light1:
			if ((tmpA & 0x01) == 0x01) {
				state = light1wait;
			}
			else {
				state = light2;
			}
			break;

		case light1wait:
			if ((tmpA & 0x01) == 0x01) {
				state = light1wait;
			}
			else {
				state = reset;
			}
			break;
		case light2: 
			if ((tmpA & 0x01) == 0x01) {
				state = light2wait;
			}
			else {
				state = light0;
			}
			break;
		case light2wait:
			if ((tmpA & 0x01) == 0x01) {
				state = light2wait;
			}
			else {
				state = reset;
			}
			break;
		case reset:
			if ((tmpA & 0x01) == 0x01) {
				state = PB0;
			}
			else {
				state = reset;
			}
			break;
/*		case press: 
			if ((tmpA & 0x01) == 0x00) {
				state = release;
			}
			else{
				state = press;
			}
			break;

		case release:
			if ((tmpA & 0x01) == 0x01) {
				state = PB0;		
			}
			else {
				state = release;	
			}
			
			break;
		case press2:
			if ((tmpA & 0x01) == 0x01) {
				state = light0;	
						}
			state = light0;
		break;
*/		default:
			state = start;
			break;

	}

	switch (state) {
		case start:
			break;
		case light0:
			tmpB = 0x01;
			break;
		case light0wait:
			break;
		case light1:
			tmpB = 0x02;
			break;
		case light1wait:
			break;
		case light2:
			tmpB = 0x04;
			break;
		case light2wait:
			break;
		case reset:
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
