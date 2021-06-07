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
#include "SERVICE/DSP_MGR.h"
int it = 0;


char turn = 0;
u8 CURRENT_MODE = 0;

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
				DISP_WRITE_STATE(INITIAL_STATE_ID, 2, 1, &i); // SET:25   CRT:25
			}
			else if(turn == 1)
			{
				DISP_WRITE_STATE(INITIAL_TEMP_ID, 1, 1, &j);	// STATE:STANDBY
			}
			turn = (turn + 1)%2;
		}
		else
		{
			u8 set_temp1 = get_set_temp_OS();
				
			if(check_hash_key() == HASH_PRESSED)
			{
				if(CURRENT_MODE == 0)
				CURRENT_MODE = 1;
				else
				CURRENT_MODE = 0;
			}
			if (CURRENT_MODE == 1)
			{
				DISP_WRITE_STATE(OPERATION_ID, 2, 7, &j);
			}
			else if (CURRENT_MODE == 0)
			{
				DISP_WRITE_STATE(STANDBY_ID, 2, 7, &j);
			}
							
		}
		it++;
		vTaskDelay(200);
	}
}


/*

void APP_OS_TASK(void* pvoid)
{
	u8 enuPressedKey;
	u8 set_temp;
	u8 first_digit = 0;
	u8 second_digit = 0;
	u8 digit_flag = 0;
	while(1)
	{
		
		enuPressedKey = KEYPAD_u8GetPressedKey_OS();
		set_temp = get_set_temp_OS();

		if(enuPressedKey != 0x00 && set_temp != KD_ERROR)
		{
			
		}

		vTaskDelay(100);
	}
}
*/

int main(void)
{
	LCD_OS_vidInit();
	KEYPAD_OS_vidInit();
	xTaskCreate(KEYPAD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			2,NULL);

	xTaskCreate(APP_OS_TASK,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			1,NULL);

	xTaskCreate(LCD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
	 			1,NULL);
	
	
	xTaskCreate(Keypad_service_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
				1,NULL);

	vTaskStartScheduler();

return 1 ;

}
