/*
 * main.c
 *
 * Created: 2015-04-20 13:41:20
 *  Author: Jesper Hansen
 */ 

#include "asf.h"
#include "Util/analogDigitalConverter.h"
#include "Util/pwmInit.h"
#include "test_runner.h"

int main (void)
{
	board_init();
	sysclk_init();
	initialize_pwm();
	test_function();

	//
	//update_dutyCycle(999);		// 999 is the highest duty cycle
}

