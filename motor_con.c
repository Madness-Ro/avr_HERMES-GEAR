/*
 * motor_con.c
 *
 * Created: 2020/02/13 18:44:52
 *  Author: ths80761
 */ 

#include "motor_con.h"
#include "ustart_lib.h"
unsigned int count=0;
char start_time = 0;
char wait_time = 0;
long speed_gage = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														  //
//			モーターが発進した時start_initに入るためここで数値を固定するためにA/D変換の数値を切るべき	   //
//														  //
//														  //
//														  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void start_init(long data, char flg)		//start fixed sequence
{
	
	timer_count();
	
	speed_gage = data /3 +BRAKE;
	
	OCR1A = OCR1B = speed_gage;
	
	data = BRAKE;
	
	for(volatile long ready_time = 0 ; ready_time<1000 ; ready_time++);
	
	data = RUSH;
	
	for(volatile long ready_time2 = 0; ready_time2<1000 ; ready_time2++);
	
	if ((count%625) == 0)
	{
		data -= 100;
		data += 12.5;
		start_time++;
	}
	
	if (start_time == 7)start_flg = FALSE;
	
	timer_off();
}

ISR(TIMER2_OVF_vect)
{
	TCNT2 = 50;
	count++;
	if(count>625)
	{
		count=0;
	}
}

void timer_count(void)
{
	TCCR2B = _BV(CS21)|_BV(CS20);		// 1 / 64
	TIMSK2 = _BV(TOIE2);								// interrupt flag
}

void timer_off(void)
{
	TCCR2B = 0;
	TIMSK2 = 0;
}

void motor_on(void)
{
	TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(COM1B1); // Clear OCR1A, OCR1B on Compare match, set Fast PWM
	TCCR1B = _BV(WGM13)| _BV(WGM12)|_BV(CS11);		// Prescaler 8
	ICR1 = 2499; // ICR1 set to TOP
}

void motor_con(long data,char start_flg)
{
////////////////////////////////////////////////////////////	
	if((start_flg == TRUE) &&(845>= data))
	{
		start_init(data,start_flg);
	}
////////////////////////////////////////////////////////////  この間のA/D変換データを切る。	
	else
	{
		if(data <= BRAKE)
		{
			if (count == 625)wait_time++;
			if (wait_time == 4)start_flg = FALSE;　 //４秒間何も数値が更新されないとフラグを立つ。
		}
	}
	
	ustart(OCR1B, 'S');
	

}
/*input = PINC;
input &=0xF0;

ustart(count,'C');

if ((count%625) == 0)
{
	data += 12.5;
	
	ustart(data,'S');
}

if ((PIND & 0x10) == 1)
{
	swt_cnt = 0;
	swt_flg = 1;
	
	TCCR1A &= 0;
	TCCR1B &= 0;
}

else
{
	swt_cnt++;
	if(swt_cnt==10000)
	{
		if(swt_flg == 1)
		{
			swt_flg = 0;
			
			TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(COM1B1); // Clear OC1A on Compare match, set Fast PWM
			TCCR1B = _BV(WGM13)| _BV(WGM12)|_BV(CS11);		// Prescaler 8
			ICR1 = 2499; // ICR1 set to TOP
			
			if(start_flg == TRUE)
			{
				start_init(data);
				continue;
			}
			
			else
			{
				data += data;
				
				
			}
		}
		
		else i = 20000;
	}*/
