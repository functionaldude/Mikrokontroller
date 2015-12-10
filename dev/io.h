/*
 * io.h
 *
 * Created: 26.11.2015 09:23:06
 *  Author: Technik
 */ 


#ifndef IO_H_
#define IO_H_

#include <avr/io.h>

#define RED (1 << PE5)
#define YELLOW (1 << PE3)

#define PUSH (PINF & (1<<PF2))
#define TILT !(PINF & (1<<PF3))

#define SERVO_LEFT OCR2B
#define SERVO_RIGHT OCR2A


#endif /* IO_H_ */