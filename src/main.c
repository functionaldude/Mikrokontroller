#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "../include/uart.h"
#include "../include/joystick.h"
#include "../include/servo.h"
#include "../include/io.h"

int main(void) {


	uart_init(9600);
	
	DDRE = (1<<PE3) | (1<<PE5);
	DDRF &= ~((1<<PF3) | (1<<PF2));
	PORTF |= (1<<PF3);
	
	DDRB |= (1<<PB4);
	DDRH |= (1<<PH6);
	
	extreme_raws.high_x_high_y.X = 1011;
	extreme_raws.high_x_high_y.Y = 902;
	extreme_raws.low_x_low_y.X = 8;
	extreme_raws.low_x_low_y.Y = 8;
	extreme_raws.idle.X = 512;
	extreme_raws.idle.Y = 508;
	
	joystick_init_asm();
	servo_init();
	
	
	while(1) {
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
		
		JoystickVector vals = joystick_status_asm();
		printf("x: %d, y: %d\n",vals.X, vals.Y);
		servo_left(vals.Y);
		servo_right(vals.Y);
		
	}

	return 0;
}
