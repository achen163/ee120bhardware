/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #9  Exercise #2
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
double sounds[9] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25 };
unsigned char position = 0x00;
unsigned char pressCounter = 0x01;

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

enum States {Start, First, Increment, Decrement, ReleaseCheck, OnOff} state;

void Tick() {
	switch(state){
		case Start: 
			state = First;
			break;
		case First:
			if (( tempA & 0x07 ) == 0x01) {
				state = Increment;
			}
			else if (( tempA & 0x07) == 0x02) {
				state = Decrement;
			}
			else if ((tempA & 0x07) == 0x04) {
				state = OnOff;
			}
			else {
				state = First;
			}
			break;
		case Increment:
			state = ReleaseCheck;
			break;
		case Decrement:
			state = ReleaseCheck;
			break;
		case ReleaseCheck:
			if ((tempA & 0x07) == 0x00) {
				state = Start;
			}
			else {
				state = ReleaseCheck;
			}
			break;
		case OnOff:
			state = ReleaseCheck;
			break;
		default:
			state = First;
			break;
	}
	switch(state) {
		case Start:
			break;
		case First:
			break;
		case Increment:
			if ((position + 1) > 7) {
				position = 7;
			}
			else {
				position++;
			}
		//	set_PWM(sounds[position]);
			break;
		case Decrement:
			if ((position - 1) < 0) {
				position = 0;
			}
			else {
				position--;
			}
			//set_PWM(sounds[position]);
			break;
		case ReleaseCheck:
			set_PWM(sounds[position]);
			break;
		case OnOff:
			if (pressCounter == 1) {
				PWM_off();
				pressCounter = 0;
			}
			else {
				PWM_on();
				pressCounter = 1;
			}
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

