/*
 * adc_functions.c
 *
 * File initializing the adc on the board
 *
 * Created: 2015-04-19 19:39:38
 *  Author: Linus
 */ 


#include <asf.h>

/* Initialize the A/D converter */
void init_adc(void){

	pmc_enable_periph_clk(ID_ADC); // initialize A/D clock
	adc_init(ADC, sysclk_get_main_hz(), sysclk_get_main_hz()/2, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12); // Set the A/D resolution to 12 bit
	
	/* Enable the A/D channels */
	adc_enable_channel(ADC, ADC_CHANNEL_3);
	adc_enable_channel(ADC, ADC_CHANNEL_4);
	adc_enable_channel(ADC, ADC_CHANNEL_5);
	adc_enable_channel(ADC, ADC_CHANNEL_6);
	
}
