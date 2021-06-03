/*
 * ADC.c
 *
 * Created: 6/2/2021 6:04:15 PM
 * Author : mostafa amr
 */
#include "STD_Types.h"
#include "macros.h"
#include "ADC_priv.h"

void ADC_vinit(void)
{
	/* configure VREF */
	set_bit(MADC->ADMUX,REFS0);
	/* enable ADC */
	set_bit(MADC->ADCSRA,ADEN);
	/* adjust ADC clock */
	set_bit(MADC->ADCSRA,ADPS2);
	set_bit(MADC->ADCSRA,ADPS1);
}
u16 ADC_u16Read(void)
{
	u16 read_val = 0;
	
	/* start conversion */
	set_bit(MADC->ADCSRA,ADSC);
	/* stay in your position till ADIF become 1 */
	while(is_bit_clr(MADC->ADCSRA,ADIF));
	/* clear ADIF */
	set_bit(MADC->ADCSRA,ADIF);
	/* read analog input */
	read_val=(MADC->ADCL);
	read_val|=((MADC->ADCH)<<8);
	return read_val ;
}