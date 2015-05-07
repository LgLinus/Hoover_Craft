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

int sum_front = 0;
double u;
int e;
double PI;
double PD;
int invalue; // Difference between left, right
int activeFan; // Keep track on which fan to activate, 0 left, 1 right
int d_buffert_front[d_buffer] = {0};
int current_buffert_front[buffert_size] = {0};
int current_value;

/* Start the communication task */
void start_controller_front(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
 	int i;
	i = 0;
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)
	 {
		adc_start(ADC);

		int front_left_inductor;
		front_left_inductor = ADC->ADC_CDR[4];
		int front_right_inductor;
		front_right_inductor = ADC->ADC_CDR[3];
			
		xSemaphoreTake(semaphore_adc_values,portMAX_DELAY); // Take semaphore
		adc_value_front_left = front_left_inductor;
		adc_value_front_right = front_right_inductor;
		xSemaphoreGive(semaphore_adc_values); // Take semaphore
		
		controll_front(front_left_inductor,front_right_inductor);
		
 		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
 	}
}

/* Function responsible of controlling the front fans*/
void controll_front(int left, int right){
	
	invalue = left-right;
	
	
	/* Calculate which fan to control in order to move the hoovercraft correctly */
	if(left<right)
	{
		activeFan = leftFan;
	}
	else
	{
		activeFan = rightFan;
	}
	
		
	/* Make room for the new values */
		if(invalue!=0)
		{
			
			/* Moving average filter */
			for(int i = buffert_size-1; i > 0;i--)
			{
				current_buffert_front[i] = current_buffert_front[i-1];
			}

			current_buffert_front[0] = invalue;
			
			int sum_current_median = 0;
			/* Calculate median value */
			for(int i = 0; i < buffert_size;i++)
			{
				sum_current_median +=current_buffert_front[i];
			}
			
			/* Make sure no other process uses the values */
			
			/* Retrieve the PID-variables */
			int temp_target_value = 0;
			double temp_KP;
			temp_KP = KP;
			double temp_TI;
			temp_TI = TI;
			double temp_TD;
			temp_TD = TD;
			
			
			current_value = sum_current_median/buffert_size;
			
			if (current_value<0)
				current_value=current_value*-1;
				
			e = (current_value);
			
			/* I-part */
			sum_front = sum_front + e;
			PI = (double) ((CONTROLLER_SCHEDULE_TIME/((double)1000*temp_TI))*sum_front);
			
			/* D-part */
			/* Calculate derivate */
			d_buffert_front[1] = d_buffert_front[0];
			d_buffert_front[0] = e;
			int d_diff;
			d_diff = d_buffert_front[0]-d_buffert_front[1];
			PD = (temp_TD*d_diff)/((double)CONTROLLER_SCHEDULE_TIME/1000);
			
			/* Only P -control */
			PI = 0;
			PD = 0;
			
			/* Regler-part */
			u = temp_KP*(e + PI + PD);

		
			update_fan_cycle((int)u,activeFan);
			
		}
}

/* Update the duty cycles for the fans. */
void update_fan_cycle(int duty_cycle, int active_Fan){
	
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle>999)
	{
		duty_cycle = 999;
	}
	if(duty_cycle<0)
	{
		duty_cycle = 0;
	}
	if(active_Fan==rightFan)
	{
		update_duty_cycle_36(duty_cycle);
		update_duty_cycle_DAC1(standby_cycle);
	}
	else
	{
		update_duty_cycle_36(standby_cycle);
		update_duty_cycle_DAC1(duty_cycle);
	}
	
	
}