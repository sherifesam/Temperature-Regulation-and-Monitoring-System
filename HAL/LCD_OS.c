/*
 * LCD_OS.c
 *
 *  Created on: Feb 28, 2019
 *      Author: elProf
 */


#include "LCD_OS.h"

static void LOC_vidWriteChar_Step1(void);
static void LOC_vidWriteChar_Step2(void);
static u8 LOC_vidSendCommand(u8 u8CmdCpy);

static u8 u8Data , bWriteRequest, bInitilized ;
static u8 state;

extern void LCD_OS_vidInit(void)
{
	/*Init DIO Ports*/
	// DIO_vidSetPortDir(DATA_PORT,OUTPUT);
    DIO_vidSetPinDir(DATA_PORT,PIN4,OUTPUT);
    DIO_vidSetPinDir(DATA_PORT,PIN5,OUTPUT);
    DIO_vidSetPinDir(DATA_PORT,PIN6,OUTPUT);
    DIO_vidSetPinDir(DATA_PORT,PIN7,OUTPUT);

	DIO_vidSetPinDir(RS_PORT,RS_PIN,OUTPUT);
	DIO_vidSetPinDir(RW_PORT,RW_PIN,OUTPUT);
	DIO_vidSetPinDir(ENABLE_PORT,ENABLE_PIN,OUTPUT);

	state = STATE_INIT_0;
	bWriteRequest = 0 ;
	bInitilized = 0 ;
}

void LCD_OS_Task(void* pvoid)
{
	u8 retVal ;

	while(1)
	{
		switch(state)
		{
			case STATE_INIT_0:
			{
				/* Function Set  */
				retVal = LOC_vidSendCommand(lcd_FunctionSet4bit); //TODO: 4 BIT
				if(retVal == DONE)
					state = STATE_INIT_1 ;
			}break;

			case STATE_INIT_1:
			{
				/* Display ON OFF Control */
				retVal = LOC_vidSendCommand(lcd_DisplayOn); // TODO: CUROSR OFF
				if(retVal == DONE)
					state = STATE_INIT_2 ;
			}break;

			case STATE_INIT_2:
			{
				/* Clear Display */
				retVal = LOC_vidSendCommand(lcd_Clear);
				if(retVal == DONE)
					state = STATE_INIT_3 ;
			}break;

			case STATE_INIT_3:
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
					LOC_vidWriteChar_Step1();
					state = STATE_1 ;
				}

			}break;

			case STATE_1:
			{
				LOC_vidWriteChar_Step2();
				state = STATE_0 ;
				bWriteRequest = 0 ;
			}break;

		}

		vTaskDelay(5);
	}
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
	//DIO_vidSetPortValue(DATA_PORT, u8Data);
    DIO_vidSetHighNibbleValue(DATA_PORT, (u8Data>>4));

	/* Set E to LOW */
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);


    
}


static void LOC_vidWriteChar_Step2(void)
{
    DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);
    DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);
	/* Set E to HIGH */
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
    DIO_vidSetHighNibbleValue(DATA_PORT, u8Data);
	DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
}

// static void LOC_vidWriteChar_Step3(void)
// {
//     DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
// }

static u8 LOC_vidSendCommand(u8 u8CmdCpy)
{
	static u8 state = 0 , counter = 0 ;
	u8 retVal = ON_GOING;

	switch (state)
	{
		case 0 :
		{
			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);

			/* Set R/W to LOW */
			DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);

			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, (u8CmdCpy >> 4));

			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);

			state = 1 ;

		}break;

		case 1:
		{
			
            /* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);

			/* Set R/W to LOW */
			DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);

			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8CmdCpy);

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
				state = 0 ;
				retVal = DONE;
			}
		}break;
	}

	return retVal;
}


