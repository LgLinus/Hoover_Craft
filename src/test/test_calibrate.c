/*
 * test_calibrate.c
 *
 * Created: 2015-05-21 14:37:36
 *  Author: Linus Granath
 */ 

#include "unity.h"
#include "values.h"

void test_calibration(void)
{
	TEST_ASSERT_EQUAL(0, get_table(520)); // 785,513,183
	TEST_ASSERT_EQUAL(2, get_table(250)); // 785,513,183
	TEST_ASSERT_EQUAL(1, get_table(500)); // 785,513,183
}
