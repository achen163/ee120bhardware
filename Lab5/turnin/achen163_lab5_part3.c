/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, NonePressed, PA0Pressed, PA0Released} state;

unsigned char tempA = 0x00;
unsigned char tempC = 0x01;
unsigned char counter = 0x00;
unsigned char numCount = 0x00;
void Tick() {
	switch(state) {
		case Start:
			state = NonePressed;		
			break;
		case NonePressed:
			if ((tempA & 0x01) == 0x01) {
				state = PA0Pressed;
			}
			else {
				state = NonePressed;
			}
			break;
		case PA0Pressed:
			state = PA0Released;
			break;
		case PA0Released:
	                if ((tempA & 0x01) == 0x01) {
                                state = PA0Released;
           		}
			else {
				state = NonePressed;
			}          
			break;
		default:
			state = Start;
			break;
	}

	switch(state) {
		case Start:
			break;
		case NonePressed:	
			break;
		case PA0Pressed:
			if (numCount < 7) {
				tempC = tempC * 2;
					
			}
		 	else if (numCount < 13) {
				tempC = tempC / 2;
			}
			else {
				numCount = 0;
			}
			numCount++;
			break;
		case PA0Released:
			break;
		
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00;
PORTA = 0xFF;
DDRC = 0xFF;
PORTC = 0x00;
state = Start;
    /* Insert your solution below */
    while (1) {
	tempA = ~PINA ;
    	Tick();
	PORTC = tempC;
    }
    return 1;
}
