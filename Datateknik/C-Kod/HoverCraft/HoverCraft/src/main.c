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
	//initialize_pwm();
	test_function();

	
	//update_dutyCycle_DAC1(999);		// 999 is the highest duty cycle
	//update_dutyCycle_36(600);
	//update_dutyCycle_38(600);
	//update_dutyCycle_40(500);
	//update_dutyCycle_9(700);
}

