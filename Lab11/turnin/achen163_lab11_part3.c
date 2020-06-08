/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #11  Exercise #3
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

enum keypad_states { start, keypad };

int keypadSM(int state) {
	unsigned char x;
	x = GetKeypadKey();
	switch(state) {
		case start:
			state = keypad;
			break;
		case keypad:
		       	state = keypad;
			break;
		default: state = start;
			 break;
	}
	switch (state) {
		case start:	
			break;
		case keypad:
			switch(x) {
				case '\0':
					x = 0x1F;
					break;
				case '0':
					x = 0x00;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
					break;	
				case '1':
					x = 0x01;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
					break;
				case '2':
					x = 0x02;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
					break;
				case '3':
                                        x = 0x03;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
                                        break;	
				case '4':
                                        x = 0x04;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
                                        break;
                                case '5':
					x = 0x05;
                                        LCD_Cursor(1);
					LCD_WriteData(x + '0');
					break;
                                case '6':         
                                        x = 0x06;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
                                        break;
                                case '7':
                                        x = 0x07;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
                                        break;
                                case '8':
                                        x = 0x08;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
                                        break;
				case '9':
					x = 0x09;
					LCD_Cursor(1);
					LCD_WriteData(x + '0');
					break;
                                case 'A':
                                        x = 65;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;
                                case 'B':
                                        x = 66;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;
                                case 'C':
                                        x = 67;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;
                                case 'D':
                                        x = 68;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;
                                case '#':
                                        x = 35;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;
                                case '*':         
                                        x = 42;
					LCD_Cursor(1);
					LCD_WriteData(x);
                                        break;	
			}
			break;
		default:
			break;
	}
	return state;
}/*
enum display_states { display_start, display};
int displaySM(int state) {
	switch(state) {
		case display_start:
			state = display;
			break;
		case display:
			state = display;
			break;
		default:
			state = display_start;
			break;
		
	}
	switch(state) {
		case display_start:
			break;
		case display:
			LCD_Cursor(1);
			LCD_WriteData(x);
			break;
		default:
			break;

			
	}
}

*/
int main(void) {
    /* Insert DDR and PORT initializations */
//	DDRA = 0x00;
//	PORTA = 0xFF;
	DDRD = 0xFF;
	PORTD = 0x00;

	DDRC = 0xF0;
	PORTC = 0x0F;
	
	DDRB = 0xFF;
	PORTB = 0x00;

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	const char start = -1;

	task1.state = start;
	task1.period = 10;
	task1.elapsedTime = task1.period;
	task1.TickFct = &keypadSM;
	
/*	task2.state = start;
	task2.period = 10;
	task2.elapsedTime = task2.period;
	task2.TickFct = &displaySM;
*/	
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
