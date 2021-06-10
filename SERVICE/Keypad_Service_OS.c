/******************************************************************************
 *
 * File Name:   Keypad_Service_OS.c
 *
 * Description: A source file in the Service layer of the project
 * 				which is responsible for the handling the input coming
 *              from the user and save it as a 2-digit temperature value
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/

#include "../STD_Types.h"
#include "../HAL/Keypad_OS.h"
#include "Keypad_Service_OS.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

/* Global variable to be returned to the APP layer */
static u8 temp_set_OS = 25;




/******************************************************************************
 *
 * Function Name: Keypad_service_OS_Task
 *
 * Description: A FreeRTOS task which is responsible for handling the input 
 *              from the user
 * 
 * 
 * Arguments: 	void *pvoid
 * Return:      void 
 *
 *****************************************************************************/

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition*/
void Keypad_service_OS_Task(void *pvoid)
{
    static u8 num_of_digits_OS = 0;
    static u8 temp_i_OS = 0;
    u8 pressed_key = 0;
	
	// for using TaskDelayUnitl() to make the task periodic
	portTickType xLastWakeTime_KEYPAD_Service;
	xLastWakeTime_KEYPAD_Service = xTaskGetTickCount();
	
    while(1)
    {
		if(num_of_digits_OS < (u8)2)
    	{
            pressed_key = KEYPAD_u8GetPressedKey_OS();
            /*ASCII TABLE: 65 is the decimal value of 'A' and 61 is the decimal value of '=' */
            if((pressed_key != (u8)65) && (pressed_key != (u8)61) && (pressed_key !=  (u8)0))
            {
                if(num_of_digits_OS == (u8)0)
                {
                    temp_i_OS += ((pressed_key - (u8)48) * (u8)10);
                }
                else if (num_of_digits_OS == (u8)1)
                {
                    temp_i_OS += (pressed_key - (u8)48);
                }
                else
                {
                    /* DO NOTHING */
                }
                num_of_digits_OS += (u8)1;
            }
			
	    }
        else if(num_of_digits_OS == (u8)2)
        {
            temp_set_OS = temp_i_OS;
            temp_i_OS = (u8)0;
			num_of_digits_OS = (u8)0;
                
        }
		vTaskDelayUntil( &xLastWakeTime_KEYPAD_Service , KEYPAD_SERVICE_PEROIDICTY );
    }
}


/******************************************************************************
 *
 * Function Name: Keypad_service_OS_Task
 *
 * Description: A Function that is responsible for returning the last input
 *              from the user
 * 
 * 
 * Arguments: 	void 
 * Return:      u8 
 *
 *****************************************************************************/
u8 get_set_temp_OS(void)
{
	return temp_set_OS;
}


/******************************************************************************
 *
 * Function Name: check_hash_key
 *
 * Description: A Function that is responsible for checking if the user has 
 *              pressed the hash key
 * 
 * 
 * Arguments: 	void 
 * Return:      u8 
 *
 *****************************************************************************/

u8 check_hash_key(void)
{
    /* 65 is the decimal value of 'A' */
    u8 hash_flag = (KEYPAD_u8GetPressedKey_OS() == (u8)65);
	return  (hash_flag);
}
