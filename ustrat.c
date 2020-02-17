/*
 * ustrat.c
 *
 * Created: 2019/05/25 17:31:20
 *  Author: HAL
 */ 
#include "ustart_lib.h"

void ustart(int data,char cnt)
{	
	/*		define		*/
	UBRR0	=	25;					/*ボーレート　19200 (8MHz)*/
	
	UCSR0A	=	0b00000000;
	
	/**********************************************************/
	/* 0b10000000 reception	complete						  */
	/* 0b01000000 transmission complete						  */
	/* 0b00100000 ready to send								  */
	/**********************************************************/
	
	UCSR0B	=	0b00011000;			/*Transmission / reception permission*/
	UCSR0C	=	0b00000110;			/*send data 8bit*/
									/*none parity	*/
									/*stop 1bit		*/
	uchar	i=0;
	char str_data[40]={0,};
	
	sprintf(str_data,"%c:%d\n",cnt,data);
	while(!(str_data[i]==0))
	{								
		while( !(UCSR0A & 0b00100000) );
		UDR0=str_data[i];
		i++;
	}
}