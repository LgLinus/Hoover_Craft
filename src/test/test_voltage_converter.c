/*
 * test_voltage_converter.c
 *
 * Created: 2015-05-18 22:39:34
 *  Author: Jesper och Linus
 */ 

#include "unity.h"
#include "values.h"

void test_voltage_converter(void)
{
	table = 2;
	TEST_ASSERT_EQUAL(0, voltage_to_distance(2000,FRONT_LEFT));
	TEST_ASSERT_EQUAL(5, voltage_to_distance(1700,FRONT_LEFT));
	TEST_ASSERT_EQUAL(5, voltage_to_distance(1800,FRONT_LEFT));
	TEST_ASSERT_EQUAL(0, voltage_to_distance(1800,BACK_RIGHT));
	TEST_ASSERT_EQUAL(35, voltage_to_distance(400,FRONT_LEFT));
}

/* WORKS */
void test_filter(void)
{
	TEST_ASSERT_EQUAL(1000, filter(1000*5,FRONT_LEFT));
	TEST_ASSERT_EQUAL(2000, filter(1000*5,FRONT_LEFT));
	TEST_ASSERT_EQUAL(500, filter(500*5,FRONT_RIGHT));
	TEST_ASSERT_EQUAL(200, filter(200*5,BACK_LEFT));
	
	TEST_ASSERT_EQUAL(10,iir_filter(100,BACK_LEFT));
	TEST_ASSERT_EQUAL(19,iir_filter(100,BACK_LEFT));
//	TEST_ASSERT_EQUAL(19,iir_filter(100,BACK_LEFT));
}
