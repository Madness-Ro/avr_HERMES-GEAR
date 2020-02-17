/*
 * motor_con.h
 *
 * Created: 2020/02/13 19:08:23
 *  Author: ths80761
 */ 


#ifndef MOTOR_CON_H_
#define MOTOR_CON_H_

#include <avr/io.h>
#include <avr/interrupt.h>


#define BRAKE	770
#define RUSH	850
#define TRUE	1
#define FALSE	0

extern char start_flg;

extern unsigned int count;
extern char start_time;
extern char wait_time;
extern long data;
extern long speed_gage;

extern void start_init(long data, char flg);		//start fixed sequence
extern void timer_count(void);
extern void timer_off(void);
extern void motor_on(void);
extern void motor_con(long data,char start_flg);

#endif /* MOTOR_CON_H_ */