/*
 * i2c_get_voltage.c
 *
 * Created: 2019/12/17 15:31:51
 *  Author: HAL
 */ 
#include "ads1015.h"
#include "i2c_lib.h"
#include <avr/io.h>

short  i2c_get_AD_change(char sel)
{
	short val;									/*valtage*/
	
	ads1015_inital_config(sel);					/*channel=A0*/
	/************ i2c communication ************/
	StartI2c(ADS1015_ADDS_WIRTE);
	TransI2c(0x00);								/*data register0x00*/
	StopI2c();
	StartI2c(ADS1015_ADDS_READ);
	val=(RecieveAckI2c()<<8);
	val|=RecieveNakI2c();
	StopI2c();
	/*******************************************/
	return val;							/*mv*/
	//return val;
}
/************ calc ************/
/*4V val=20672				  */
/*val/16=					@*/
/*0V=0, 4.096V=1292			  */
/******************************/
short i2c_get_controller(void)					/*get voltage*/
{
	return i2c_get_AD_change(0);
}
short i2c_get_voltage(void)					/*get voltage*/
{
	return i2c_get_AD_change(3)/5.172;
}
short i2c_get_gyro_y(void)					/*y ƒÖ_get*/
{
	return i2c_get_AD_change(1);
}
short i2c_get_gyro_x(void)					/*x ƒÖ_get*/
{
	return i2c_get_AD_change(2);
}
