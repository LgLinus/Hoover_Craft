/*
 * controller_front.c
 *
 * File responsible of handling the controlling of the two front fans.
 *
 * Created: 2015-05-05 11:00:00
 *  Author: Linus Granath
 */ 

#include <asf.h>
#include "controller_front.h"
#include "values.h"
#include "pwm_controller.h"
#include "semaphores.h"

int16_t sum_front = 0;
double u;
int32_t e;
int invalue; // Difference between left, right
int8_t activeFan; // Keep track on which fan to activate, 0 left, 1 right
int left_in_distance;
int right_in_distance;
int filtered_front_left;
int filtered_front_right;
int previous_value_front = 0;
int previous_control_signal_front = 0;
int distance_left_temp = 0;
int distance_right_temp = 0;

/* Start the communication task */
void start_controller_front(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)
	 {
		//ioport_set_pin_level(PIO_PD1_IDX,HIGH);
		adc_start(ADC);

		// Wait for the end of conversion, check if data is ready
		while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY);
		
		int front_left_inductor;
		front_left_inductor = ADC->ADC_CDR[3];
		int front_right_inductor;
		front_right_inductor = ADC->ADC_CDR[4];
			
		xSemaphoreTake(semaphore_adc_values,portMAX_DELAY); // Take semaphore
		adc_value_front_left = front_left_inductor;
		adc_value_front_right = front_right_inductor;
		xSemaphoreGive(semaphore_adc_values); // Take semaphore
		
		controll_front_dead_beat(front_left_inductor,front_right_inductor);
		
 		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
 	}
}

/* Onoff controll, used when testing different control methods*/
void controll_front_onoff(int left, int right){
	
	/* Filter the values from the sensor */
	filtered_front_left = filter(left,BACK_LEFT);
	filtered_front_right = filter(right,BACK_RIGHT);
	
	/* Convert from voltage to distance */
	left_in_distance = voltage_to_distance(filtered_front_left,BACK_LEFT);
	right_in_distance = voltage_to_distance(filtered_front_right,BACK_RIGHT);
	
	if(left_in_distance > right_in_distance)
	{
		activeFan = leftFan;
	}
	else
	{
		activeFan = rightFan;
	}
	
	update_fan_cycle_front(999,activeFan);
}

/* Function responsible of controlling the back fans*/
void controll_front_dead_beat(int left, int right){

	double d0,d1,koffs;
	
	koffs = 0.0084*6;
	// Dead beat
	// 	d0 = 2/(koffs);
	// 	d1 = -(1/(koffs));
		
	// Double pool
	d0 = 1/(koffs);
	d1 = -(0.75/(koffs));
	/* Filter the values from the sensor */
	filtered_front_left = filter(left,FRONT_LEFT);
	filtered_front_right = filter(right,FRONT_RIGHT);
	
	/* Convert from voltage to distance */
	left_in_distance = voltage_to_distance(filtered_front_left,FRONT_LEFT);
	distance_left_temp = left_in_distance;
	right_in_distance = voltage_to_distance(filtered_front_right,FRONT_RIGHT);
	distance_right_temp = right_in_distance;

	/* Calculate the difference from the sensor */
	invalue = left_in_distance-right_in_distance;

	/* Error */
	e = 0 - ((d0*invalue) + (d1*previous_value_front));
		
	/* Moves current value one step */
	previous_value_front = invalue;
	
	if(e < 0){
		e=e*-1;
		activeFan = leftFan;
	}
	else{
		activeFan = rightFan;
	}
		
	
	/* Regulator-part */
	u = e;

	update_fan_cycle_front((int)u,activeFan);
	
}
/* Update the duty cycles for the fans. */
void update_fan_cycle_front(int duty_cycle, int active_Fan){
	
	if(active_Fan==rightFan)
	{
		update_duty_cycle_36(standby_torque + duty_cycle); // FRONT RIGHT
		update_duty_cycle_DAC1(standby_cycle); // FRONT LEFT
	}
	else
	{
		update_duty_cycle_36(standby_torque);
		update_duty_cycle_DAC1(standby_cycle + duty_cycle);
	}
}