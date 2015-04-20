/*
 * pwmInit.c
 *
 * Created: 2015-03-19 11:27:54
 *  Author: Jesper Hansen & Andrée Höög
 */
#include "Util/pwmInit.h"
#include <Util/asf.h>

static pwm_channel_t pwm_channel_instance;			// Instance to the PWM channel

/*
 * Initialize PWM
 */
void initialize_pwm(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM, PWM_CHANNEL);
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PWM_RESOLUTION,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_main_hz()
	};
	pwm_init(PWM, &clock_setting);
	pwm_channel_instance.alignment = PWM_ALIGN_LEFT;
	pwm_channel_instance.polarity = PWM_POLARITY;
	pwm_channel_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel_instance.ul_period = PWM_RESOLUTION;
	pwm_channel_instance.ul_duty = 0;
	pwm_channel_instance.channel = PWM_CHANNEL;
	pwm_channel_init(PWM, &pwm_channel_instance);
	/* Setup PWM for pin */
	pio_set_peripheral(PWM_PIO, PWM_PIO_PERIPHERAL, PWM_PIO_PIN);
	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_CHANNEL);
}

/* Updates the dutycycle of the PWM signal */
void update_dutyCycle(uint32_t dutyCycle)
{
	pwm_channel_update_duty(PWM, &pwm_channel_instance, dutyCycle);
}
