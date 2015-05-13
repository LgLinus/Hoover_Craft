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

int sum = 0;
double u;
int e;
double PI;
double PD;
int invalue; // Difference between left, right
int activeFan; // Keep track on which fan to activate, 0 left, 1 right
int d_buffert[d_buffer] = {0};
int current_buffert[buffert_size] = {0};
int current_value;

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
		controll_back(back_left_inductor,back_right_inductor);
		
		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
	}

}

/* Function responsible of controlling the back fans*/
 void controll_back(int left, int right){

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
 			current_buffert[i] = current_buffert[i-1];
 		}
 
 		current_buffert[0] = invalue;
 		
 		int sum_current_median = 0;
 		/* Calculate median value */
 		for(int i = 0; i < buffert_size;i++)
 		{
 			sum_current_median +=current_buffert[i];
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
 		sum = sum + e;
 		PI = (double) ((CONTROLLER_SCHEDULE_TIME/((double)1000*temp_TI))*sum);
 		/* D-part */
 		/* Calculate derivate */
 		d_buffert[1] = d_buffert[0];
 		d_buffert[0] = e;
		int d_diff;
 		d_diff = d_buffert[0]-d_buffert[1];
 		PD = (temp_TD*d_diff)/((double)CONTROLLER_SCHEDULE_TIME/1000);
 		
 		/* Only P -control */
 		PI = 0;
 		PD = 0;
 			
 		/* Regler-part */
 		u = temp_KP*(e + PI + PD);
 
 		
 		update_fan_cycle_back((int)u,activeFan);
 		
 	}
 }
 
 /* Update the duty cycles for the fans. */
 void update_fan_cycle_back(int duty_cycle, int activeFan){
 	
 	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
 	if(duty_cycle>999)
 	{
 		duty_cycle = 999;
 	}
 	if(duty_cycle<0)
 	{
 		duty_cycle = 0;
 	}
	
	/* Activate the correct fan */
 	if(activeFan==rightFan)
 	{
 		update_duty_cycle_40(duty_cycle);
 		update_duty_cycle_38(standby_cycle);
 	}
 	else
 	{
 		update_duty_cycle_38(standby_cycle);
 		update_duty_cycle_40(duty_cycle);
 	}
 	
 }