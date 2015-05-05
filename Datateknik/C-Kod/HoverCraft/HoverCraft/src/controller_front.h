/*
 * controller_front.h
 *
 * Created: 2015-05-05 12:23:17
 *  Author: Linus Granath
 */ 


#ifndef CONTROLLER_FRONT_H_
#define CONTROLLER_FRONT_H_

void start_controller_front(void *);
void update_fan_cycle(int duty_cycle, int active_fan);
void controll_front(int,int);

#define CONTROLLER_SCHEDULE_TIME 500
#define KP 1
#define TI 1
#define TD 0.1
#endif /* CONTROLLER_FRONT_H_ */