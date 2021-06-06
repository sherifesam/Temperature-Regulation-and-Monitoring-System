/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER0_INTFC	       */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */
#ifndef _TIMER0_INT_H
#define _TIMER0_INT_H



void TIMER0_void_Init(void);

void TIMER0_void_SetTimerReg(u8 Copy_uint8Val);

void TIMER0_void_CLRTimerReg(void);

void TIMER0_void_SetCompareVal(u8 Copy_uint8Val);

void TIMER0_void_CLRCompareVal(void);

void TIMER0_void_EnableOVInt(void);

void TIMER0_void_DisableOVInt(void);

void TIMER0_void_EnableCTCInt(void);

void TIMER0_void_DisableCTCInt(void);

void TIMER0_void_SetOVCallBack(void (*Copy_ptr) (void) ) ;

void TIMER0_void_SetCTCCallBack(void (*Copy_ptr) (void) ) ;

void timer_CTC_init_interrupt(u8 u8_ocr_val);

void timer_wave_nonPWM(u8 u8_ocr_val);

void timer_wave_fastPWM(u8 u8_duty_val);

void timer_wave_phasecorrectPWM(u8 u8_duty_val);


#endif
