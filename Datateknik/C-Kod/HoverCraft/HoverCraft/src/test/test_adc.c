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
/* Check if channel 3 is enabled*/
void test_channel_4_enabled(void){
	TEST_ASSERT_BIT_HIGH_MESSAGE(4,ADC->ADC_CHSR,"Channel 4 disabled");
}
/* Check if channel 3 is enabled*/
void test_channel_5_enabled(void){
	TEST_ASSERT_BIT_HIGH_MESSAGE(5,ADC->ADC_CHSR,"Channel 5 disabled");
}
/* Check if channel 3 is enabled*/
void test_channel_6_enabled(void){
	TEST_ASSERT_BIT_HIGH_MESSAGE(6,ADC->ADC_CHSR,"Channel 6 disabled");
}

/* Check if the adc pin is enabled*/
void test_adc_pin_enabled(void){
	TEST_ASSERT_BIT_HIGH_MESSAGE(PIO_PA6_IDX,PIOA->PIO_PSR,"Pin 3 is disabled");
}

/* Check if the adc pin is set to input */
void test_adc_pin_input(void){
	TEST_ASSERT_BIT_LOW_MESSAGE(PIO_PA6_IDX,PIOA->PIO_OSR,"Pin 3 is output");
}

/* Check if the adc pin is set to input */
void test_adc_pin_pullup(void){
	TEST_ASSERT_BIT_LOW_MESSAGE(PIO_PA6_IDX,PIOA->PIO_PUSR,"Pin 3 mode is not pullup");
}
