/* *********************************** */
/* Author     : Muhammed Ehab Adel     */
/* Describtion: TIMER2_CFG             */
/* Date       :Jun 3,2021              */
/* Version    : 1.0v                   */
/* *********************************** */

#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

/**    TIMER2_u8_NORMAL
	   TIMER2_u8_CTC
	   TIMER2_u8_FAST_PWM
	   TIMER2_u8_PHASE_CORRECT

 */
#define _TIMER2_u8_MODE_   TIMER2_u8_CTC

/*
 *
 *  TIMER2_u8_DIV_BY_1
	TIMER2_u8_DIV_BY_8
	TIMER2_u8_DIV_BY_32
	TIMER2_u8_DIV_BY_64
	TIMER2_u8_DIV_BY_128
	TIMER2_u8_DIV_BY_256
	TIMER2_u8_DIV_BY_1024
 */

#define TIMER2_u8_PRE_SCALAER  TIMER2_u8_DIV_BY_256


/*
 * TIMER2_u8_NO_ACTION
   TIMER2_u8_TOGGLE
   TIMER2_u8_SET
   TIMER2_u8_CLEAR
 */

#define TIMER2_COM_EVENT  TIMER2_u8_SET

#endif /* TIMER2_CONFIG_H_ */
