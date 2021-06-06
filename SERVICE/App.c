/*
 * App.c
 *
 *  Created on: Mar 28, 2020
 *      Author: elProf
 */

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/FreeRTOSConfig.h"
#include "FreeRTOS/task.h"
#include "STD_Types.h"
#include "HAL/LCD_OS.h"
#include "HAL/Keypad.h"
#include "HAL/Keypad_OS.h"
#include "SERVICE/Keypad_Service_OS.h"


#define NORMAL_ID   0
#define STANDBY_ID   1
#define OPERATION_ID 2
#define ERROR_ID     3
#define SET_ID     4
#define CRT_ID     5
#define STATE_ID     6


int it = 0;


char normal[] =    {'N', 'O', 'R', 'M', 'A', 'L', ' ', ' ', ' ', '\0'};
char standby[] =   "SET:15    CRT:25";
char state[] = "STATE:STANDBY";
char operation[] = {'O', 'P', 'E', 'R', 'A', 'T', 'I', 'O', 'N', '\0'};
char error[]     = {'E', 'R', 'R', 'O', 'R', ' ', ' ', ' ', ' ', '\0'}; 
char set_temp[] = {'1', '2', '\0'};
char crt_temp[] = {'3', '4', '\0'};	

char* modes[] = {normal, standby, operation, error, set_temp, crt_temp, state};

char turn = 0;

void WRITE_WORD(u8 mode_id, u8 row, u8 col, u8 *i)
{
	u8 code = getCursorCommand(row, col+(*i));
	while(LOC_vidSendCommand(code) != 1);
	char *mode = modes[mode_id];
	if(is_wreq_available())
	{
		u8 char_to_be_written = *(mode+(*i));
		if(char_to_be_written != '\0')
		{
			LCD_OS_WriteChar(char_to_be_written);
			(*i) = (*i) + 1;
		}
		else
		{
			(*i) = 0;
		}
	}
}

void WRITE_WORD_1(u8 mode_id, u8 row, u8 col)
{
	static int j = 0;
	u8 code = getCursorCommand(row, col+j);
	while(LOC_vidSendCommand(code) != 1);
	char *mode = modes[mode_id];
	if(is_wreq_available())
	{
		u8 char_to_be_written = *(mode+j);
		if(char_to_be_written != '\0')
		{
			LCD_OS_WriteChar(char_to_be_written);
			j++;
		}
		else
		{
			j = 0;
		}
	}
}

void WRITE_TEMP(u8 set_temp, u8 crt_temp)
{
	// working on set_temp...
	u8 code;
	static u8 temp_turn = 0;
	u8 set_temp_ones = set_temp % 10;
	u8 set_temp_tens = set_temp / 10;
	static u8 index = 0;
	if(is_wreq_available() && temp_turn == 0)
	{
		if(index == 0)
		{
			code = getCursorCommand(1, 5);
			while(LOC_vidSendCommand(code) != 1);
			LCD_OS_WriteChar(set_temp_tens+48);	
			index++;
		}
		else
		{
			code = getCursorCommand(1, 6);
			while(LOC_vidSendCommand(code) != 1);
			LCD_OS_WriteChar(set_temp_ones+48);
			index = 0;
			temp_turn++;
		}
		
	}
	u8 crt_temp_ones = crt_temp % 10;
	u8 crt_temp_tens = crt_temp / 10;
	static u8 index2 = 0;
	if(is_wreq_available() && temp_turn == 1)
	{
		if(index2 == 0)
		{
			code = getCursorCommand(1, 15);
			while(LOC_vidSendCommand(code) != 1);
			LCD_OS_WriteChar(crt_temp_tens+48);
			index2++;
		}
		else
		{
			code = getCursorCommand(1, 16);
			while(LOC_vidSendCommand(code) != 1);
			LCD_OS_WriteChar(crt_temp_ones+48);
			index2 = 0;
			temp_turn = 0;
		}
	}
}

void APP_OS_TASK(void* pvoid)
{
	u8 i = 0;
	u8 j = 0;
	while(1)
	{
		if(it < 50)
		{
			if(turn == 0)
			{
				WRITE_WORD(STANDBY_ID, 1, 1, &i); // SET:25   CRT:25
			}
			else if(turn == 1)
				WRITE_WORD(STATE_ID, 2, 1, &j);	// STATE:STANDBY
			turn = (turn + 1)%2;
		}
		else
		{
			u8 set_temp1 = get_set_temp_OS();
			if(set_temp1 != KD_ERROR)				
			WRITE_TEMP(set_temp1, 34);
		}
		
		it++;
		vTaskDelay(100);
	}
}


int main(void)
{
	LCD_OS_vidInit();
	KEYPAD_OS_vidInit();
	xTaskCreate(KEYPAD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			1,NULL);

	xTaskCreate(APP_OS_TASK,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			1,NULL);

	xTaskCreate(LCD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			1,NULL);
	
	
	xTaskCreate(Keypad_service_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
				1,NULL);

	vTaskStartScheduler();

return 1 ;

}
