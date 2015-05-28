/*
 * controller_back.c
 *
 * File responsible of handling the controlling of the two back fans.
 *
 * Created: 2015-05-04 14:13:42
 *  Author: Linus Granath
 */ 

#include <asf.h>
#include "controller_back.h"
#include "values.h"
#include "pwm_controller.h"
#include "semaphores.h"

double u;
int e;
int invalue; // Difference between left, right
int activeFan; // Keep track on which fan to activate, 0 left, 1 right
int distance_left;
int distance_right;
int filtered_back_left;
int filtered_back_right;
int previous_value_back = 0;
int previous_control_signal = 0;

/* Start the communication task */
void start_controller_back(void *p)
{
	
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	

	/* Simple infinite loop, printing text with a given delay */
	while(1)
	{
		adc_start(ADC);
		
		// Wait for the end of conversion, check if data is ready
		while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY);

		int back_left_inductor;
		back_left_inductor = ADC->ADC_CDR[6]; // Retrieve latest vaule from back left inductor
		int back_right_inductor;
		back_right_inductor = ADC->ADC_CDR[5]; // Retrieve latest value from back right inductor
		
		xSemaphoreTake(semaphore_adc_values,portMAX_DELAY); // Take semaphore
		adc_value_back_left = back_left_inductor;
		adc_value_back_right = back_right_inductor;
		xSemaphoreGive(semaphore_adc_values); // Take semaphore
		
		controll_back_dead_beat(back_left_inductor,back_right_inductor);
		
		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
	}

}

/* Function responsible of controlling the back fans*/
void controll_back_dead_beat(int left, int right){

	double d0,d1,koffs;
	koffs = 0.0084*6;
	
	// Double pool
	d0 = 1/(koffs);
	d1 = -(0.75/(koffs));
	
	/* Filter the values from the sensor */
	filtered_back_left = filter(left,BACK_LEFT);
	filtered_back_right = filter(right,BACK_RIGHT);

	/* Convert from voltage to distance */
	distance_left = voltage_to_distance(filtered_back_left,BACK_LEFT);
	distance_right = voltage_to_distance(filtered_back_right,BACK_RIGHT);
	
	/* Regulate from the differens between the sensor */
	invalue = distance_left-distance_right;
		
	/* Error */
	e = 0 - ((d0*invalue) + (d1*previous_value_back));
	if(e < 0)
	{
		e=e*-1;
		activeFan = leftFan;
	}
	else
	{
		activeFan = rightFan;
	}
		
	/* Moves the value one step */
	previous_value_back = invalue;
	
	u = e;
	update_fan_cycle_back((int)u,activeFan);
	
} 
 /* Update the duty cycles for the fans. */
 void update_fan_cycle_back(int duty_cycle, int activeFan)
{
	/* Activate the correct fan */
 	if(activeFan==rightFan)
 	{
 		update_duty_cycle_40(standby_cycle+duty_cycle);		// Back right
 		update_duty_cycle_38(standby_torque);				// Back left
 	}
 	else
 	{
		update_duty_cycle_40(standby_cycle);
		update_duty_cycle_38(standby_torque + duty_cycle);
 	}
 }