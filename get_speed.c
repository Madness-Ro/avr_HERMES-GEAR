/*
 * Inital_speedget.c
 *
 * Created: 2019/12/04 14:12:21
 *  Author: HAL
 */ 
#include "get_speed.h"

/*　It is global variable for speed getting */
volatile unsigned long timer_counter=0;							/*161bit+32bit timercounter*/
volatile unsigned long timer_counter1=0;						/*16bit+32bit timercounter*/
volatile unsigned short timer_8counter=0;						/*8bitタイマーカウンタを16bit化する*/
/**************** INT0 **********************/
volatile unsigned long before_time=0;							/*before interrupt time*/
volatile unsigned long now_time=0;								/*now time*/
volatile unsigned long progress_time=0;							/*before - now time*/
volatile char int0_flg=0;
/**************** INT1 **********************/
volatile unsigned long before_time1=0;							/*before interrupt time*/
volatile unsigned long now_time1=0;								/*now time*/
volatile unsigned long progress_time1=0;						/*before - now time*/
volatile char int1_flg=0;
/*********************************************/
/************* speed buff ********************/
volatile char get_speed_buff=0;

ISR (INT0_vect)													/*External interrupt*/
{
	now_time=TCNT0 + (timer_8counter<<8);												/*get timer counter*/
	if(now_time>before_time)timer_counter=0;					/*initialize variable*/
	progress_time=now_time+(timer_counter<<16)-before_time;		/*calc progress time*/
	if(progress_time<100)										/*filter*/  /*経過時間が十分に小さいとき、無視をする　最高速時のパルスよりも短いときのように条件式を描く必要がある*/
	{
		int0_flg=0;												/*信頼できない値を捨てる　計算をしない*/
	}
	else
	{
		before_time=now_time;									/*信頼できる値の時before_timeを更新する*/
		int0_flg=1;
	//	timer_counter=0;	
	}
	
	
#ifdef DEBUG_SPEEDGET
	DDRC|=0x01;
	PORTC|=0x01;
#endif
}
ISR (INT1_vect)													/*External interrupt*/
{
	now_time1=TCNT0 + (timer_8counter<<8);
	if(now_time1>before_time1)timer_counter1=0;					/*initialize variable*/											/*get timer counter*/
	progress_time1=now_time1+(timer_counter1<<16)-before_time1;	/*calc progress time*/
	if(progress_time1<100)										/*filter*/  /*経過時間が十分に小さいとき、無視をする　最高速時のパルスよりも短いときのように条件式を描く必要がある*/
	{
		int1_flg=0;												/*信頼できない値を捨てる　計算をしない*/
	}
	else
	{
		before_time1=now_time1;									/*信頼できる値の時before_timeを更新する*/
	//	timer_counter=0;
		int1_flg=1;
	}
	
#ifdef DEBUG_SPEEDGET1
	DDRC|=0x02;
	PORTC|=0x02;
#endif
}
ISR (TIMER0_OVF_vect)											/*Timer interrupt*/
{
	if(timer_8counter!=0xFF)
	{
		timer_8counter++;
	}
	else
	{
		timer_8counter=0;
		timer_counter++;											/*Timer1 OVF counter*/
		timer_counter1=timer_counter;								/*Timer1 OVF counter*/
	}
}
void inital_speedget_timerinterrupt(void)
{
	/*port config*/
	DDRD&=0xF0;													/*all input*/
	PORTD|=0x00;												/*not all pull up*/
	
	/*timer config*/
	TCCR0A=0b00000000;											/*TOP 0xFF*/
	TCCR0B=(1<<CS02);											/*256 division  32us per clock*/
	TIMSK0=(1<<TOIE0);											/*OVF interrupt*/
	sei();
}
void inital_external_interrupt(void)
{
	sei();
	EICRA = (1<<ISC10)|(1<<ISC11)|(1<<ISC00)|(1<<ISC01);		/*INT0 PD2pin*/
	EIMSK = (1<<INT0)|(1<<INT1);								/*permit interrupt int0 int1*/
}
extern long get_speed_calc(long counter)
{							
	long speed; 
	speed=SPEED_CALC/(counter);									/*s_time(us) per rotaiton*/
	if(speed&0xFFFFFFFE)
	{	
		speed+=0x2;												/*繰り上げ*/
	}
	speed=speed>>1;				
	if(speed>=SPEEDLY_RESTRICTION)		
	{
		speed=get_speed_buff;
	}
	else
	{
		get_speed_buff=(char)speed;
	}				
	
	return speed;
}