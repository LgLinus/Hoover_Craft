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
	
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_3);
	
}