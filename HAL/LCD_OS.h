/*
 * LCD_OS.h
 *
 *  Created on: Mar 25, 2020
 *      Author: elProf
 */

#ifndef HAL_LCD_OS_H_
#define HAL_LCD_OS_H_


#include "STD_Types.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "DIO.h"
#include "LCD_OS_cfg.h"

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_FunctionSet4bit 0x28          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position
#define lcd_ShiftRight		0b00011100	//Shift display right without changing DDRAM content
#define lcd_ShiftLeft		0b00011000	//Shift display left without changing DDRAM content


/*States*/
#define STATE_INIT_0	((u8)0)
#define STATE_INIT_1	((u8)1)
#define STATE_INIT_2	((u8)2)
#define STATE_INIT_3	((u8)3)
#define STATE_0			((u8)4)
#define STATE_1			((u8)5)

#define ON_GOING		((u8)0)
#define DONE			((u8)1)

#define E_OK ((u8)0)
#define E_NOK ((u8)1)

extern void LCD_OS_vidInit(void);

extern u8 LCD_OS_WriteChar(u8 ch);

void LCD_OS_Task(void* pvoid);


#endif /* HAL_LCD_OS_H_ */
