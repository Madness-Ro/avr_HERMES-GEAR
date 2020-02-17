/*
 * pid_controller.c
 *
 * Created: 2020/01/27 14:24:50
 * Author : HAL
 */ 
#include "adxl.h"
#include "i2c_lib.h"
#include "ustart_lib.h"
#include "get_speed.h"
#include "ads1015.h"
#include "motor_con.h"

char start_flg = TRUE;

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;						//PD5
	
	sei();

	ACC_DATA xyz_data;
	long data;          //				value of a/d convert 
	int i;
	int speed=0;
	int speed2=0;
	
	
	motor_on();
	
	inital_speedget_timerinterrupt();
	inital_external_interrupt();
	
    while (1) 
    {
		data=i2c_get_controller();
	
		/*xyz_data=acc_rec(xyz_data);
		ustart(xyz_data.x_data,'x');
		for(i=0;i<10000;i++);
		ustart(xyz_data.y_data,'y');
		for(i=0;i<10000;i++);
		ustart(xyz_data.z_data,'z');
		for(i=0;i<10000;i++);*/
		if(int0_flg==1)
		{
			int0_flg=0;
			speed2=(int)get_speed_calc(PD2_INT0);
			if(speed2>0&&speed2<21)
			{
				speed=speed2;
			}
		//	ustart(speed,'0');
		}
		for(i=0;i<10000;i++);
		
		if(int1_flg==1)	
		{
			int1_flg=0;
			speed2=(int)get_speed_calc(PD3_INT1);
			if(speed>0&&speed2<21)
			{
				speed = speed2;
			}
		//	ustart(speed,'1');
		}
		
		motor_con(data, start_flg);
		
		//ustart(OCR1B, 'S');
	}
}

