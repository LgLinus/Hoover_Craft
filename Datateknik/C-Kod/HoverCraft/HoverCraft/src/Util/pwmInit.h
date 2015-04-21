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
/* Parallel Input/Output Controller B for pin using PWM output*/
#define PWM_PIO_B				PIOB
/* Parallel Input/Output Controller C for pin using PWM output*/
#define PWM_PIO_C				PIOC
/* Peripheral that is controlling the pin*/
#define PWM_PIO_PERIPHERAL	PIO_PERIPH_B
/* Output pin for PWM signal: DAC1 */
#define PWM_PIO_PIN_DAC1	PIO_PB16B_PWML0
/* Output pin for PWM signal: Pin 36 */
#define PWM_PIO_PIN_36		PIO_PC4B_PWML1
/* Output pin for PWM signal: Pin 38 */
#define PWM_PIO_PIN_38		PIO_PC6B_PWML2
/* Output pin for PWM signal: Pin 40 */
#define PWM_PIO_PIN_40		PIO_PC8B_PWML3
/* Output pin for PWM signal: Pin 40 */
#define PWM_PIO_PIN_9		PIO_PC21B_PWML4
/* Low polarity of PWM signal.
 * Match low polarity with low output. The higher value for 
 * the duty cycle will result in a high signal. Otherwise the 
 * signal will be inverted. */
 #define PWM_POLARITY		PWM_LOW
 
 #define DUTYCYCLE 100
#endif /* PWMINIT_H_ */

/* Initialize PWM on DAC1 */
void initialize_pwm_DAC1(void);
/* Initialize PWM on A8 */
void initialize_pwm_36(void);
/* Function for initialize PWM on pins DAC1, 9, 36, 38 and 40 */
void initialize_pwm(void);
/* Set duty cycle of PWM signal on DAC1 */
void update_dutyCycle_DAC1(uint32_t);
/* Set duty cycle of PWM signal on pin 36 */
void update_dutyCycle_36(uint32_t);
/* Set up duty cycle of PWM signal on pin 38 */
void update_dutyCycle_38(uint32_t);
/* Set up duty cycle of PWM signal on pin 40 */
void update_dutyCycle_40(uint32_t);
/* Set up duty cycle of PWM signal on pin 9 */
void update_dutyCycle_9(uint32_t);