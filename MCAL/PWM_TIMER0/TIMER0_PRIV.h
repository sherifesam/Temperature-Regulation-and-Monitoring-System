/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER0_PRIVT	       */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */

#ifndef _TIMER0_PRIV
#define _TIMER0_PRIV

#define TIMSK	 (*(volatile u8 * )0x59)
#define OCR0 	 (*(volatile u8 * )0x5C)
#define TCCR0	 (*(volatile u8 * )0x53)
#define TCNT0	 (*(volatile u8 * )0x52)
#define TIFR	 (*(volatile u8 * )0x58)



#define COM00 4
#define COM01 5

#define CS00 0
#define CS02 2
#define WGM00 6
#define WGM01 3


#define TIMER0_NORMAL 		1
#define TIMER0_CTC 			2
#define TIMER0_FAST_PWM 	3
#define TIMER0_PHASE_PWM 	4

#define TIMER0_DIV_BY_1			1
#define TIMER0_DIV_BY_8			5
#define TIMER0_DIV_BY_64		8
#define TIMER0_DIV_BY_256		10
#define TIMER0_DIV_BY_1024		15


#define TIMER0_NO_ACTION	100
#define TIMER0_TOGGLE		12
#define TIMER0_SET			20
#define TIMER0_CLEAR		25


#endif