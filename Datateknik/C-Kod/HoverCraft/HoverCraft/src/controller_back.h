/*
 * controller_back.h
 *
 * Created: 2015-05-05 11:01:24
 *  Author: Linus Granath
 */ 


#ifndef CONTROLLER_BACK_H_
#define CONTROLLER_BACK_H_

void update_fan_cycle_back(int duty_cycle, int active_fan);
void controll_back(int,int);
void start_controller_back(void *);

#define CONTROLLER_SCHEDULE_TIME 500
#define KP 1
#define TI 1
#define TD 0.1
#endif /* CONTROLLER_FRONT_H_ */