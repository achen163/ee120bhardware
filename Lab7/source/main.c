/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #7  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#include "timer.h"
#endif
enum States {start, light0, light1, light2, light3, press, release, WonGame,RestartGame} state;
unsigned char tmpB = 0x00;
unsigned char score = 0x05;
unsigned char count = 0x00;
unsigned char tmpA = 0x00;
unsigned char prev = 0x00;
void tick() {
	switch (state){
		case start:
			LCD_ClearScreen();
			score = 5;
			LCD_Cursor(1);
			LCD_WriteData(5 + '0');
			state = light0;
			break;
		case light0:
			if (prev == 1) {
				if ((tmpA & 0x01) == 0x00) {
					prev =0 ;
					state = light1;
				}
				else {
					state = light1;
				}
			}
	
			else if ((tmpA & 0x01) == 0x01) {
				if (score > 0) {
					score = score - 1;
				}
				state = press;

			}
			else {
				state = light1;
			}
			break;
		case light1:
			if (prev == 1) {
				if ((tmpA & 0x01) == 0x00) {
					prev = 0;
					state = light2;
				}
				else {	
					state = light2;
			
				}
			}
			else if ((tmpA & 0x01) == 0x01) {
				if (score < 9 ) {
					score = score+1;
					state = press;
				}
				if (score == 9) {
					state = WonGame;
				}
			}
			else {
				state = light2;
			}
			break;
		case light2:
		        if (prev == 1 ) {
				if ((tmpA & 0x01) == 0x00) {
					prev = 0;
					state = light3;
				}
				else {
					state = light3;
				}
				
			}
			else if ((tmpA & 0x01) == 0x01) {
				if (score > 0 ) {
					score = score - 1;
				}
				state = press;
			}
			else {
				state = light3;
			}
			break;
		case light3:
			if (prev == 1) {
				if ((tmpA & 0x01) == 0x00) {
					prev = 0;
					state = light0;
				}
				else {
					state = light0;
				}
			}
			else if ((tmpA & 0x01) == 0x01){
				if (score < 9 ) {
					score = score + 1;
					state = press;
				}
				if (score == 9 ) {
					state = WonGame;
					break;
				}
			}
			else {
				state = light0;
			}
			break;
		case press: 
			if (count < 1) { 
				if ((tmpA & 0x01) == 0x00) {
					state = release;
				}
			}
			else if (count == 1) {
				count = 0;
				state = light0;
			}	
			else{
				state = press;
			}
			break;

		case release:
			if ((tmpA & 0x01) == 0x01) {
				state = press;
				count++;
				prev = 1;		
			}
			else if ((tmpA & 0x01) == 0x00){
				state = release;
			}
			
			
			break;
		case WonGame:
			if (tmpA == 0x01) {
				state = RestartGame;
			}
			else {
				state = WonGame;
			}
			break;
		case RestartGame:
			state = start;
			break;
		default:
			state = start;
			break;

	}

	switch (state) {
		case start:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			break;
		case light0:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			tmpB = 0x01;
			break;
		case light1:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			tmpB = 0x02;
			break;
		case light2:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			tmpB = 0x04;
			break;
		case light3:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			tmpB = 0x02;
			break;
		case press:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			break;
		case release:
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			break;
		case WonGame:
			LCD_DisplayString(1, "YOU WON!! Click to play again :)");
			break;
		case RestartGame:
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
	DDRC = 0xFF;
	PORTC = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	TimerSet(300);
	TimerOn();
	LCD_init();
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
