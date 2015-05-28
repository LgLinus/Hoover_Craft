/*
 * controller_front.h
 *
 * Created: 2015-05-05 12:23:17
 *  Author: Linus Granath
 */ 


#ifndef CONTROLLER_FRONT_H_
#define CONTROLLER_FRONT_H_

void start_controller_front(void *);
void update_fan_cycle_front(int duty_cycle, int active_fan);
void controll_front(int,int);
void controll_front_dead_beat(int,int);
void controll_front_onoff(int,int);

#define CONTROLLER_SCHEDULE_TIME 50
#endif /* CONTROLLER_FRONT_H_ */