/*
 * LCD.c
 *
 * Created: 6/2/2021 4:36:45 PM
 *  Author: mostafa amr
 */ 
#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>

void LCD_vInit(void)
{
	_delay_ms(200);
	#if defined eight_bits_mode
	DIO_vidSetPinDir(LCD_DataPort,PIN0,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN1,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN2,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN3,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN4,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN5,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN6,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN7,OUTPUT);
	DIO_vidSetPinDir(LCD_EPort,LCD_EPin,OUTPUT);
	DIO_vidSetPinDir(LCD_RWPort,LCD_RWPin,OUTPUT);
	DIO_vidSetPinDir(LCD_RSPort,LCD_RSPin,OUTPUT);
	DIO_vidSetPinValue(LCD_RWPort,LCD_RWPin,LOW);
	LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1); 
	
	#elif defined four_bits_mode
	DIO_vidSetPinDir(LCD_DataPort,PIN4,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN5,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN6,OUTPUT);
	DIO_vidSetPinDir(LCD_DataPort,PIN7,OUTPUT);
	DIO_vidSetPinDir(LCD_EPort,LCD_EPin,OUTPUT);
	DIO_vidSetPinDir(LCD_RWPort,LCD_RWPin,OUTPUT);
	DIO_vidSetPinDir(LCD_RSPort,LCD_RSPin,OUTPUT);
   	DIO_vidSetPinValue(LCD_RWPort,LCD_RWPin,LOW);
	LCD_vSend_cmd(RETURN_HOME); //return home
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); //4bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1);
	#endif
}


static void send_falling_edge(void)
{
	DIO_vidSetPinValue(LCD_EPort,LCD_EPin,HIGH);
	_delay_ms(2);
	DIO_vidSetPinValue(LCD_EPort,LCD_EPin,LOW);
	_delay_ms(2);
}
void LCD_vSend_cmd(u8 cmd)
{
	#if defined eight_bits_mode
	DIO_vidSetPortValue(LCD_DataPort,cmd);
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,LOW);
	send_falling_edge();
	
	#elif defined four_bits_mode
	DIO_vidSetHighNibbleValue(LCD_DataPort,(cmd>>4));
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,LOW);
	send_falling_edge();
	DIO_vidSetHighNibbleValue(LCD_DataPort,cmd);
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,LOW);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void LCD_vSend_char(u8 data)
{
	#if defined eight_bits_mode
	DIO_vidSetPortValue(LCD_DataPort,data);
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,HIGH);
	send_falling_edge();
	
	#elif defined four_bits_mode
	DIO_vidSetHighNibbleValue(LCD_DataPort,(data>>4));
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,HIGH);
	send_falling_edge();
	DIO_vidSetHighNibbleValue(LCD_DataPort,data);
	DIO_vidSetPinValue(LCD_RSPort,LCD_RSPin,HIGH);
	send_falling_edge();
	#endif
	_delay_ms(1);
}


void LCD_vSend_string(u8 *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
}
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_movecursor(u8 row,u8 coloumn)
{
	char data = 0x80;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}
