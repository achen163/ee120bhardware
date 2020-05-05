/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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

enum States {start, light0, light1, light2} state;
unsigned char tmpB = 0x00;

void tick() {
	switch (state){
		case start:
			state = light0;
			break;
		case light0:
			state = light1;
			break;
		case light1:
			state = light2;
			break;
		case light2: 
			state = light0;
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
		default:
			break;
	}
	PORTB = tmpB;

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
