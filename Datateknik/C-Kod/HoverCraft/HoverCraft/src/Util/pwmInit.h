/*
 * pwmInit.h
 *
 * Created: 2015-03-19 11:28:07
 *  Author: Jesper Hansen & Andrée Höög
 */ 


#ifndef PWMINIT_H_
#define PWMINIT_H_

/* Frequency of the PWM signal */
#define PWM_FREQUENCY		1000
/* Resolution: 1000 steps between 0-100% duty cycle */
#define PWM_RESOLUTION		999
/* PWM Channel */
#define PWM_CHANNEL			PWM_CHANNEL_0
/* Parallel Input/Output Controller for pin using PWM output*/
#define PWM_PIO				PIOB
/* Peripheral that is controlling the pin*/
#define PWM_PIO_PERIPHERAL	PIO_PERIPH_B
/* Output pin for PWM signal: DAC1 */
#define PWM_PIO_PIN			PIO_PB16B_PWML0
/* Low polarity of PWM signal.
 * Match low polarity with low output. The higher value for 
 * the duty cycle will result in a high signal. Otherwise the 
 * signal will be inverted. */
 #define PWM_POLARITY		PWM_LOW
 
 #define DUTYCYCLE 100
#endif /* PWMINIT_H_ */

/* Initialize PWM */
void initialize_pwm(void);
/* Set duty cycle of PWM signal */
void update_dutyCycle(uint32_t);