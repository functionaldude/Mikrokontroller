#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "dev/uart.h"
#include "dev/io.h"
#include "dev/joystick.h"
#include "dev/servo.h"
#include "dev/joy2servo.h"
#include <avr/interrupt.h>

volatile JoystickVector j_state;

void blinker_init(){
	cli();
	TCCR1A = 0;
	TCCR1B |= (1<<CS11) | (1<<CS10);
	TIMSK1 |= (1<<OCIE1A);

	TCNT1H = 0x00;
	TCNT1L = 0x01;
	sei();
}

void init_push_interrupt(){
	cli();
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT5);
	sei();
}

ISR(TIMER1_COMPA_vect){
	//PORTE |= RED;
	if(j_state.X > 50){
		PINE |= YELLOW;
	} else if(j_state.X < -50){
		PINE |= RED;
	} else {
		PORTE &= ~(RED | YELLOW);
	}
}

ISR(PCINT0_vect){
	//PORTE |= RED;
	coll = 1;
}


int main(void) {
	
	uart_init(9600);

	
	DDRE = (1<<PE3) | (1<<PE5);
	DDRF &= ~((1<<PF3) | (1<<PF2));
	PORTF |= (1<<PF3);
	
	DDRB |= (1<<PB4);
	DDRH |= (1<<PH6);
	

	blinker_init();
	init_push_interrupt();
	
	joystick_init();
	servo_init();
	
	
	while(1) {
		/*
		if (!PUSH && !TILT) {
			PORTE |= RED | YELLOW;
			_delay_ms(50);
			PORTE &= ~(RED | YELLOW);
			_delay_ms(50);
		} else if (!TILT) {
			PORTE &= ~(YELLOW);
			PORTE |= RED;
			_delay_ms(50);
			PORTE &= ~(RED);
			_delay_ms(50);
		} else if (!PUSH) {
			PORTE &= ~(RED);
			PORTE |= YELLOW;
			_delay_ms(50);
			PORTE &= ~(YELLOW);
			_delay_ms(50);
		} else {
			PORTE &= ~(RED);
			PORTE |= YELLOW;
			_delay_ms(500);
			PORTE &= ~(YELLOW);
			PORTE |= RED;
			_delay_ms(500);
		}
		*/
		
		j_state = joystick_status();
		printf("x: %d, y: %d\n",j_state.X, j_state.Y);
		ServoVector s_vector = computeServo(j_state);
		servo_go(s_vector);
		
	}

	return 0;
}
