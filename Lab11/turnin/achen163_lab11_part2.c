/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "keypad.h"
#include "bit.h"
#include "io.h"
#include "scheduler.h"
#include "timer.h"
#endif

unsigned char x = 0x00;
unsigned char message[] = "CS120B is Legend... wait for it DARY!               "; //length of 52
unsigned char output[16] = "";
unsigned char cursor = 0x00;
enum LCDSM { start, LCD };

int LCDSM(int state) {
	switch(state) {
		case start:
			state = LCD;
			break;
		case LCD:
		       	state = LCD;
			break;
		default: state = start;
			 break;
	}
	switch (state) {
		case start: 
			break;
		case LCD:
			for (unsigned int i = 0; i < 16; i++) {
				output[i] = message[(cursor + i) % 52];	
			}
		// for loop gets 16 to print, cursor increases starting point of the message	
			LCD_DisplayString(1, output);
			cursor++;
			if (cursor == 53) { //total is 53 so it will go through as 53, increment and then hit this if statement to reset
				cursor = 0;
			}

			
			break;
		default:
			break;
	}
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
//	DDRA = 0x00;
//	PORTA = 0xFF;
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRB = 0xFF;
	PORTB	= 0x00;

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	const char start = -1;

	task1.state = start;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &LCDSM;

	
	TimerSet(10);
	TimerOn();
	LCD_init();
	unsigned short i;
    /* Insert your solution below */
    while (1) {
	for ( i = 0 ; i < numTasks; i++) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		
		}
		tasks[i]->elapsedTime += 10;
	}

	while (!TimerFlag);
	TimerFlag = 0;
    	
    }


    return 1;
}
