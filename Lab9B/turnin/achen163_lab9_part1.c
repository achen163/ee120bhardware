/*	Author: Alex Chen	
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempA = 0x00;

void set_PWM(double frequency) {
	static double current_frequency;

	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08;}
		else {TCCR3B |= 0x03;}

		if (frequency < 0.954) { OCR3A = 0xFFFF;}

		else if (frequency > 31250) { OCR3A = 0x0000; }

		else { OCR3A = (short) (8000000 / (128 * frequency)) -1; }

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);

	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States {Start, NonePressed, Pressed1, Pressed2, Pressed3, BothPressed} state;

void Tick() {
	switch(state){
		case Start: 
			state = NonePressed;
			break;
		case NonePressed:
			if (( tempA & 0x07 ) == 0x01) {
				state = Pressed1;
			}
			else if (( tempA & 0x07) == 0x02) {
				state = Pressed2;
			}
			else if ((tempA & 0x07) == 0x04) {
				state = Pressed3;
			}
			else if ((tempA & 0x07) == 0x03) {
				state = BothPressed;
			}
			else if ((tempA & 0x07) == 0x05) {
				state = BothPressed;
			}
			else if ((tempA & 0x07) == 0x06) {
				state = BothPressed;
			}
			else {
				state = NonePressed;
			}
			break;
		case Pressed1:
			if ((tempA & 0x07) == 0x01) {
				state = Pressed1;
			}
			else {
				state = NonePressed;
			}
			break;
		case Pressed2:
			if ((tempA & 0x07) == 0x02) {
				state = Pressed2;
			}
			else {
				state = NonePressed;
			}
			break;
		case Pressed3:
			if ((tempA & 0x07) == 0x04) {
				state = Pressed3;
			}
			else {
				state = NonePressed;
			}
			break;
		default:
			state = NonePressed;
			break;
	}
	switch(state) {
		case Start:
			break;
		case NonePressed:
			set_PWM(0);
			break;
		case Pressed1:
			set_PWM(261.63);
			break;
		case Pressed2:
			set_PWM(293.66);
			break;
		case Pressed3:
			set_PWM(329.63);
			break;
		case BothPressed:
			set_PWM(0);
			break;
		default:
			break;
	}


	
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	state = Start;
	PWM_on();
    /* Insert your solution below */
    while (1) {
	tempA = ~PINA;
	Tick();
    }
    return 1;
}

