/*
 * i2c_lib.h
 *
 * Created: 2019/11/03 22:29:33
 *  Author: HAL
 */ 
#ifndef I2C_LIB_H_
#define I2C_LIB_H_

#endif /* I2C_LIB_H_ */

/***********  i2c function****************/
void InitI2c(void);
unsigned char StartI2c(unsigned char dataStartI2c);
void StopI2c(void);
unsigned char TransI2c(unsigned char dataTransI2c);
unsigned char RecieveAckI2c(void);
unsigned char RecieveNakI2c(void);
/*****************************************/