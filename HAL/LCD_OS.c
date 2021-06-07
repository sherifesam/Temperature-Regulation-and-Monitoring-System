/*
 * LCD_OS.c
 *
 *  Created on: Feb 28, 2019
 *      Author: elProf
 */
#include "../STD_Types.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../MCAL/DIO.h"
#include "LCD_OS_Cfg.h"
#include "LCD_OS.h"


#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_FunctionSet4bit 0x28 
#define lcd_SetCursor       0x80          // set cursor position
#define lcd_ShiftRight		0b00011100	//Shift display right without changing DDRAM content
#define lcd_ShiftLeft		0b00011000	//Shift display left without changing DDRAM content

/*States*/
#define STATE_INIT_0	((u8)0)
#define STATE_INIT_1	((u8)1)
#define STATE_INIT_2	((u8)2)
#define STATE_INIT_3	((u8)3)
#define STATE_INIT_4	((u8)4)
#define STATE_0			((u8)5)
#define STATE_1			((u8)6)

#define ON_GOING		((u8)0)
#define DONE			((u8)1)

#define E_OK ((u8)0)
#define E_NOK ((u8)1)

static u8 u8Data , bWriteRequest, bInitilized ;
static u8 state;

extern void LCD_OS_vidInit(void)
{
	/*Init DIO Ports*/
	

	DIO_vidSetPinDir(DATA_PORT,4,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,5,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,6,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,7,OUTPUT);
	

	DIO_vidSetPinDir(RS_PORT,RS_PIN,OUTPUT);
	DIO_vidSetPinDir(RW_PORT,RW_PIN,OUTPUT);
	DIO_vidSetPinDir(ENABLE_PORT,ENABLE_PIN,OUTPUT);
	DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);
	state = STATE_INIT_0;
	bWriteRequest = 0 ;
	bInitilized = 0 ;
}

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition*/
void LCD_OS_Task(void* pvoid)
{
	u8 LCD_OS_retVal ;
	u8 LCD_OS_w_retVal;

	while(1)
	{
		switch(state)
		{
			
			case STATE_INIT_0:
			{
				/* Function Set  */
			    LCD_OS_retVal = LOC_vidSendCommand((u8)lcd_Home);
				if(LCD_OS_retVal == DONE)
				{
				    state = STATE_INIT_1 ;
				}
			}break;
			
			case STATE_INIT_1:
			{
				/* Function Set  */
			    LCD_OS_retVal = LOC_vidSendCommand((u8)lcd_FunctionSet4bit);
				if(LCD_OS_retVal == DONE)
				{
				    state = STATE_INIT_2;
				}
			}break;

			case STATE_INIT_2:
			{
				/* Display ON OFF Control */
			    LCD_OS_retVal = LOC_vidSendCommand((u8)lcd_DisplayOn);
				if(LCD_OS_retVal == DONE)
				{
				    state = STATE_INIT_3;
				}
			}break;

			case STATE_INIT_3:
			{
				/* Clear Display */
			    LCD_OS_retVal = LOC_vidSendCommand((u8)lcd_Clear);
				if(LCD_OS_retVal == DONE)
				{
				    state = STATE_INIT_4;
				}
			}break;

			case STATE_INIT_4:
			{
				/* Entry Mode Set  */
			    LCD_OS_retVal = LOC_vidSendCommand((u8)lcd_EntryMode);
				if(LCD_OS_retVal == DONE)
				{
				    state = STATE_0 ;
					bInitilized = (u8)1;
				}
			}break;

			case STATE_0 :
			{
				if(bWriteRequest == (u8)1)
				{
				    LCD_OS_w_retVal = (u8)LCD_OS_WriteChar_API();
					if(LCD_OS_w_retVal == DONE)
					{
					    state = STATE_0 ;
						bWriteRequest = (u8)0;
					}
				}

			}break;

			default:
			    break;
		}

		vTaskDelay(5);
	}
}

u8 LCD_OS_WriteChar_API(void)
{
	static u8 char_writing_state = (u8)0;
	static u8 char_writing_counter = (u8)0;
	u8 char_writing_retVal = ON_GOING;

	switch (char_writing_state)
	{
		case (u8)0:
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, (u8Data>>4));

			/* Set RS to HIG */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

			/* Set E to HIGH */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			char_writing_state = (u8)1;

		}break;
		
		
		case (u8)1:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			char_writing_state = (u8)2;
		}break;

		
		case (u8)2:
		{
			char_writing_counter++;
			if(char_writing_counter==(u8)2)
			{
				/*10ms elapsed*/
				char_writing_counter = (u8)0;
				char_writing_state = (u8)3;
			}
		}break;
		
		case (u8)3:
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8Data);

			
			/* Set RS to HIG */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

			/* Set E to HIGH */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			char_writing_state = (u8)4;

		}break;
		
		
		case (u8)4:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			char_writing_state = (u8)5;
		}break;

		
		case (u8)5:
		{
			char_writing_counter++;
			if(char_writing_counter==(u8)2)
			{
				/*10ms elapsed*/
				char_writing_counter = (u8)0;
				char_writing_state = (u8)0;
				char_writing_retVal = DONE;
			}
		}break;

		default:
		break;
	}


	return char_writing_retVal;
}

extern u8 LCD_OS_WriteChar(u8 ch)
{
	u8 writing_state = E_NOK;
	if((bInitilized == (u8)1)&&(bWriteRequest==(u8)0))
	{
		bWriteRequest = (u8)1;
		u8Data = ch;
		writing_state = E_OK;
	}
	else
	{
		writing_state = E_NOK;
	}
	return writing_state;
}


u8 LOC_vidSendCommand(u8 u8CmdCpy)
{
	static u8 send_state = (u8)0;
	static u8 send_counter = (u8)0;
	u8 send_retVal = (u8)ON_GOING;

	switch (send_state)
	{
		case (u8)0 :
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, (u8CmdCpy>>4));


			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);


			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
			send_state = (u8)1 ;

		}break;

		case (u8)1:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			send_state = (u8)2 ;
		}break;

		case (u8)2:
		{
			send_counter++;
			if(send_counter==(u8)2)
			{
				/*10ms elapsed*/
				send_counter = (u8)0;
				send_state = (u8)3;
			}
		}break;
		
		case (u8)3:
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8CmdCpy);


			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);


			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
			send_state = (u8)4;

		}break;

		case (u8)4:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			send_state = (u8)5;
		}break;

		case (u8)5:
		{
			send_counter++;
			if(send_counter==(u8)2)
			{
				/*10ms elapsed*/
				send_counter = (u8)0;
				send_state = (u8)0;
				send_retVal = DONE;
			}
		}break;
		default:
		break;
	}
	
	return send_retVal;
}

u8 is_wreq_available(void)
{
	u8 is_w_available = (u8)0;
	if(bWriteRequest == (u8)0)
	{
		is_w_available = (u8)1;
	}
	return is_w_available;
}

u8 getCursorCommand(u8 row, u8 col)
{
	u8 code;
	if(row == (u8)1)
	{
		code = ((u8)0x80 + col) - (u8)1;
	}
	else if(row == (u8)2)
	{
		code = ((u8)0xc0 + col) - (u8)1;
	}
	else
	{
		/* DO NOTHING */
	}
	return code;
}
