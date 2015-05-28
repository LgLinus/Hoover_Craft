/*
 * pwmInit.c
 *
 * File responsible of initializing the PWM signals
 *
 * Created: 2015-03-19 11:27:54
 *  Author: Jesper Hansen & Andrée Höög
 */
#include "pwm_controller.h"
#include <asf.h>

static pwm_channel_t pwm_channel_DAC1;			// Instance to the PWM pin DAC1
static pwm_channel_t pwm_channel_36;			// Instance to the PWM pin 36
static pwm_channel_t pwm_channel_38;			// Instance to the PWM pin 38
static pwm_channel_t pwm_channel_40;			// Instance to the PWM pin 40
static pwm_channel_t pwm_channel_9;				// Instance to the PWM pin 9
static pwm_channel_t pwm_channel_8;				// Instance to the PWM pin 8

/* Duty_cycles for the different PWM signalds */
int duty_cycle_36 = 0;
int duty_cycle_38 = 0;
int duty_cycle_40 = 0;
int duty_cycle_9 = 0;
int duty_cycle_DAC1= 0;
int duty_cycle_8 = 0;

/* Function for initialize PWM on pins DAC1, 9, 36, 38 and 40 */
void initialize_pwm(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	pwm_channel_enable(PWM, PWM_CHANNEL_2);
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	pwm_channel_enable(PWM, PWM_CHANNEL_5);
	
	/* General clock settings for the PWM */
	pmc_enable_periph_clk(ID_PWM);
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PWM_RESOLUTION,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_main_hz()
	};
	pwm_init(PWM, &clock_setting);
	
	/* Disables the PWM channels for setup */
	pwm_channel_disable(PWM, PWM_CHANNEL_0);
	pwm_channel_disable(PWM, PWM_CHANNEL_1);
	pwm_channel_disable(PWM, PWM_CHANNEL_2);
	pwm_channel_disable(PWM, PWM_CHANNEL_3);
	pwm_channel_disable(PWM, PWM_CHANNEL_4);
	pwm_channel_disable(PWM, PWM_CHANNEL_5);
	
	/* DAC1 */
	pwm_channel_DAC1.alignment = PWM_ALIGN_LEFT;
	pwm_channel_DAC1.polarity = PWM_POLARITY;
	pwm_channel_DAC1.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_DAC1.ul_period = PWM_RESOLUTION;
	pwm_channel_DAC1.ul_duty = 0;
	pwm_channel_DAC1.channel = PWM_CHANNEL_0;
	pwm_channel_init(PWM, &pwm_channel_DAC1);
	pio_set_peripheral(PWM_PIO_B, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_DAC1);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	
	/* Pin 36 */
	pwm_channel_36.alignment = PWM_ALIGN_LEFT;
	pwm_channel_36.polarity = PWM_POLARITY;
	pwm_channel_36.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_36.ul_period = PWM_RESOLUTION;
	pwm_channel_36.ul_duty = 0;
	pwm_channel_36.channel = PWM_CHANNEL_1;
	pwm_channel_init(PWM, &pwm_channel_36);
	pio_set_peripheral(PWM_PIO_C, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_36);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_1);
	
	/* Pin 38 */
	pwm_channel_38.alignment = PWM_ALIGN_LEFT;
	pwm_channel_38.polarity = PWM_POLARITY;
	pwm_channel_38.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_38.ul_period = PWM_RESOLUTION;
	pwm_channel_38.ul_duty = 0;
	pwm_channel_38.channel = PWM_CHANNEL_2;
	pwm_channel_init(PWM, &pwm_channel_38);
	pio_set_peripheral(PWM_PIO_C, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_38);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_2);
	
	/* Pin 40 */
	pwm_channel_40.alignment = PWM_ALIGN_LEFT;
	pwm_channel_40.polarity = PWM_POLARITY;
	pwm_channel_40.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_40.ul_period = PWM_RESOLUTION;
	pwm_channel_40.ul_duty = 0;
	pwm_channel_40.channel = PWM_CHANNEL_3;
	pwm_channel_init(PWM, &pwm_channel_40);
	pio_set_peripheral(PWM_PIO_C, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_40);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_3);
	
	/* Pin 9 */
	pwm_channel_9.alignment = PWM_ALIGN_LEFT;
	pwm_channel_9.polarity = PWM_POLARITY;
	pwm_channel_9.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_9.ul_period = PWM_RESOLUTION;
	pwm_channel_9.ul_duty = 0;
	pwm_channel_9.channel = PWM_CHANNEL_4;
	pwm_channel_init(PWM, &pwm_channel_9);
	pio_set_peripheral(PWM_PIO_C, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_9);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	
	/* Pin 8 */
	pwm_channel_8.alignment = PWM_ALIGN_LEFT;
	pwm_channel_8.polarity = PWM_POLARITY;
	pwm_channel_8.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_8.ul_period = PWM_RESOLUTION;
	pwm_channel_8.ul_duty = 0;
	pwm_channel_8.channel = PWM_CHANNEL_5;
	pwm_channel_init(PWM, &pwm_channel_8);
	pio_set_peripheral(PWM_PIO_C, PWM_PIO_PERIPHERAL, PWM_PIO_PIN_8);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL_5);
}


/* Updates the dutycycle of the PWM signal on DAC1 */
void update_duty_cycle_DAC1(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_DAC1 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_DAC1, duty_cycle_temp);
}

/* Update the dutycycle of the PWM signal on pin 36 */
void update_duty_cycle_36(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_36 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_36, duty_cycle_temp);
}

/* Updates the dutycycle of the PMW signal on pin 38 */
void update_duty_cycle_38(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_38 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_38, duty_cycle_temp);
}

/* Updates the dutycycle of the PWM signal on pin 40 */
void update_duty_cycle_40(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_40 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_40, duty_cycle_temp);
}

/* Updates the dutycycle of the PWM signal on pin 9 */
void update_duty_cycle_9(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_9 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_9, duty_cycle_temp);
}

/* Updates the dutycycle of the PWM signal on pin 8 */
void update_duty_cycle_8(uint32_t duty_cycle_temp)
{
	/* Make sure the duty_cycle doesn't exceed or go below the possible range */
	if(duty_cycle_temp>999)
	{
		duty_cycle_temp = 999;
	}
	else if(duty_cycle_temp<0)
	{
		duty_cycle_temp = 0;
	}
	
	duty_cycle_8 = duty_cycle_temp;
	pwm_channel_update_duty(PWM, &pwm_channel_8, duty_cycle_temp);
}

