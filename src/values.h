/*
 * values.h
 *
 * File holding constant values that are used by multiple files
 *
 * Created: 2015-05-05 12:30:50
 *  Author: Linus Granath
 */ 
#include <inttypes.h>

#ifndef VALUES_H_
#define VALUES_H_

#define VOLTAGE_TO_DISTANCE_AMMOUNT 3
#define buffert_size 5
#define buffert_size_iir 2
#define standby_cycle 300
#define standby_torque 570
#define leftFan 0
#define rightFan 1
#define standby 1
#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define BACK_LEFT 2
#define BACK_RIGHT 3
/* Different states, used to get step respone */
#define ROTATE_LEFT 0
#define ROTATE_RIGHT 1
#define ONLY_MIDDLE 2
#define GO_FORWARD 3
#define STAND_STILL 4

int adc_value_front_left;
extern int voltage_to_distance_table[VOLTAGE_TO_DISTANCE_AMMOUNT][4][25];
extern int adc_value_front_right;
int adc_value_back_left;
int adc_value_back_right;
extern int table;

extern int distance_left_temp;
extern int distance_right_temp;

int voltage_to_distance(int,int);
int filter(int,int);
int iir_filter(int,int);
int get_table(int);
#endif /* VALUES_H_ */