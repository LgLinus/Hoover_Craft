/*
 * test_adc.c
 *
 * Created: 2015-04-19 17:01:32
 *  Author: Linus
 */ 
#include <asf.h>
#include "unity.h"

Adc* adc;

void setUp(){
}

void tearDown(){
	
}

void test_adc_enabled(void){
	
}

/* Method testing if the ADC resolution is 12 bit*/
void test_adc_12bit(void){
	TEST_ASSERT_BIT_LOW_MESSAGE(4,ADC->ADC_MR,"ADC is 10bit");
}

/* Check if channel 3 is enabled*/
void test_channel_3_enabled(void){
	TEST_ASSERT_BIT_HIGH_MESSAGE(3,ADC->ADC_CHSR,"Channel 3 disabled");
}