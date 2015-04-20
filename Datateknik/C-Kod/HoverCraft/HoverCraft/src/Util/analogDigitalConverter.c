/*
 * analogDigitalConverter.c
 *
 * Created: 2015-03-19 00:36:46
 *  Author: Jesper Hansen & Andrée Höög
 */ 
#include "Util/analogDigitalConverter.h"
#include <adc.h>
#include "Util/asf.h"

/*********************************************
Function that set's up the A/D converter
**********************************************/
void adc_setup(void)
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_RESOLUTION);				// The A/D-converter resolution (1024)
	adc_enable_channel(ADC, ADC_CHANNEL);					// We are using Analog 8 for sampling on the Due
	adc_enable_interrupt(ADC, ADC_IER_DRDY);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}