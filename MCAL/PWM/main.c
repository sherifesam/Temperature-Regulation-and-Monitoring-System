/*
 * PWM.c
 *
 * Created: 6/2/2021 6:15:54 PM
 * Author : owner
 */ 
#define F_CPU 4000000UL
#include "STD_TYPES.h"
#include "macros.h"
#include "DIO.h"
#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "TIMER0_PRIV.h"
#include <util/delay.h>

int main(void)
{
	DIO_vidSetPinDir(PORTB,3, OUTPUT);
	TIMER0_void_Init();
	TIMER0_void_SetTimerReg(0);  
	/* Replace with your application code */
    while (1) 
    {
		
		for( u16 duty=0; duty<=1023; duty++)
		{
			timer_wave_fastPWM(duty);
			_delay_ms(10);
		}	
		for( u16 duty=1023; duty>=0; duty--)
		{
			timer_wave_fastPWM(duty);
			_delay_ms(10);

		}
    }
}

