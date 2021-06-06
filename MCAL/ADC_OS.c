/*
 * ADC.c
 *
 * Created: 6/4/2021 6:04:15 PM
 * Author : mostafa amr
 */ 
#include "../STD_Types.h"
#include "../macros.h"
#include "DIO.h"    
#include "ADC_priv.h"
#include "ADC_OS.h"
#include "../FreeRTOS/FreeRTOS.h"

static f32 ADC_value = 0;

void ADC_OS_init(void)
{
	/*SET PINS DIR*/
	DIO_vidSetPinDir(PORTA, PIN0, INPUT);

	/*ADC ON*/
	set_bit(MADC->ADCSRA,ADEN);
	/*V reference*/
	set_bit(MADC->ADMUX,REFS0);

	/*READ ADCH ONLY*/
	set_bit(MADC->ADMUX,ADLAR);
}

void ADC_OS_Task(void* pvoid)
{
    u8 high;
    while (1)
    {
        /*start conversion*/
        set_bit(MADC->ADCSRA,ADSC);

        /*polling*/
        while(is_bit_clr(MADC->ADCSRA,ADIF));
        /* clear ADIF */
        set_bit(MADC->ADCSRA,ADIF);

        high = MADC->ADCH;
        ADC_value = (high*5)/256;
       
        vTaskDelay(500); 
    }    
}

f32 ADC_OS_GetValue(void)
{
	return ADC_value;
}

