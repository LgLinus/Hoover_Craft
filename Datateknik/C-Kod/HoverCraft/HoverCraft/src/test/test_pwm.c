/*
 * test_pwm.c
 *
 * Created: 2015-04-20 15:21:45
 *  Author: Jesper Hansen
 */ 

#include "unity.h"
#include "asf.h"
#include "test_pwm.h"

/* Method testing if PWM channel is enabled */
void test_pwm_channel_enabled(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
<<<<<<< HEAD
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	pwm_channel_enable(PWM, PWM_CHANNEL_2);
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	TEST_ASSERT_EQUAL_HEX32(0x0000001F, PWM->PWM_SR);	
}

=======
	TEST_ASSERT_BIT_HIGH_MESSAGE(0, PWM->PWM_SR,"Wrong channel in enabled");
}

/* Method for testing channel 1 is enabled */
void test_pwm_channel_1(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	TEST_ASSERT_BIT_HIGH_MESSAGE(1, PWM->PWM_SR, "Wrong channel is enabled");
}

/* Method for testing channel 2 is enabled */
void test_pwm_channel_2(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_2);
	TEST_ASSERT_BIT_HIGH_MESSAGE(2, PWM->PWM_SR, "Wrong channel is enabled");
}

/* Method for testing channel 3 is enabled */
void test_pwm_channel_3(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
	TEST_ASSERT_BIT_HIGH_MESSAGE(3, PWM->PWM_SR, "Wrong channel is enabled");
}

/* Method for testing channel 4 is enabled */
void test_pwm_channel_4(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	TEST_ASSERT_BIT_HIGH_MESSAGE(4, PWM->PWM_SR, "Wrong channel is enabled");
}
>>>>>>> 922d6488929f892eaa570b3995759a188003cf84
