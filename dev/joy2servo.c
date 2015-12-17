/*
 * joy2servo.c
 *
 * Created: 17.12.2015 09:25:21
 *  Author: Technik
 */ 
#include "joy2servo.h"
#include "joystick.h"

ServoVector computeServo(JoystickVector input){
	ServoVector output;
	
	if(input.X == 0 && input.Y == 0){
		output.left = 0;
		output.right = 0;
	} else if(input.X == 0 && input.Y != 0){
		output.left = input.Y;
		output.right = input.Y;
	} else if(input.X > 0 && input.Y == 0){
		output.left = input.X;
		output.right = 0;
	} else if(input.X < 0 && input.Y == 0){
		output.left = 0;
		output.right = input.X*(-1);
	} else if(input.Y > 0){
		output.left = input.Y;
		output.right = input.Y;
		if(input.X > 0) output.right -= input.X;
		else output.left -= (-1)*input.X;
	} else if(input.Y < 0){   
		output.left = input.Y;
		output.right = input.Y;
		if(input.X > 0) output.right += input.X;
		else output.left += (-1)*input.X;
	}
	return output;
}