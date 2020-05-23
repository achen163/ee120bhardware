/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum states {Start, Light1, Light2, Light3} state;
enum states2 {Start2, On, Off} state2;
enum states3 {Start3, Combined} state3;
unsigned char result1 = 0x00;
unsigned char result2 = 0x00;

void tick () {
	switch(state){
		case Start:
			state = Light1;
			break;
		case Light1:
			state = Light2;
			break;
		case Light2:
			state = Light3;
			break;
		case Light3:
			state = Light1;
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			break;
		case Light1:
			result1 = 0x01;
			break;
		case Light2:
			result1 = 0x02;
			break;
		case Light3:
			result1 = 0x04;
			break;
		default:
			break;	
	}
}

void tick2() {
	switch(state2) {
		case Start2:
			state2 = On;
			break;
		case On:
			state2 = Off;
			break;
		case Off:
			state2 = On;
			break;
		default:
			state2 = Start2;
			break;
	}
	switch(state2) {
		case Start2:
			break;
		case On:
			result2 = 0x08;
			break;
		case Off:
			result2 = 0x00;
			break;
		default:
			break;
	}
}

void tick3() {
	switch(state3){
		case Start3:
			state3 = Combined;
			break;
		case Combined:
			state3 = Combined;
			break;
		default:
			state3 = Start3;
			break;
	}
	switch(state3) {
		case Start3:
			break;
		case Combined:
			PORTB = result1 | result2;
			break;
		default:
			break;
	}


}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	unsigned long first_elapsedTime = 0;
	unsigned long second_elapsedTime = 0;
	unsigned long third_elapsedTime = 0;
	const unsigned long timerPeriod = 50;
	TimerSet(timerPeriod);
	TimerOn();
	state = Start;
	state2 = Start2;
	state3 = Start3;

    /* Insert your solution below */
    while (1) {
		if (first_elapsedTime >= 300) {
	    		tick();
			first_elapsedTime = 0;
		}
		if (second_elapsedTime >= 1000) {
			tick2();
			second_elapsedTime = 0;
		}
		if (third_elapsedTime >= 50) {
			tick3();
			third_elapsedTime = 0;
		}
		
		while (!TimerFlag) {}
		TimerFlag = 0;
		first_elapsedTime += timerPeriod;
		second_elapsedTime += timerPeriod;
		third_elapsedTime += timerPeriod;
    }
    return 1;
}
