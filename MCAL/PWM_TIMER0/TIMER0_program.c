/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER0_PRGRM	       */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */

#include "STD_TYPES.h"
#include "macros.h"
#include "TIMER0_interface.h"
#include "TIMER0_PRIV.h"
#include "TIMER0_config.h"


void (*TIMER0_OV_CallBack) (void) ;
void (*TIMER0_CTC_CallBack) (void) ;


void TIMER0_void_Init(void)
{
	#if(TIMER0_MODE == TIMER0_NORMAL)
		clr_bit(TCCR0 , 6);
		clr_bit(TCCR0 , 3);
    
	#elif(TIMER0_MODE == TIMER0_CTC)
		clr_bit(TCCR0 , 6);
		set_bit(TCCR0 , 3);
		
	#elif(TIMER0_MODE == TIMER0_FAST_PWM )
		set_bit(TCCR0 , 6);
		set_bit(TCCR0 , 3);
	#elif(TIMER0_MODE == TIMER0_PHASE_PWM )
		set_bit(TCCR0 , 6);
		clr_bit(TCCR0 , 3);
		
	#endif
	
	#if(TIMER0_PRESCALER == TIMER0_DIV_BY_1)
		set_bit(TCCR0 , 0);
		clr_bit(TCCR0 , 1);
		clr_bit(TCCR0 , 2);
	
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_8)
		clr_bit(TCCR0 , 0);
		set_bit(TCCR0 , 1);
		clr_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_64 )
		set_bit(TCCR0 , 0);
		set_bit(TCCR0 , 1);
		clr_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_256 )
		clr_bit(TCCR0 , 0);
		clr_bit(TCCR0 , 1);
		set_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_1024 )
		set_bit(TCCR0 , 0);
		clr_bit(TCCR0 , 1);
		set_bit(TCCR0 , 2);
		
	#endif
	
	#if(TIMER0_COM_EVENT == TIMER0_NO_ACTION)
		clr_bit(TCCR0 , 4);
		clr_bit(TCCR0 , 5);
		
	#elif(TIMER0_COM_EVENT == TIMER0_TOGGLE)
		set_bit(TCCR0 , 4)
		clr_bit(TCCR0 , 5);
	#elif(TIMER0_COM_EVENT == TIMER0_CLEAR )
		clr_bit(TCCR0 , 4);
		set_bit(TCCR0 , 5);
	#elif(TIMER0_COM_EVENT == TIMER0_SET )
		set_bit(TCCR0 , 4);
		set_bit(TCCR0 , 5);
		
	#endif
	/*Disable Interrupts*/
    TIMER0_void_DisableOVInt();
    TIMER0_void_DisableCTCInt();
	/*CLEAR FLAGS*/
	set_bit(TIFR , 0);	
	set_bit(TIFR , 1);
	/*Clear register*/
    TIMER0_void_CLRTimerReg();
    TIMER0_void_CLRCompareVal()	;
}

void TIMER0_void_SetTimerReg(u8 Copy_uint8Val)
{
	TCNT0 = Copy_uint8Val ;
}


void TIMER0_void_CLRTimerReg(void)
{
	TCNT0 = 0 ;
}

void TIMER0_void_SetCompareVal(u8 Copy_uint8Val)
{
	OCR0 = Copy_uint8Val ;
}


void TIMER0_void_CLRCompareVal(void)
{
	OCR0 = 0 ;
}

void TIMER0_void_EnableOVInt(void)
{
	set_bit(TIMSK , 0);
}

void TIMER0_void_DisableOVInt(void)
{
	clr_bit(TIMSK , 0);
}


void TIMER0_void_EnableCTCInt(void)
{
	set_bit(TIMSK , 1);
}

void TIMER0_void_DisableCTCInt(void)
{
	clr_bit(TIMSK , 1);
}

void timer_CTC_init_interrupt(u8 u8_ocr_val)
{
	/* select CTC mode*/
	set_bit(TCCR0,WGM01);
	/* load a value in OCR0 */
    TIMER0_void_SetCompareVal(u8_ocr_val);
    /* enable interrupt*/
    TIMER0_void_EnableCTCInt();
}


void timer_wave_nonPWM(u8 u8_ocr_val)
{
	/* select CTC mode*/
	set_bit(TCCR0,WGM01);
	/* load a value in OCR0 */
    if(u8_ocr_val<41)
    {
        TIMER0_void_SetCompareVal(41);
    }
    else if(u8_ocr_val>100)
    {
        TIMER0_void_SetCompareVal(100);
    }
    else
    {
        TIMER0_void_SetCompareVal(u8_ocr_val);
    }
	/* toggle OC0 on compare match*/
	set_bit(TCCR0,COM00);
}

void timer_wave_fastPWM(u8 u8_duty_val)
{

	/* select fast PWM mode*/
	set_bit(TCCR0,WGM00);
	set_bit(TCCR0,WGM01);
	/* load a value in OCR0 */
    if(u8_duty_val<0)
    {
	    TIMER0_void_SetCompareVal(0);
    }
    else if(u8_duty_val>255)
    {
	    TIMER0_void_SetCompareVal(255);
    }
    else
    {
	    TIMER0_void_SetCompareVal(u8_duty_val);
    }

}


void timer_wave_phasecorrectPWM(u8 u8_duty_val)
{

	/* select phase correct PWM mode*/
	set_bit(TCCR0,WGM00);
	/* load a value in OCR0 */
    if(u8_duty_val<0)
    {
        TIMER0_void_SetCompareVal(0);
    }
    else if(u8_duty_val>255)
    {
        TIMER0_void_SetCompareVal(255);
    }
    else
    {
        TIMER0_void_SetCompareVal(u8_duty_val);
    }

}


void __vector_11(void) __attribute__((signal , used));
void __vector_11(void)
{
	
	TIMER0_OV_CallBack();
}

void __vector_10(void) __attribute__((signal , used));
void __vector_10(void)
{
	
	TIMER0_CTC_CallBack();
}