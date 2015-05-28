/*
 * main.c
 *
 * Class responsible of initializing and starting the task for the hoovercraft
 * Created: 2015-05-04 14:09:50
 *  Author: Linus Granath
 */ 

#include <asf.h>
#include "serial_communication.h"
#include "pwm_controller.h"
#include "semaphores.h"
#include "adc_functions.h"
#include "controller_front.h"
#include "controller_back.h"
#include "values.h"
#include "reset_fan.h"

//Unity
#include "test/unity.h"

void init_tasks(void);
void init_pwm(void);
void init_code_pins(void);
void init_sempahores(void);
void test_calibrate(void);
void set_state(int);
void test_voltage_to_distance(void);

extern void test_filter(void);
extern void test_calibration(void);
extern void test_voltage_converter(void);

xSemaphoreHandle semahpore_duty_cycles = 0;
xSemaphoreHandle semaphore_adc_values = 0;

/* Configure console UART.*/
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = { .baudrate =
	CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };// Configure console UART. 
	
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	
	ioport_set_pin_mode(PIO_PA8_IDX,IOPORT_MODE_PULLUP);// No stdout buffer
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	
	#endif
}

int main(void)
{
	/* Setup */
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	
	/* Initialize program */
	init_adc();
	init_pwm();
	init_sempahores();
	delay_init();
	
	set_state(STAND_STILL);
	set_state(ROTATE_LEFT);

	init_tasks();
}

/* Set different states so we can get the step response for different translations and rotations*/
void set_state(int state){
	
	/* Initialize the pwm signals with the given dutycycle (0-999) */
	switch(state){
		case ROTATE_LEFT:
			update_duty_cycle_36(999);
			update_duty_cycle_38(999);
			break;
		case ROTATE_RIGHT:
			update_duty_cycle_40(999);
			update_duty_cycle_DAC1(999);
			break;
		case GO_FORWARD:
			update_duty_cycle_8(999);
			break;
		case STAND_STILL:
			update_duty_cycle_36(standby_torque);
			update_duty_cycle_38(standby_torque);
			update_duty_cycle_40(standby_cycle);
			update_duty_cycle_DAC1(standby_cycle);
			delay_ms(5000);
			break;
	}
}


/* Initialize pwm */
void init_pwm(void)
{
	initialize_pwm();
	
	/* Initialize the pwm signals with the given dutycycle (0-999) */
	update_duty_cycle_9(900);
	update_duty_cycle_8(0);
	update_duty_cycle_DAC1(0);
	update_duty_cycle_36(0);
	update_duty_cycle_38(0);
	update_duty_cycle_40(0);

}

/* Initialize and create the tasks*/
void init_tasks(void)
{
	/* Create and start the reset fan task, used to slow down the maximum speed of the hoovercraft */
	//if(xTaskCreate(reset_fan,(const signed char * const) "Reset Fan", 2048, NULL, 3, NULL) !=pdPASS)
	//{
	//	printf("Could not create task Reset Fan");
	//}
	
	/* Create and start the front controller task */
 	if(xTaskCreate(start_controller_front,(const signed char * const) "Front controller", 2048, NULL, 2, NULL) !=pdPASS)
 	{
 		printf("Could not create task Front controller");
 	}
	
	/* Create and start the front controller task */
	if(xTaskCreate(start_controller_back,(const signed char * const) "Back controller", 2048, NULL, 2, NULL) !=pdPASS)
	{
		printf("Could not create task Back controller");
	}
	
	/* Create and start the communication task */
 	if(xTaskCreate(start_communication,(const signed char * const) "Communication", 2048, NULL, 1, NULL) !=pdPASS)
 	{
 		printf("Could not create task Communication");
 	}
	
	vTaskStartScheduler(); // Start the tasks
}



/* Initialize the semaphores */
void init_sempahores(void)
{
	vSemaphoreCreateBinary(semahpore_duty_cycles);
	vSemaphoreCreateBinary(semaphore_adc_values);
}

/* Test the calibration */
void test_calibrate(void){
	printf("START TEST\n");
	// Unity Test
	UnityBegin("test/test_calibrate.c");
	RUN_TEST(test_calibration, 12);
	UnityEnd();
}

/* Test the calibration */
void test_voltage_to_distance(void){
	// Unity Test
	UnityBegin("test/test_voltage_converter.c");
	RUN_TEST(test_voltage_converter, 12);
	RUN_TEST(test_filter, 12);
	UnityEnd();
}