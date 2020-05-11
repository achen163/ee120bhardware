/*	Author: Alex Chen
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #7  Exercise #1
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
enum States {Start, NonePressed, PA0Pressed, Wait1, Wait2, PA1Pressed, BothPressed} state;
unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
unsigned char counter = 0x00;

void tick() {
	switch (state){
		case Start:
			LCD_Cursor(1);
			LCD_WriteData(0 + '0');
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
				counter++;
                        }

                        else if ((tempA & 0x02) == 0x02) {
                                state = PA1Pressed;

                        }
                        else {
                                state = NonePressed;
                        }

			break;
		case Wait1:
			if ((tempA & 0x03) == 0x03) {
				state = BothPressed;
				counter = 0;
			}
			else if ((tempA & 0x01) == 0x01) {
				state = Wait1;
				counter++;
			}
			else if ((tempA & 0x03) == 0x00){
				state = NonePressed;
				counter = 0;
			}
			else {
				state = Wait1;
			}

			break;
		case Wait2:
			if ((tempA & 0x03) == 0x03) {
				state = BothPressed;
				counter = 0;
			}
			else if ((tempA & 0x02) == 0x02) {
				state = Wait2;
				counter++;
			}
			else if ((tempA & 0x03) == 0x00){
				state = NonePressed;
				counter = 0;
			}
			else {
				state = Wait2;
			}
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
				counter++;
			}
			else {
				state = NonePressed;
			}

			break;
		case BothPressed:
			counter =0;
			if ((tempA & 0x03) ==0x03) {
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
		default:
			state = Start;
			break;

	}

	switch (state) {
		case Start:
			break;
		case NonePressed:
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');
			break;
		case PA0Pressed:
			tempB = PORTB;
			if (tempB < 9) {
				tempB = tempB + 1;
			}
			else {
				tempB = 9;
			}
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');
			break;
		case Wait1:
			if ((tempB < 9) && (counter % 10 == 0)) {
				tempB++;
			}
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');
			break;
		case Wait2:
			if ((tempB > 0) && (counter % 10 == 0 )) {
				tempB--;

			}
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');

			break;
		case PA1Pressed:
			tempB = PORTB;
			if (tempB > 0) {
				tempB = tempB - 1;
			}
			else {
				tempB = 0;
			}
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');
			break;
		case BothPressed:
			tempB = 0x00;
			LCD_Cursor(1);
			LCD_WriteData(tempB + '0');
			break;
		default:
			break;
	}

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
	TimerSet(100);
	TimerOn();
	LCD_init();
	state = Start;
    /* Insert your solution below */
    while (1){
	tempA = ~PINA & 0x03;
	tick();
	PORTB = tempB;
	while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
