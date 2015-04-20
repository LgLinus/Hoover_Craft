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
extern void test_adc_pin_enabled(void);

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
	
	ioport_enable_pin(PIO_PA6_IDX);
	ioport_set_pin_dir(PIO_PA6_IDX,IOPORT_DIR_INPUT);
	
	init_adc();
	
	ioport_set_pin_mode(PIO_PA6_IDX,IOPORT_MODE_PULLUP);//  for adc
	UnityBegin("test/test_adc.c"); // Begin unity on the test protocol for test_math, run setUp() in test_math.c
	
	RUN_TEST(test_adc_12bit,20); // Run test if adc is 12bit resolution.
	RUN_TEST(test_channel_3_enabled,20);
	RUN_TEST(test_adc_pin_enabled,20);
	
	UnityEnd(); // End test protocol, print information
	
	int a;
	int i;
	
	for(;;)
	{	
		i = 0;
		a = 0;	
		while(i<10) // Average filter 
		{
			int temp = adc_get_latest_value(ADC);
			adc_start(ADC);
			
			if(temp!=0)
			{
				a += temp;
				i++;
			}
		}
		a = a/10;
		//printf("%d\n\r",a);
	}
	return 0;
}