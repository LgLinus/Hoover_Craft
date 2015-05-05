/*
 * controller_front.c
 *
 * Created: 2015-05-05 11:00:00
 *  Author: Linus Granath
 */ 
#include <asf.h>
#include "pwm_controller.h"
#include "test/unity.h"
#include "semaphores.h"


/* Start the communication task */
void start_communication(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount(); //Retrieve the startup tick timer
	
 	int i;
	i = 0;
	
	/* Simple infinite loop, printing text with a given delay */
 	while(1)
	 {
		 
		xSemaphoreTake(semahpore_duty_cycles,portMAX_DELAY); // Take semaphore


		xSemaphoreGive(semahpore_duty_cycles); // Give back the semaphore
		
 		vTaskDelayUntil(&xLastWakeTime,CONTROLLER_SCHEDULE_TIME);
 	}
}