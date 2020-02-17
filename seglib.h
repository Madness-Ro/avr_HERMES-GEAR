/*
 * _7seglib.h
 *
 * Created: 2019/07/25 22:02:19
 *  Author: HAL
 */ 
#define SER_ON PORTB|0b00100000
#define SER_OFF PORTB& 0b11011111
#define RCLK_ON PORTB|0b00010000
#define RCLK_OFF PORTB& 0b11101111
#define SRCLK_ON PORTB|0b00001000
#define SRCLK_OFF PORTB& 0b11110111

#include <avr/io.h>
extern void segu_initial(void);
extern void segu(unsigned char);
extern void segu_light(unsigned char);