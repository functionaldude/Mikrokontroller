#ifndef __JOYSTICK_H__
#define  __JOYSTICK_H__

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"

typedef struct {
	int8_t X;
	int8_t Y;
} JoystickVector;

typedef struct {
	int16_t X;
	int16_t Y;
} JoystickRawVector;

typedef struct {	
	
	JoystickRawVector low_x_low_y;
	JoystickRawVector high_x_high_y;
	JoystickRawVector idle;
	
} ExtremeRaws;

ExtremeRaws extreme_raws;

void joystick_init();
extern void joystick_init_asm();
JoystickVector joystick_status();
extern JoystickVector joystick_status_asm();

#endif
