/*
 * ADC_priv.h
 *
 * Created: 6/2/2021 6:04:15 PM
 * Author : mostafa amr
 */ 
#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

typedef struct{
	volatile u8 ADCL;
	volatile u8 ADCH;
	volatile u8 ADCSRA;
	volatile u8 ADMUX;
}ADC;

/* M is Refer To MCal */

#define MADC ((volatile ADC *)0x24)

/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

#endif /* ADC_PRIV_H_ */
