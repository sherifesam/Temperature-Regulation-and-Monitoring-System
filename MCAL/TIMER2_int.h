/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER2_INTFC           */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */
#ifndef TIMER2_INT_H_
#define TIMER2_INT_H_


/* global variable to count the number of overflows */


void TIMER2_voidInitialize(void);

void TIMER2_voidSetTimerReg(u8 Copy_u8value);

void TIMER2_voidResetTimerReg(void);

void TIMER2_voidDisableOvINT(void);

void TIMER2_voidEnableOvINT(void);

void TIMER2_voidDisableCTCINT(void);

void TIMER2_voidEnableCTCINT(void);

void TIMER2_voidSetOvCallBack(void(*Copy_ptr)(void));

void TIMER2_voidSetCTCCallBack(void(*Copy_ptr)(void));

void TIMER2_voidSetComparValue(u8 Copy_u8Value);

u8 TIMER2_u8GetREGvale(void);


u8 Timer2_count_3Mins(u8 overflow_tot);




#endif /* TIMER2_INT_H_ */
