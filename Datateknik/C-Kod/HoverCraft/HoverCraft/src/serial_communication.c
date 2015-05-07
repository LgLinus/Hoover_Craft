/*
 * serial_communication.c
 * 
 * File responsible of handling the sending of information
 *
 * Created: 2015-05-04 14:13:42
 *  Author: Linus Granath
 */ 
#include <asf.h>
#include "serial_communication.h"
#include "pwm_controller.h"
#include "test/unity.h"
#include "semaphores.h"
#include "values.h"
extern void test_duty_cycle_36(void);
extern void test_duty_cycle_38(void);
extern void test_duty_cycle_40(void);
extern void test_duty_cycle_9(void);
extern void test_duty_cycle_DAC1(void);
extern void test_update_duty_cycle_DAC1(void);

/* Start the communication task */
void start_communication(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
 	int i;
	i = 0;
	UnityBegin("test/test_duty_cycle.h");
	RUN_TEST(test_duty_cycle_36,20);
	RUN_TEST(test_duty_cycle_38,20);
	RUN_TEST(test_duty_cycle_40,20);
	RUN_TEST(test_duty_cycle_9,20);
	RUN_TEST(test_duty_cycle_DAC1,20);
	RUN_TEST(test_update_duty_cycle_DAC1,20);
	UnityEnd();
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)
	 {
		 
		xSemaphoreTake(semahpore_duty_cycles,portMAX_DELAY); // Take semaphore
		/* Store the external variables temporarely */
		int duty_cycle_36_temp = duty_cycle_36;
		int duty_cycle_38_temp = duty_cycle_38;
		int duty_cycle_40_temp = duty_cycle_40;
		int duty_cycle_9_temp = duty_cycle_9;
		int duty_cycle_DAC1_temp = duty_cycle_DAC1;

		xSemaphoreGive(semahpore_duty_cycles); // Give back the semaphore
		
		/* Print out duty cycle information */
		printf("Duty cycle DAC1: %d\n\r",duty_cycle_DAC1_temp);
		printf("Duty cycle 36: %d\n\r",duty_cycle_36_temp);
		printf("Duty cycle 38: %d\n\r",duty_cycle_38_temp);
		printf("Duty cycle 40: %d\n\r",duty_cycle_40_temp);
		printf("Duty cycle 9: %d\n\r",duty_cycle_9_temp);
		
		xSemaphoreTake(semaphore_adc_values,portMAX_DELAY); // Take semaphore
		int adc_value_back_left_temp = adc_value_back_left;
		int adc_value_back_right_temp = adc_value_back_right;
		int adc_value_front_left_temp = adc_value_front_left;
		int adc_value_front_right_temp = adc_value_front_right;
		xSemaphoreGive(semaphore_adc_values); // Give back the semaphore
		printf("AD FRONT_LEFT: %d\n\r",adc_value_front_left_temp);
		printf("AD FRONT_RIGHT: %d\n\r",adc_value_front_right_temp);
		printf("AD BACK_LEFT: %d\n\r",adc_value_back_left_temp);
		printf("AD BACK_RIGHT: %d\n\r",adc_value_back_right_temp);
		
 		vTaskDelayUntil(&xLastWakeTime,COMMUNICATION_SCHEDULE_TIME);
 	}
}