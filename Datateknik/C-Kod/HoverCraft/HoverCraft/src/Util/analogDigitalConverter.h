/*
 * analogDigitalConverter.h
 *
 * Created: 2015-03-19 00:37:03
 *  Author: Jesper Hansen & Andrée Höög
 */ 


#ifndef ANALOGDIGITALCONVERTER_H_
#define ANALOGDIGITALCONVERTER_H_

/* The clock rate for the A/D-converter */
#define ADC_CLOCK		(sysclk_get_main_hz())
/* Channel for the A/D-converter */
#define ADC_CHANNEL		ADC_CHANNEL_10
/* A/D-resolution */
#define ADC_RESOLUTION	ADC_MR_LOWRES_BITS_12

void adc_setup(void);
#endif /* ANALOGDIGITALCONVERTER_H_ */