/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER2_MAIN_EXE        */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */

#define F_CPU 4000000UL
#include "STD_TYPES.h"
#include "macros.h"
//#include "DIO.h"
#include "TIMER2_int.h"
#include "TIMER2_config.h"
#include "TIMER2_priv.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile u8 tot_overflow;

// TIMER2 overflow interrupt service routine
// called whenever TCNT2 overflows
ISR(TIMER2_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
}


int main(void)
{
	u8 count_flag=0;
	tot_overflow=0;	
	// initialize timer
	TIMER2_voidInitialize();
		// connect led to pin PA0
	DDRA|=(1<<0);
	PORTA |= (1 << 0);    

	// loop forever
	while(1)
	{
			count_flag= Timer2_count_3Mins(tot_overflow);
			if(count_flag==1)
			{
					PORTA ^= ( 1 << 0);
			}
			else
			{
				/*Do Nothing*/
			}	
	}
}

