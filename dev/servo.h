/*
 * servo.h
 *
 * Created: 26.11.2015 09:29:28
 *  Author: Technik
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#include <stdint.h>
#include "joy2servo.h"

void servo_init();
void servo_go(ServoVector);

volatile int8_t coll;



#endif /* SERVO_H_ */