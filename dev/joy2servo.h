/*
 * joy2servo.h
 *
 * Created: 17.12.2015 09:24:40
 *  Author: Technik
 */ 


#ifndef JOY2SERVO_H_
#define JOY2SERVO_H_
#include <stdint.h>
#include "joystick.h"

typedef struct {
	int8_t left;
	int8_t right;
} ServoVector;

ServoVector computeServo(JoystickVector);




#endif /* JOY2SERVO_H_ */