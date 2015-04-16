/*
* testmath.c
*
* Created: 2015-04-16 11:00:53
*  Author: Linus
*/
#include "math.h"
#include "unity.h"

int a;
int b;

/* Method that runs at Unitybegin in test_math_runner */
void setUp(void)
{
	a = 5;
	b = 2;

}

/* Method tat runs at Unityend(?) */
void tearDown(void)
{
	
}

/* Test methods for math operations */

void test_sum(void)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(7, sum(a,b), "ERROR"); // Test sum functions, expected result 7 (5+2), result is sum(a,b), display "ERROR" if false.
}

void test_diff(void)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, diff(a, b), "Error difference"); // Test  diff method
}

void test_product(void)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(a*b, product(a, b), "Error product"); // Test product method
}