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

void init_tasks(void);
void init_pwm(void);
void init_sempahores(void);

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
	
	init_adc();
	init_pwm();
	init_sempahores();
	init_tasks();
	
}

/* Initialize the pwm signals */
void init_pwm(void)
{
	initialize_pwm();
	update_duty_cycle_DAC1(999);		// 999 is the highest duty cycle
	update_duty_cycle_36(600);
	update_duty_cycle_38(600);
	update_duty_cycle_40(500);
	update_duty_cycle_9(700);

}

void init_tasks(void)
{
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

void init_sempahores(void)
{
	vSemaphoreCreateBinary(semahpore_duty_cycles);
	vSemaphoreCreateBinary(semaphore_adc_values);
}