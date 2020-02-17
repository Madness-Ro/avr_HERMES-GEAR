/*
 * ADXL_i2c.c
 *
 * Created: 2019/11/03 22:27:40
 * Author : HAL
 */ 
#include "i2c_lib.h"
#include "ustart_lib.h"
#include "adxl.h"
#include <avr/io.h>
#define SLA 0x1d
#define SLA_W 0x3A
#define SLA_R 0x3B
#define START 0x08
#define SLA_ACK 0x18
#define SLA_R_ACK 0x40
#define DATA_ACK 0x28
#define RECEVE_NACK 0x88
#define RECEVE_ACK 0x80
#define RESTART 0x10

ACC_DATA acc_rec(ACC_DATA xyz_data)
{
	char x_data_low,x_data_high;
	char y_data_low,y_data_high;
	char z_data_low=0,z_data_high=0;
    /* Replace with your application code */
	
	StartI2c(SLA_W);						/*��������*/
	TransI2c(0x31);							/*�t�H�[�}�b�g������*/
	TransI2c(0x08);
	StopI2c();								/*�X�g�b�v*/
	
	StartI2c(SLA_W);						/*��������*/
	TransI2c(0x32);							/*�����xx���W�X�^�w��*/
	StopI2c();
	StartI2c(SLA_R);						/*�ăX�^�[�g�ǂݍ���*/
		
	x_data_low=RecieveAckI2c();				/*����8bit*/
	x_data_high=RecieveAckI2c();			/*���8bit*/
		
	y_data_low=RecieveAckI2c();				/*����8bit*/
	y_data_high=RecieveAckI2c();			/*���8bit*/
	
	z_data_low=RecieveAckI2c();				/*����8bit*/
	z_data_high=RecieveNakI2c();			/*���8bit*/
	
	xyz_data.x_data=(((int)x_data_high) << 8)|x_data_low;
	xyz_data.y_data=(((int)y_data_high) << 8)|y_data_low;
	xyz_data.z_data=(((int)z_data_high) << 8)|z_data_low;
	return xyz_data;
}
void ADXL_inti(void)
{
	InitI2c();
	StartI2c(SLA_W);						/*��������*/
	TransI2c(0x2D);							/*����J�n�A�h���X*/
	TransI2c(0x08);							/*����J�n*/
	StopI2c();								/*�X�g�b�v*/
	
}
