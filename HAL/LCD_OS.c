
/******************************************************************************
 *
 * File Name:   LCD_OS.c
 *
 * Description: A source file in the HAL layer of the project
 * 				which is responsible for the APIs of the LCD Module
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/


#include "../STD_Types.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../MCAL/DIO.h"
#include "LCD_OS_Cfg.h"
#include "LCD_OS.h"

static u8 u8Data , bWriteRequest, bInitilized ;
static u8 state;



/******************************************************************************
 *
 * Function Name: LCD_OS_vidInit
 *
 * Description: A function that is responsible for initializing the LCD
 *
 * Arguments:   void
 * Return:      void
 *
 *****************************************************************************/

extern void LCD_OS_vidInit(void)
{
	/*Init DIO Ports*/
	

	DIO_vidSetPinDir(DATA_PORT,PIN4,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,PIN5,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,PIN6,OUTPUT);
	DIO_vidSetPinDir(DATA_PORT,PIN7,OUTPUT);
	

	DIO_vidSetPinDir(RS_PORT,RS_PIN,OUTPUT);
	DIO_vidSetPinDir(RW_PORT,RW_PIN,OUTPUT);
	DIO_vidSetPinDir(ENABLE_PORT,ENABLE_PIN,OUTPUT);
	DIO_vidSetPinValue(RW_PORT, RW_PIN, LOW);
	state = STATE_INIT_0;
	bWriteRequest = (u8)0 ;
	bInitilized = (u8)0 ;
}


/******************************************************************************
 *
 * Function Name: LCD_OS_Task
 *
 * Description: A FreeRTOS task that's responsible for initialzing the LCD 
 * 				at first then waiting for any writing request to do it
 *
 * Arguments:   void* pvoid
 * Return:      void
 *
 *****************************************************************************/

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition*/
void LCD_OS_Task(void* pvoid)
{
	u8 LCD_OS_retVal ;

	/* for using TaskDelayUnitl() to make the task periodic */
	portTickType xLastWakeTime_LCD;
	xLastWakeTime_LCD = xTaskGetTickCount();
	
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
					while(LCD_OS_WriteChar_API() != DONE)
					{
						/* Do Nothing */
					}
					state = STATE_0 ;
					bWriteRequest = (u8)0;
				}

			}break;

			default:
			break;
		}

		vTaskDelayUntil( &xLastWakeTime_LCD , LCD_TASK_PERIODICTIY );
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}



/******************************************************************************
 *
 * Function Name: LCD_OS_WriteChar_API
 *
 * Description: A function that is responsible for writing characters on LCD
 *
 * Arguments:   void
 * Return:      u8
 *
 *****************************************************************************/

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
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8Data);

			
			/* Set RS to HIG */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, HIGH);

			/* Set E to HIGH */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);

			char_writing_state = (u8)3;

		}break;
		
		
		case (u8)3:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			char_writing_state = (u8)4;
		}break;

		
		case (u8)4:
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


/******************************************************************************
 *
 * Function Name: LCD_OS_WriteChar
 *
 * Description: A function that is responsible for giving the request to the
 * 				LCD_OS_TASK to start writing
 *
 * Arguments:   u8 ch
 * Return:      u8
 *
 *****************************************************************************/


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



/******************************************************************************
 *
 * Function Name: LCD_OS_WriteChar
 *
 * Description: A function that is responsible for sending a command to the LCD
 *
 * Arguments:   u8 ch
 * Return:      u8
 *
 *****************************************************************************/

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
			
			/* Load Command on Data bus */
			DIO_vidSetHighNibbleValue(DATA_PORT, u8CmdCpy);


			/* Set RS to LOW */
			DIO_vidSetPinValue(RS_PORT, RS_PIN, LOW);


			/* Set E to HIGH  */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, HIGH);
			send_state = (u8)3;

		}break;

		case (u8)3:
		{
			/* Set E to LOW */
			DIO_vidSetPinValue(ENABLE_PORT, ENABLE_PIN, LOW);
			send_state = (u8)4;
		}break;

		case (u8)4:
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


/******************************************************************************
 *
 * Function Name: is_wreq_available
 *
 * Description: A function that is responsible for checking if the writing request
 * 				is on or off
 *
 * Arguments:   void
 * Return:      u8
 *
 *****************************************************************************/

u8 is_wreq_available(void)
{
	u8 is_w_available = (u8)0;
	if(bWriteRequest == (u8)0)
	{
		is_w_available = (u8)1;
	}
	return is_w_available;
}


/******************************************************************************
 *
 * Function Name: is_wreq_available
 *
 * Description: A function that is responsible for calculating the hex data 
 * 				that should be sent to the LCD in order to move the cursor
 *
 * Arguments:   u8 row, u8 col
 * Return:      u8
 *
 *****************************************************************************/

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
