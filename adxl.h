/*
 * adxl.h
 *
 * Created: 2020/01/15 15:03:52
 *  Author: HAL
*/
typedef struct						/*加速度センサデータ*/
{
	double x_data;
	double y_data;
	double z_data;
}ACC_DATA;

ACC_DATA acc_rec(ACC_DATA);
void ADXL_inti(void);