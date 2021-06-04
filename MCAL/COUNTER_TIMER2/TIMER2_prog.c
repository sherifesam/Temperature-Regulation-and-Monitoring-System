/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER2_PRGRM           */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */
#include "STD_TYPES.h"
#include "macros.h"
#include "TIMER2_int.h"
#include "TIMER2_priv.h"
#include "TIMER2_config.h"
#include <avr/interrupt.h>

u8 counting_tot_overflow=0;
u8 ThreeMins_flag=0;
u8 counter=0;
void (*TIMER2_voidOVCallBack)(void);
void (*TIMER2_voidCTCCallBack)(void);

void TIMER2_voidInitialize(void)
{
#if _TIMER2_u8_MODE_ ==  TIMER2_u8_NORMAL
	clr_bit(TCCR2,6);
	clr_bit(TCCR2,3);

#elif _TIMER2_u8_MODE_ ==  TIMER2_u8_CTC
	clr_bit(TCCR2,6);
	set_bit(TCCR2,3);

#elif _TIMER2_u8_MODE_ ==  TIMER2_u8_FAST_PWM
	set_bit(TCCR2,6);
	set_bit(TCCR2,3);

#elif _TIMER2_u8_MODE_ ==  TIMER2_u8_PHASE_CORRECT
	set_bit(TCCR2,6);
	clr_bit(TCCR2,3);

#endif


#if TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_1
	set_bit(TCCR2,0);
	clr_bit(TCCR2,1);
	clr_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_8
	clr_bit(TCCR2,0);
	set_bit(TCCR2,1);
	clr_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_32
	set_bit(TCCR2,0);
	set_bit(TCCR2,1);
	clr_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_64
	clr_bit(TCCR2,0);
	clr_bit(TCCR2,1);
	set_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_128
	set_bit(TCCR2,0);
	clr_bit(TCCR2,1);
	set_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_256
	clr_bit(TCCR2,0);
	set_bit(TCCR2,1);
	set_bit(TCCR2,2);

#elif TIMER2_u8_PRE_SCALAER == TIMER2_u8_DIV_BY_1024
	set_bit(TCCR2,0);
	set_bit(TCCR2,1);
	set_bit(TCCR2,2);

#endif

#if TIMER2_COM_EVENT == TIMER2_u8_NO_ACTION
	clr_bit(TCCR2,4);
	clr_bit(TCCR2,5);
#elif TIMER2_COM_EVENT == TIMER2_u8_TOGGLE
	set_bit(TCCR2,4);
	clr_bit(TCCR2,5);
#elif TIMER2_COM_EVENT == TIMER2_u8_SET
	clr_bit(TCCR2,4);
	set_bit(TCCR2,5);
#elif TIMER2_COM_EVENT == TIMER2_u8_CLEAR
	set_bit(TCCR2,4);
	set_bit(TCCR2,5);
#endif

	TIMER2_voidResetTimerReg();
	sei();
	TIMER2_voidEnableOvINT();
	// initialize overflow counter variable
	


	/* CLEAR FLAG  */
	set_bit(TIFR,6);
	set_bit(TIFR,7);

	OCR2=0;


}

void TIMER2_voidSetTimerReg(u8 Copy_u8value)
{
	TCNT2 = Copy_u8value;
}

void TIMER2_voidResetTimerReg(void)
{
	TCNT2 = 0;
}


void TIMER2_voidDisableOvINT(void)
{
	clr_bit(TIMSK,6);
}

void TIMER2_voidEnableOvINT(void)
{
	set_bit(TIMSK,6);
}

void TIMER2_voidDisableCTCINT(void)
{
	clr_bit(TIMSK,7);
}

void TIMER2_voidEnableCTCINT(void)
{
	set_bit(TIMSK,7);
}

void TIMER2_voidSetOvCallBack(void(*Copy_ptr)(void))
{
	TIMER2_voidOVCallBack=Copy_ptr;
}

void TIMER2_voidSetCTCCallBack(void(*Copy_ptr)(void))
{
	TIMER2_voidCTCCallBack=Copy_ptr;
}

void TIMER2_voidSetComparValue(u8 Copy_u8Value)
{
	OCR2=Copy_u8Value;
}

u8 TIMER2_u8GetREGvale(void)
{
	return TCNT2;
}


u8 Timer2_count_3Mins(u8 overflow_tot)
{
	if (overflow_tot == 255)  // NOTE: '>=' is used
	{
		TIMER2_voidResetTimerReg();
		counting_tot_overflow++;
		if (counting_tot_overflow==255)
			 {
				 counting_tot_overflow=0;
				 counter++;
				 if(counter==194)
				 {
					 ThreeMins_flag=1;
					 counter=0;
				 }
			 }
			 else{
				 ThreeMins_flag=0;
			 }
	}
	return ThreeMins_flag;
}