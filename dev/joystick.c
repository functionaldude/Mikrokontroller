#include "joystick.h"
#include "io.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

extern uint16_t adc_get_asm(int8_t);

void joystick_init() {
	adc_init( 0x02 | 0x01 ); //Datenblatt s. 2
	printf("calibrating\n");
	
	extreme_raws.high_x_high_y.X = 0;
	extreme_raws.high_x_high_y.Y = 0;
	
	extreme_raws.low_x_low_y.X = 1000;
	extreme_raws.low_x_low_y.Y = 1000;
	
	while(!PUSH){
		int16_t x = adc_get(0);
		int16_t y = adc_get(1);
		
		if (x < extreme_raws.low_x_low_y.X){
			extreme_raws.low_x_low_y.X = x;
		}
		if (x > extreme_raws.high_x_high_y.X){
			extreme_raws.high_x_high_y.X = x;
		}
		
		if (y < extreme_raws.low_x_low_y.Y){
			extreme_raws.low_x_low_y.Y = y;
		}
		if (y > extreme_raws.high_x_high_y.Y){
			extreme_raws.high_x_high_y.Y = y;
		}
	}
	
	_delay_ms(20);
	//extreme_raws.idle.X = adc_get(0);
	//extreme_raws.idle.Y = adc_get(1);
	
	extreme_raws.idle.X = adc_get(0);
	extreme_raws.idle.Y = adc_get(1);
	
	printf("cal complete\n");
	printf("high:\n");
	printf("x: %d, y: %d\n", extreme_raws.high_x_high_y.X, extreme_raws.high_x_high_y.Y);
	printf("low:\n");
	printf("x: %d, y: %d\n", extreme_raws.low_x_low_y.X, extreme_raws.low_x_low_y.Y);
	printf("idle:\n");
	printf("x: %d, y: %d\n", extreme_raws.idle.X, extreme_raws.idle.Y);
}

int8_t convert_low_raw_x(uint16_t raw) {
	return ((raw * 100) / extreme_raws.idle.X) - 100;
}

int8_t convert_high_raw_x(uint16_t raw) {
	return ((raw - extreme_raws.idle.X) * 100) / (extreme_raws.high_x_high_y.X - extreme_raws.idle.X);
}

int8_t convert_low_raw_y(uint16_t raw) {
	return ((raw * 100) / extreme_raws.idle.Y) - 100;
}

int8_t convert_high_raw_y(uint16_t raw) {
	return ((raw - extreme_raws.idle.Y) * 100) / (extreme_raws.high_x_high_y.Y - extreme_raws.idle.Y);
}

int8_t compute_x(uint16_t raw){
	int8_t retval = (raw <= extreme_raws.idle.X) ? convert_low_raw_x(raw) : convert_high_raw_x(raw);
	if (abs(raw - extreme_raws.idle.X) <= 5) retval = 0;
	return retval;
}

int8_t compute_y(uint16_t raw){
	int8_t retval = (raw <= extreme_raws.idle.Y) ? convert_low_raw_y(raw) : convert_high_raw_y(raw);
	if (abs(raw - extreme_raws.idle.Y) <= 5) retval = 0;
	return retval;
}

JoystickVector joystick_status() {
	
	uint16_t raw_x = adc_get(0);
	uint16_t raw_y = adc_get(1);
	
	JoystickVector returnVector;
	returnVector.X = compute_x(raw_x);
	returnVector.Y = compute_y(raw_y);
	
	return returnVector;
}

