/*
 * _7seg.c
 *
 * Created: 2019/07/25 22:01:38
 *  Author: HAL
 */
#include "seglib.h"
void segu_initial(void)
{
	DDRB |= 0b000111000;
}
void segu(unsigned char num)
 {
	char work;
	//if(num < 23)
	//{
		work = num / 10;
		segu_light(work);
		work = num % 10;
		segu_light(work);
	//}
 }
void segu_light(unsigned char num)
{
	short seg_data[10]={0b1111111100,0b01100000,0b11011010,0b11110010,0b01100110,
	0b10110110,0b10111110,0b11100100,0b11111110,0b11100110};
	char i;
	for(i=0;i<8;i++)
	{
		if(((seg_data[num]>>i) & 0x01) == 0)
		{
			PORTB = SER_OFF;
		}
		else
		{
			PORTB = SER_ON;
		}
		PORTB = SRCLK_OFF;
		PORTB = SRCLK_ON;
	}
	PORTB = RCLK_OFF;
	PORTB = RCLK_ON;
}
