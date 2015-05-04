/*
 * serial_communication.c
 *
 * Created: 2015-05-04 14:13:42
 *  Author: ad2302
 */ 
#include <asf.h>
#include "serial_communication.h"

/* Start the communication task */
void start_communication(void *p)
{
	
 	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
 	int i;
	i = 0;
	 
 	while(1)
	 {
 		i++;
		printf("Send %d\n\r",i);
 		vTaskDelayUntil(&xLastWakeTime,COMMUNICATION_SAMPLE_TIME);
 	}
}