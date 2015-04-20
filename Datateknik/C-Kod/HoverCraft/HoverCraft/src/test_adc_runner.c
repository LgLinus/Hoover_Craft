/**
 * 
 * File responsible of running the test protocol for math functions
 */


#include <asf.h>
#include "test/unity.h"
#include <setjmp.h>
#include "adc_functions.h"

extern void test_adc_12bit(void);
extern void test_channel_3_enabled(void);

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
	init_adc();
	
	UnityBegin("test/test_adc.c"); // Begin unity on the test protocol for test_math, run setUp() in test_math.c
	RUN_TEST(test_adc_12bit,20);
	RUN_TEST(test_channel_3_enabled,20);
	UnityEnd(); // End test protocol, print information
	
	for(;;){
		
	}
	return 0;
}