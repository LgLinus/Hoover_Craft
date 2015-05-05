/*
 * test_duty_cycle.c
 *
 * Created: 2015-05-05 10:11:29
 *  Author: ad2302
 */ 
#include "pwm_controller.h"
#include "unity.h"
void test_duty_cycle_DAC1(void) {
	TEST_ASSERT_EQUAL_MESSAGE(999,duty_cycle_DAC1,"wrong duty cycle DAC1");
}

void test_duty_cycle_36(void) {
	TEST_ASSERT_EQUAL_MESSAGE(600,duty_cycle_36,"wrong duty cycle DAC1");
}

void test_duty_cycle_38(void) {
	TEST_ASSERT_EQUAL_MESSAGE(600,duty_cycle_38,"wrong duty cycle DAC1");
}

void test_duty_cycle_40(void) {
	TEST_ASSERT_EQUAL_MESSAGE(500,duty_cycle_40,"wrong duty cycle DAC1");
}

void test_duty_cycle_9(void) {
	TEST_ASSERT_EQUAL_MESSAGE(700,duty_cycle_9,"wrong duty cycle DAC1");
}
void test_update_duty_cycle_DAC1(void) {
	update_duty_cycle_DAC1(0);
	TEST_ASSERT_EQUAL_MESSAGE(0,duty_cycle_DAC1,"wrong duty cycle DAC1");
}