/*
 * ADC.c
 *
 * Created: 6/4/2021 6:04:15 PM
 * Author : mostafa amr
 */ 
#include "STD_Types.h"
#include "macros.h"
#include "DIO.h"    
#include "ADC_priv.h"
#include "ADC_OS.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

static f32 ADC_value = 0;

void ADC_OS_init(void)
{
	/*SET PINS DIR*/
	DIO_vidSetPinDir(PORTA, PIN0, INPUT);

	/*ADC ON*/
	/* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
	set_bit(MADC->ADCSRA , ADEN);
	/*V reference*/
	/* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
	set_bit(MADC->ADMUX , REFS0);

	/*READ ADCH ONLY*/
	/* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
	set_bit(MADC->ADMUX , ADLAR);
}

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard declaration*/
void ADC_OS_Task(void* pvoid)
{
    u8 high = 0;
    u8 clr_flag = 0;
    while (1)
    {
        /*start conversion*/
        /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
        set_bit(MADC->ADCSRA , ADSC);

        /*polling*/
        while(clr_flag)
        {
           /* [MISRA VIOLATION] RULE(11.3 & 10.5 & 12.6): Unsolvable*/
           clr_flag = is_bit_clr(MADC->ADCSRA,ADIF);
        }
        /* clear ADIF */
        /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
        set_bit(MADC->ADCSRA,ADIF);

        /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
        high = MADC->ADCH;
        ADC_value = ((f32)high*(f32)5)/(f32)256;
       
        vTaskDelay((u32)500);
    }    
}

f32 ADC_OS_GetValue(void)
{
	return ADC_value;
}

