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
	delay_init();
	
	init_adc();
	
	UnityBegin("test/test_adc.c"); // Begin unity on the test protocol for test_math, run setUp() in test_math.c
	
	RUN_TEST(test_adc_12bit,20); // Run test if adc is 12bit resolution.
	RUN_TEST(test_channel_3_enabled,20); // Test i channel 3 is enabled
	RUN_TEST(test_adc_pin_enabled,20); // Test if analog pin is enabled
	RUN_TEST(test_adc_pin_input,20); // Test if analpog pin is set as input
	RUN_TEST(test_adc_pin_pullup,20); // Test if analpog pin is set as input
	
	UnityEnd(); // End test protocol, print information
	
	int a;
	int b;
	int c;
	int d;
	int i;
	
	for(;;)
	{	
		i = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		while(i<10) // Average filter 
		{
		int temp = ADC->ADC_CDR[3];//adc_get_latest_value(ADC);
			adc_start(ADC);
		int temp2 = ADC->ADC_CDR[4];	
		int temp3 = ADC->ADC_CDR[5];
		int temp4 = ADC->ADC_CDR[6];	
			if(temp!=0)
			{
				a += temp;
				b += temp2;
				c += temp3;
				d += temp4;
				i++;
			}
	}
	a = a/10;
	b = b/10;
	c = c/10;
	d = d/10;
		printf("#A4 %d\n\r",a);
		printf("#A3 %d\n\r",b);
		printf("#A2 %d\n\r",c);
		printf("#A1 %d\n\r",d);
		delay_ms(1000);
	}
	return 0;
}