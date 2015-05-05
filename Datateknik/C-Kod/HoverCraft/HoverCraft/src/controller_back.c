/*
 * serial_communication.c
 * 
 * File responsible of handling the sending of information
 *
 * Created: 2015-05-04 14:13:42
 *  Author: Linus Granath
 */ 
#include <asf.h>
#include "controller_back.h"

/* Start the communication task */
void start_controller_back(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
 	int i;
	i = 0;
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)
	 {
		adc_start(ADC);

		int back_left_inductor;
		back_left_inductor = ADC->ADC_CDR[2];
		int back_right_inductor;
		back_right_inductor = ADC->ADC_CDR[1];
		
 		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
 	}
}