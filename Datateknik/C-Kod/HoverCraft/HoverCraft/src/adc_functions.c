/*
 * adc.c
 
 * File initializing the adc
 *
 * Created: 2015-04-19 19:39:38
 *  Author: Linus
 */ 

/* Enable the adc */

#include <asf.h>

/* Initialize the A/D converter */
void init_adc(void){

	ioport_enable_pin(PIO_PA6_IDX); // Enable analog pin 4
	ioport_set_pin_dir(PIO_PA6_IDX,IOPORT_DIR_INPUT); // Set analog pin 4 as input
	
	// Enable analog pin 3
	ioport_enable_pin(PIO_PA22_IDX); // Enable analog pin 4
	ioport_set_pin_dir(PIO_PA22_IDX,IOPORT_DIR_INPUT); // Set analog pin 4 as input

	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_3);
	adc_enable_channel(ADC, ADC_CHANNEL_4);
	
	ioport_set_pin_mode(PIO_PA6_IDX,IOPORT_MODE_PULLUP);//  Set mode for analog in to pullup
}