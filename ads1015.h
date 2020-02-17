/*
 * ads1015.h
 *
 * Created: 2019/12/17 15:15:53
 *  Author: HAL
 */ 
/**********************************************************/
/*シリアル通信間隔が速すぎるとうまくデータを取得できないので注意*/
/**********************************************************/
#ifndef ADS1015_H_
#define ADS1015_H_
/******************** ads1015 define**********************/
#define ADS1015_ADDS 0x48
#define ADS1015_ADDS_READ (0x48<<1)|0x01					/*i2c read*/
#define ADS1015_ADDS_WIRTE (0x48<<1)						/*i2c write*/
#define ADS1015_CONFIG 0x01
#define ADS1015_CONVERSION 0x00								/*conversion register 16bit*/
#define ADS1015_CONFIG_HIGH (0xc1|(ads1015_channel<<4))		/*config 8~15bit*//*channel 0=A0 1=A1 2=A2 3=A3*//*0~6.144v*/
#define ADS1015_CONFIG_LOW (0xe3)							/*config 0~7bit*/

volatile char ads1015_channel;								/*select_channel 1=A0 2=A1 3=A2 4=A3*/
/********************************************************/
extern void ads1015_inital_config(char);
extern short i2c_get_voltage(void);							/*get voltage*/
extern short i2c_get_AD_change(char);
extern short i2c_get_gyro_y(void);
extern short i2c_get_gyro_x(void);
extern short i2c_get_controller(void);

#endif /* ADS1015_H_ */