/*
 * test_pwm.c
 *
 * Created: 2015-04-20 15:21:45
 *  Author: Jesper
 */ 

#include "unity.h"
#include "asf.h"

/* Method testing channel 0 is enabled */
void test_pwm_channel_0(void)
{
	TEST_ASSERT_BIT_HIGH_MESSAGE(0, PWM->PWM_SR,"Wrong channel in enabled");
}

/* Method for testing channel 1 is enabled */