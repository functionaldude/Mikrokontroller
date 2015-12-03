/*
 * servo.h
 *
 * Created: 26.11.2015 09:29:28
 *  Author: Technik
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#include <stdint.h>

void servo_init();
void servo_left(int16_t);
void servo_right(int16_t);



#endif /* SERVO_H_ */