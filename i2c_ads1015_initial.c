/*
 * i2c_get_data.c
 *
 * Created: 2019/12/17 14:47:01
 *  Author: HAL
 */ 
#include "i2c_lib.h"
#include "ads1015.h"

/***************** ads1015 config *******************/
void ads1015_inital_config(char select)
{
	ads1015_channel=select;							/*select channel*/
	StartI2c(ADS1015_ADDS_WIRTE);
	TransI2c(ADS1015_CONFIG);
	TransI2c(ADS1015_CONFIG_HIGH);
	TransI2c(ADS1015_CONFIG_LOW);
	StopI2c();
}
/****************************************************/