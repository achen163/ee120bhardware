/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #3
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

enum States {Start, NonePressed, PA0Pressed, Wait1, Wait2, PA1Pressed, BothPressed} state;
unsigned char tempA = 0x00;
unsigned char tempB = 0x07;
unsigned char counter = 0x00;

void tick() {
	switch (state){
		case Start:
			state = NonePressed;
			break;
		case NonePressed:
			if ((tempA & 0x03) == 0x03) {
				state = BothPressed;
			}
			else if ((tempA & 0x01) == 0x01) {
				state = PA0Pressed;
			}
	
			else if ((tempA & 0x02) == 0x02) {
				state = PA1Pressed;

			}
			else {
				state = NonePressed;
			}
			break;
		case PA0Pressed:
			if ((tempA & 0x03) == 0x03) {
                                state = BothPressed;
                        }
                        else if ((tempA & 0x01) == 0x01) {
                                state = Wait1;
                        }

                        else if ((tempA & 0x02) == 0x02) {
                                state = PA1Pressed;

                        }
                        else {
                                state = NonePressed;
                        }
			break;
		case Wait1:
		        if (counter > 9){
				if ((tempA & 0x03) == 0x03) {
					state = BothPressed;
				}
				else if ((tempA & 0x01) == 0x01) {
					state = PA0Pressed;
				}
				else if ((tempA & 0x03) == 0x00){
					state = NonePressed;
				}
				counter = 0;
			}
			else {
				state = Wait1;
			}
			counter++;
			break;
		case Wait2:
			if (counter > 9) {
				if ((tempA & 0x03) == 0x03) {
					state = BothPressed;
				}
				else if ((tempA & 0x02) == 0x02) {
					state = PA1Pressed;	
				}
				else if ((tempA & 0x03) == 0x00){
					state = NonePressed;
				}
				counter = 0;
			}
			else {
				state = Wait2;
			}
			counter++;
			break;
		case PA1Pressed:
			if ((tempA & 0x03) == 0x03) {
				state = BothPressed;	
			}
			else if ((tempA & 0x01) == 0x01) {
				state = PA0Pressed;
			}
			else if ((tempA & 0x02) == 0x02) {
				state = Wait2;
			}
			else {
				state = NonePressed;
			}
			break;
		case BothPressed:
			if ((tempA & 0x03) ==0x03) {

			}
			else if ((tempA & 0x01) == 0x01) {
				state = PA0Pressed;
			}
			else if ((tempA & 0x02) == 0x02) {
				state = PA1Pressed;
			}	
			else {
				state = NonePressed;
			}
		default:
			state = Start;
			break;

	}

	switch (state) {
		case Start:
			PORTB = 0x07;
			break;
		case NonePressed:
			break;
		case PA0Pressed:
			tempB = PORTB;
			if (PORTB < 9) {
				PORTB = tempB + 1;
			}
			break;
		case Wait1:
			break;
		case Wait2:
			break;
		case PA1Pressed:
			if (PORTB > 0) {
				PORTB = PORTB - 1;
			}
			break;
		case BothPressed:
			PORTB = 0x00;
			break;
		default:
			break;
	}

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x07;
	DDRA = 0x00;
	PORTA = 0xFF;
	TimerSet(100);
	TimerOn();
	state = Start;
    /* Insert your solution below */
    while (1){
	tempA = ~PINA & 0x03;
	tick();
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
