/******************************************************************************
 *
 * File Name:   TIMER0_program.c
 *
 * Description: A source file in the MCAL layer of the project
 * 				which is responsible for the APIs of the Timer Module
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/


#include "../STD_TYPES.h"
#include "../macros.h"
#include "DIO.h"

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
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 6);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 3);
	#elif(TIMER0_MODE == TIMER0_PHASE_PWM )
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 6);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 3);
	
	#endif
	
	#if(TIMER0_PRESCALER == TIMER0_DIV_BY_1)
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 1);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 2);
	
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_8)
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 1);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_64 )
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 1);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_256 )
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 1);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 2);
	#elif(TIMER0_PRESCALER == TIMER0_DIV_BY_1024 )
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 1);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 2);
	
	#endif
	
	#if(TIMER0_COM_EVENT == TIMER0_NO_ACTION)
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 4);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 5);
	

	#elif(TIMER0_COM_EVENT == TIMER0_TOGGLE)
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 4);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 5);
	#elif(TIMER0_COM_EVENT == TIMER0_CLEAR )
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TCCR0 , 4);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 5);
	#elif(TIMER0_COM_EVENT == TIMER0_SET )
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 4);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , 5);
	
	#endif
	/*Disable Interrupts*/
	TIMER0_void_DisableOVInt();
	TIMER0_void_DisableCTCInt();
	/*CLEAR FLAGS*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TIFR , 0);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TIFR , 1);
	/*Clear register*/
	TIMER0_void_CLRTimerReg();
	TIMER0_void_CLRCompareVal();
}

void TIMER0_void_SetTimerReg(u8 Copy_uint8Val)
{
	/* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
	TCNT0 = Copy_uint8Val;
}


void TIMER0_void_CLRTimerReg(void)
{
	/* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
	TCNT0 = (u8)0;
}

void TIMER0_void_SetCompareVal(u8 Copy_uint8Val)
{
	/* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
	OCR0 = Copy_uint8Val;
}

void TIMER0_void_CLRCompareVal(void)
{
	/* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
	OCR0 = (u8)0;
}

void TIMER0_void_EnableOVInt(void)
{
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TIMSK , 0);
}

void TIMER0_void_DisableOVInt(void)
{
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TIMSK , 0);
}


void TIMER0_void_EnableCTCInt(void)
{
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TIMSK , 1);
}

void TIMER0_void_DisableCTCInt(void)
{
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	clr_bit(TIMSK , 1);
}

void TIMER0_void_CTC(u8 u8_ocr_val)
{
	/* select CTC mode*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , WGM01);
	/* load a value in OCR0 */
	TIMER0_void_SetCompareVal(u8_ocr_val);
	/* enable interrupt*/
	TIMER0_void_EnableCTCInt();
}


void TIMER0_void_nonPWM(u8 u8_ocr_val)
{
	/* select CTC mode*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , WGM01);
	/* load a value in OCR0 */
	if(u8_ocr_val < ((u8)41))
	{
		TIMER0_void_SetCompareVal((u8)41);
	}
	else if(u8_ocr_val > ((u8)100))
	{
		TIMER0_void_SetCompareVal((u8)100);
	}
	else
	{
		TIMER0_void_SetCompareVal(u8_ocr_val);
	}
	/* toggle OC0 on compare match*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , COM00);
}

void TIMER0_void_fastPWM(u8 u8_duty_val)
{

	/* select fast PWM mode*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , WGM00);
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , WGM01);
	/* load a value in OCR0 */
	if(u8_duty_val > (u8)255)
	{
		TIMER0_void_SetCompareVal((u8)255);
	}
	else
	{
		TIMER0_void_SetCompareVal(u8_duty_val);
	}

}


void TIMER0_void_phasecorrectPWM(u8 u8_duty_val)
{

	/* select phase correct PWM mode*/
	/* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(12.7): bitwise operations inside registers would not result an error*/
	/* [MISRA VIOLATION] RULE(10.1): Standard Addresses */
	/* [MISRA VIOLATION] RULE(11.3) There is a dereferencing in the macro */
	set_bit(TCCR0 , WGM00);
	/* load a value in OCR0 */
	if(u8_duty_val > (u8)255)
	{
		TIMER0_void_SetCompareVal((u8)255);
	}
	else
	{
		TIMER0_void_SetCompareVal(u8_duty_val);
	}

}
