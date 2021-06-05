/*
 * LCD_OS.h
 *
 *  Created on: Mar 25, 2020
 *      Author: elProf
 */

#ifndef HAL_LCD_OS_H_
#define HAL_LCD_OS_H_

extern void LCD_OS_vidInit(void);

extern u8 LCD_OS_WriteChar(u8 ch);

void LCD_OS_Task(void* pvoid);

u8 LCD_OS_WriteChar_API(void);


#endif /* HAL_LCD_OS_H_ */
