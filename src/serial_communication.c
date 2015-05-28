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
#include "semaphores.h"
#include "values.h"

int invalue;

/* Start the communication task */
void start_communication(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)	
	 {
		
		xSemaphoreTake(semahpore_duty_cycles,portMAX_DELAY); // Take semaphore
		/* Store the duty cycle values temporarily in this method */
		int duty_cycle_36_temp;
		duty_cycle_36_temp = duty_cycle_36;
		int duty_cycle_38_temp;
		duty_cycle_38_temp = duty_cycle_38;
		int duty_cycle_40_temp;
		duty_cycle_40_temp = duty_cycle_40;
		int duty_cycle_9_temp;
		duty_cycle_9_temp = duty_cycle_9;
		int duty_cycle_DAC1_temp;
		duty_cycle_DAC1_temp = duty_cycle_DAC1;
		
		xSemaphoreGive(semahpore_duty_cycles); // Give back the semaphore
		
		xSemaphoreTake(semaphore_adc_values,portMAX_DELAY); // Take semaphore
		
		/* Store the adc values temporarily in this file */
		int adc_value_back_left_temp;
		adc_value_back_left_temp = adc_value_back_left;
		int adc_value_back_right_temp = adc_value_back_right;
		adc_value_back_right_temp = adc_value_back_right;
		int adc_value_front_left_temp = adc_value_front_left;
		adc_value_front_left_temp = adc_value_front_left;
		int adc_value_front_right_temp = adc_value_front_right;
		adc_value_front_right_temp = adc_value_front_right;
		
		xSemaphoreGive(semaphore_adc_values); // Give back the semaphore
		
		/* Send information to bluetooth device*/
		printf("%d,%d,%d,%d,%d,%d,%d,%d",duty_cycle_36_temp,duty_cycle_38_temp,duty_cycle_40_temp,duty_cycle_9_temp,
										adc_value_back_left_temp,adc_value_back_right_temp,adc_value_front_left_temp,
										adc_value_front_right_temp);
		vTaskDelayUntil(&xLastWakeTime,COMMUNICATION_SCHEDULE_TIME); 	
		}
}