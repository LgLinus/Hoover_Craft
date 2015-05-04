/*
 * main.c
 *
 * Class responsible of initializing and starting the task for the hoovercraft
 * Created: 2015-05-04 14:09:50
 *  Author: Linus Granath
 */ 

#include <asf.h>
#include "serial_communication.h"
void init_tasks(void);

/**
* Configure consol UART.
*/
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = { .baudrate =
	CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };
	/* Konfigurera konsol UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	/* Specifiera att stdout inte ska buffras */
	ioport_set_pin_mode(PIO_PA8_IDX,IOPORT_MODE_PULLUP);
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	
	#endif
}

int main(void)
{
	
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	
	init_tasks();
}

void init_tasks(void)
{
	if(xTaskCreate(start_communication,(const signed char * const) "Communication", 2048, NULL, 1, NULL) !=pdPASS)
	{
		printf("Could not create task Communication");
	}
	
	vTaskStartScheduler(); // Start the tasks
}