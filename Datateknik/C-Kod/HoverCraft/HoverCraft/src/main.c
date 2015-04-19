/**
 * 
 * File responsible of running the test protocol for math functions
 */


#include <asf.h>
#include "test/unity.h"
#include <setjmp.h>

extern void test_sum(void);
extern void test_product(void);
extern void test_diff(void);

/* Configure console UART. */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = { .baudrate =
	CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };
	
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID); // Configure console UART 
	stdio_serial_init(CONF_UART, &uart_serial_options);
	

	ioport_set_pin_mode(PIO_PA8_IDX,IOPORT_MODE_PULLUP); // Specify that sdout will not buffer 
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	
	#endif
}

int main(void)
{
	configure_console();
	board_init();
	sysclk_init();

	return 0;
}