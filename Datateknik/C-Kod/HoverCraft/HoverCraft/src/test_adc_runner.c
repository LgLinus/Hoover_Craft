/**
 * 
 * File responsible of running the test protocol for math functions
 */


#include <asf.h>
#include "test/unity.h"
#include <setjmp.h>
#include "adc_functions.h"

/* Declare the test methods */
extern void test_adc_12bit(void);
extern void test_channel_3_enabled(void);
extern void test_channel_4_enabled(void);
extern void test_channel_5_enabled(void);
extern void test_channel_6_enabled(void);
extern void test_adc_pin_enabled(void);
extern void test_adc_pin_input(void);
extern void test_adc_pin_pullup(void);

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
	
	RUN_TEST(test_adc_12bit,20); // Run test if adc is 12bit resolution.
	
	/* Test if the channels 3-6 are activated */
	RUN_TEST(test_channel_3_enabled,20);
	RUN_TEST(test_channel_4_enabled,20);
	RUN_TEST(test_channel_5_enabled,20);
	RUN_TEST(test_channel_6_enabled,20);
	
	RUN_TEST(test_adc_pin_enabled,20); // Test if analog pin is enabled
	RUN_TEST(test_adc_pin_input,20); // Test if analpog pin is set as input
	RUN_TEST(test_adc_pin_pullup,20); // Test if analpog pin is set as input
	
	UnityEnd(); // End test protocol, print information
	
	int i;
	for(;;)
	{	
		adc_start(ADC);
		
		/* Retrieve input values from each channel */
		i = 0;
		/*while(i<10)
			i++;
		printf("#3 %d\n\r",ADC->ADC_CDR[3]);
		printf("#4 %d\n\r",ADC->ADC_CDR[4]);
		printf("#5 %d\n\r",ADC->ADC_CDR[5]);
		printf("#6 %d\n\r",ADC->ADC_CDR[6]);
	*/}
	return 0;
}