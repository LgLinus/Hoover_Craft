/*
 * test_pwm.c
 *
 * Created: 2015-04-20 15:21:45
 *  Author: Jesper Hansen
 */ 

#include "unity.h"
#include "asf.h"

/* Method testing if PWM channel is enabled */
void test_pwm_channel_enabled(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	pwm_channel_enable(PWM, PWM_CHANNEL_2);
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	TEST_ASSERT_EQUAL_HEX32(0x0000001F, PWM->PWM_SR);	
}

