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
#include "timer.h"

#endif

unsigned char tempA = 0x00;
double sounds[9] = {311.13, 392.00, 523.25, 587.33, 466.16, 523.25,440,349.23, 391.9954 };
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

enum States {Start, Off, Play, ReleaseCheck} state;

void Tick() {
	switch(state){
		case Start: 
			state = Off;
			break;
		case Off:
			if ((tempA & 0x01) == 0x01) {
				state = Play;
			}
			else {
				state = Off;
			}
			break;
		case Play:
			if  (position < 10) {
				state = Play;
				position++;
			}
			else {
				state = ReleaseCheck;
			}
		case ReleaseCheck:
			if ((tempA & 0x07) == 0x00) {
				state = Start;
			}
			else {
				state = ReleaseCheck;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			break;
		case Off:
			break;
		case Play:
			set_PWM(sounds[position]);
			break;
		case ReleaseCheck:
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
	TimerSet(100);
	TimerOn();
	state = Start;
	PWM_on();
    /* Insert your solution below */
    while (1) {
	tempA = ~PINA;
	Tick();
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

