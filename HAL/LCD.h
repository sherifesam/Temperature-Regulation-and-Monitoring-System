/*
 * LCD.h
 *
 * Created: 6/2/2021 4:36:45 PM
 *  Author: mostafa amr
 */ 

#ifndef LCD_H_
#define LCD_H_
#include "STD_Types.h"
#include "DIO.h"
#include "LCD_config.h"

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define CURSOR_OFF_DISPLAN_ON 0x0c
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06

#if defined four_bits_mode
#define FOUR_BITS 0x28

#elif defined eight_bits_mode
#define EIGHT_BITS 0x38
#endif

void LCD_vInit(void);
static void send_falling_edge(void);
void LCD_vSend_cmd(u8 cmd);
void LCD_vSend_char(u8 data);
void LCD_vSend_string(u8 *data);
void LCD_clearscreen();
void LCD_movecursor(u8 row,u8 coloumn);

#endif /* LCD_H_ */