/*
 * pwmInit.h
 *
 * Created: 2015-03-19 11:28:07
 *  Author: Jesper Hansen & Andr�e H��g
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
/* Output pin for PWM signal: Pin 9 */
#define PWM_PIO_PIN_9		PIO_PC21B_PWML4
/* Output pin for PWM signal: Pin 9 */
#define PWM_PIO_PIN_8		PIO_PC22B_PWML5
/* Fan positions */
#define FAN_FL 0
#define FAN_FR 1
#define FAN_BL 2
#define FAN_BR 3
#define FAN_LIFT 4
#define FAN_DRIVE 5

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
void update_duty_cycle_DAC1(uint32_t);
/* Set duty cycle of PWM signal on pin 36 */
void update_duty_cycle_36(uint32_t);
/* Set up duty cycle of PWM signal on pin 38 */
void update_duty_cycle_38(uint32_t);
/* Set up duty cycle of PWM signal on pin 40 */
void update_duty_cycle_40(uint32_t);
/* Set up duty cycle of PWM signal on pin 9 */
void update_duty_cycle_9(uint32_t);
/* Set up duty cycle of PWM signal on pin 8 */
void update_duty_cycle_8(uint32_t);

/* Duty_cycles */
int duty_cycle_DAC1;
int duty_cycle_36;
int duty_cycle_38;
int duty_cycle_40;
int duty_cycle_9;
int duty_cycle_8;