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
#include "LCD_Cfg.h"
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

static void LOC_vidWriteChar_Step1(void);
static void LOC_vidWriteChar_Step2(void);


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

void LCD_OS_Task(void* pvoid)
{
	u8 retVal ;
	u8 w_retVal;

	while(1)
	{
		switch(state)
		{
			
			case STATE_INIT_0:
			{
				/* Function Set  */
				retVal = LOC_vidSendCommand(lcd_Home);
				if(retVal == DONE)
					state = STATE_INIT_1 ;
			}break;
			
			case STATE_INIT_1:
			{
				/* Function Set  */
				retVal = LOC_vidSendCommand(lcd_FunctionSet4bit);
				if(retVal == DONE)
					state = STATE_INIT_2 ;
			}break;

			case STATE_INIT_2:
			{
				/* Display ON OFF Control */
				retVal = LOC_vidSendCommand(lcd_DisplayOn);
				if(retVal == DONE)
					state = STATE_INIT_3 ;
			}break;

			case STATE_INIT_3:
			{
				/* Clear Display */
				retVal = LOC_vidSendCommand(lcd_Clear);
				if(retVal == DONE)
					state = STATE_INIT_4;
			}break;

			case STATE_INIT_4:
			{
				/* Entry Mode Set  */
				retVal = LOC_vidSendCommand(lcd_EntryMode);
				if(retVal == DONE)
				{
					state = STATE_0 ;
					bInitilized = 1;
				}
			}break;

			case STATE_0 :
			{
				if(bWriteRequest == 1)
				{
					w_retVal = LCD_OS_WriteChar_API();
					if(w_retVal == DONE)
					{
						state = STATE_0 ;
						bWriteRequest = 0 ;
					}
				}

			}break;

		}

		vTaskDelay(5);
	}
}


u8 LCD_OS_WriteChar_API(void)
{
	static u8 state = 0;
	static u8 counter = 0;
	u8 retVal = ON_GOING;

	switch (state)
	{
		case 0 :
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, (u8Data>>4));

			/* Set RS to HIG */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

			/* Set E to HIGH */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			state = 1 ;

		}break;
		
		
		case 1:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			state = 2;
		}break;

		
		case 2:
		{
			counter++;
			if(counter==2)
			{
				/*10ms elapsed*/
				counter = 0 ;
				state = 3;
			}
		}break;
	
		case 3:
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8Data);

			
			/* Set RS to HIG */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

			/* Set E to HIGH */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			state = 4;

		}break;
		
		
		case 4:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			state = 5;
		}break;

		
		case 5:
		{
			counter++;
			if(counter==2)
			{
				/*10ms elapsed*/
				counter = 0 ;
				state = 0 ;
				retVal = DONE;
			}
		}break;
	}


	return retVal;

}

extern u8 LCD_OS_WriteChar(u8 ch)
{
	if((bInitilized == 1)&&(bWriteRequest==0))
	{
		bWriteRequest = 1;
		u8Data = ch;
		return E_OK;
	}
	else
		return E_NOK;

}
static void LOC_vidWriteChar_Step1()
{
	/* Set RS to HIG */
	DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

	/* Set R/W to LOW */
	DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);

	/* Set E to HIGH */
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

	/* Load Command on Data bus */
	DIO_vidSetPortValue(DATA_PORT, u8Data);

	/* Set E to LOW */
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
}

static void LOC_vidWriteChar_Step2(void)
{
	/* Set E to HIGH */
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
}

u8 LOC_vidSendCommand(u8 u8CmdCpy)
{
	static u8 state = 0;
	static u8 counter = 0 ;
	u8 retVal = ON_GOING;

	switch (state)
	{
		case 0 :
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, (u8CmdCpy>>4));


			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);


			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
			state = 1 ;

		}break;

		case 1:
		{			
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			state = 2 ;
		}break;

		case 2:
		{
			counter++;
			if(counter==2)
			{
				/*10ms elapsed*/
				counter = 0 ;
				state = 3;
			}
		}break;
	
		case 3:
		{
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8CmdCpy);


			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);


			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
			state = 4;

		}break;

		case 4:
		{			
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			state = 5;
		}break;

		case 5:
		{
			counter++;
			if(counter==2)
			{
				/*10ms elapsed*/
				counter = 0 ;
				state = 0 ;
				retVal = DONE;
			}
		}break;
	
	}
	
	return retVal;
}


u8 is_wreq_available(void)
{
	return (bWriteRequest == 0);
}

u8 getCursorCommand(u8 row, u8 col)
{
	u8 code;
	if(row == 1)
	{
		code = 0x80 + col - 1;
	}
	else if(row == 2)
	{
		code = 0xc0 + col - 1;
	}
	return code;
}