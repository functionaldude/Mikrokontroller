/*
 * servo.c
 *
 * Created: 26.11.2015 09:29:17
 *  Author: Technik
 */ 

#include "servo.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include "io.h"
#include <util/delay.h>
#include <stdio.h>

#define START_L 24
#define START_R 23
#define DELAY 24

void servo_init(){
	cli();
	TCCR2A |= (1<<COM2A1) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20); 
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
	sei();
	SERVO_RIGHT = START_R;
	SERVO_LEFT = START_L;
}

void servo_left(int16_t in){
	int8_t new_val;
	if (in == 0){
		new_val = START_L;
	} else {
		new_val = (((in*-1)+100)*16)/200 + 16;
	}
	int8_t old_val = SERVO_LEFT;
	if (new_val < old_val){
		while (SERVO_LEFT > new_val){
			SERVO_LEFT = --old_val;
			_delay_ms(DELAY);
		}
	} else {
		while (SERVO_LEFT < new_val){
			SERVO_LEFT = ++old_val;
			_delay_ms(DELAY);
		}
	}
	
	//SERVO_LEFT = (((in*-1)+100)*16)/200 + 16;
}

void servo_right(int16_t in){
	int8_t new_val;
	if (in == 0){
		new_val = START_R;
	} else {
		new_val = (((in)+100)*16)/200 + 16;
	}
	int8_t old_val = SERVO_RIGHT;
	if (new_val > old_val){
		while (SERVO_RIGHT < new_val){
			SERVO_RIGHT = ++old_val;
			_delay_ms(DELAY);
		}
	} else {
		while (SERVO_RIGHT > new_val){
			SERVO_RIGHT = --old_val;
			_delay_ms(DELAY);
		}
	}
}