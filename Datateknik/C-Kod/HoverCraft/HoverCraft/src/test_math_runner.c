/**
 * 
 * File responsible of running the test protocol for math functions
 */


#include "asf.h"
#include "test/unity.h"
#include <setjmp.h>
#include <stdio.h>

int main(void)
{
	board_init();
	sysclk_init();
	
	UnityBegin("test/test_math.c"); // Begin unity on the test protocol for test_math, run setUp() in test_math.c
	RUN_TEST(test_sum, 23); // Run the test_sum case. Lcoated on line 23
	RUN_TEST(test_diff, 35); // Run test_diff case.
	RUN_TEST(test_product,22);
	
	UnityEnd(); // End test protocol, print information
	
	return 0;
}