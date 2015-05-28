/*
 * reset_fan.c
 * 
 * Process used to reduce the maximum speed of the hoovercraft by cutting the power of the lifting fan
 * Created: 2015-05-25 20:05:48
 *  Author: P.Johansson77
 */ 

#include <asf.h>
#include "reset_fan.h"
#include "pwm_controller.h"
#include "values.h"
#include "controller_front.h"

void reset_fan(void *p)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	
	while (1)
	{
		/* Shut down and power up again if outside of the track */
		if ((distance_left_temp == 120 && distance_right_temp >= 10) || (distance_left_temp >= 10 && distance_right_temp == 120))
		{
			update_duty_cycle_9(0);
			delay_ms(3000);
			update_duty_cycle_9(900);
		}
		vTaskDelayUntil(&xLastWakeTime, 100);
	}
}