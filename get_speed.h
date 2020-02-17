/*
 * speedget.h
 *
 * Created: 2019/12/04 14:13:04
 *  Author: HAL
 */ 
/********************************************
if you use a library,you most include it. 

using timer OCR1A
*********************************************/
#ifndef SPEEDGET_H_
#define SPEEDGET_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/***************  DEBUG  ********************/
#define DEBUG_SPEEDGET										/*INT0*/
#define DEBUG_SPEEDGET1										/*INT1*/
/********************************************/

/*Å@It is global variable for speed getting */
/**************** INT0 **********************/
extern volatile unsigned long timer_counter;					/*8bit+32bit timercounter*/
extern volatile unsigned long before_time;						/*before interrupt time*/
extern volatile unsigned long now_time;							/*now time*/
extern volatile unsigned long progress_time;					/*before - now time*/
extern volatile char int0_flg;
/**************** INT1 **********************/
extern volatile unsigned long timer_counter1;					/*8it+32bit timercounter*/
extern volatile unsigned long before_time1;						/*before interrupt time*/
extern volatile unsigned long now_time1;						/*now time*/
extern volatile unsigned long progress_time1;					/*before - now time*/
extern volatile char int1_flg;
/*********************************************/

#define TIMER1_TIME_PER_CLOCK 32;							/*32us*/
#define PD2_INT0 progress_time								
#define PD3_INT1 progress_time1
#define	SPEEDLY_RESTRICTION	80								/*speedly Restriction 80km/h*/
/*********** 50mm*ÉŒ(3.14) = 157mm  **********/
#define MOTOER_SIZE 157
#define SPEED_CALC 11769									/*5884.5<<1*/

extern void inital_external_interrupt(void);				/*external interrupt*/
extern void inital_speedget_timerinterrupt(void);			/*timer interrupt*/
extern long get_speed_calc(long);							/*calc speed*/

#endif /* SPEEDGET_H_ */