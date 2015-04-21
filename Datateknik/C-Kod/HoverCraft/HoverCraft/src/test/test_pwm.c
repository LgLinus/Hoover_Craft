/*
 * test_pwm.c
 *
 * Created: 2015-04-20 15:21:45
 *  Author: Jesper
 */ 

#include "unity.h"
#include "asf.h"
#include "test_pwm.h"

/* Method testing channel 0 is enabled */
void test_pwm_channel_0(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
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