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
	configure_console();
	board_init();
	sysclk_init();
	
	UnityBegin("test/test_math.c"); // Begin unity on the test protocol for test_math, run setUp() in test_math.c
	RUN_TEST(test_sum, 23); // Run the test_sum case. Lcoated on line 23
	RUN_TEST(test_diff, 35); // Run test_diff case.
	RUN_TEST(test_product,22);
	
	UnityEnd(); // End test protocol, print information
	printf("Test");
	return 0;
}