/*
 * ADC.c
 *
 * Created: 6/2/2021 6:04:15 PM
 * Author : mostafa amr
 */ 
#include "STD_Types.h"
#include "macros.h"
#include "DIO.h"
#include "ADC_priv.h"
#include "ADC.h"

void ADC_init(){
	/*SET PINS DIR*/
	DIO_vidSetPinDir(PORTA, PIN0, INPUT);

	/*ADC ON*/
	set_bit(MADC->ADCSRA,ADEN);
	/*V reference*/
	set_bit(MADC->ADMUX,REFS0);

	/*READ ADCH ONLY*/
	set_bit(MADC->ADMUX,ADLAR);
}

u8 ADC_GetValue(){
	u8 high;
	/*start conversion*/
	set_bit(MADC->ADCSRA,ADSC);

	/*polling*/
	while(is_bit_clr(MADC->ADCSRA,ADIF));
	/* clear ADIF */
	set_bit(MADC->ADCSRA,ADIF);

	high = MADC->ADCH;
	return (high*5)/256;
}

