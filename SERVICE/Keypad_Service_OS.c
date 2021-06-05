#include "Keypad_Service_OS.h"

static u8 temp_set_OS = 25;
static u8 num_of_digits_OS = 0;
static u8 temp_i_OS = 0;


void Keypad_service_OS_Task(void *pvoid)
{
    u8 pressed_key = 0;
    while(1)
    {
        if(num_of_digits < 2)
    	{
            pressed_key = KEYPAD_u8GetPressedKey_OS();
            if(pressed_key != 'A' && pressed_key != '=' && pressed_key != 0)
            {
                if(num_of_digits_OS == 0)
                {
                    temp_i_OS += ((pressed_key - 48) * 10);
                }
                else if (num_of_digits_OS == 1)
                {
                        
                    temp_i_OS += (pressed_key-48);
                }
                num_of_digits_OS += 1;
            }
	    }
        if(num_of_digits_OS == 2)
        {
            temp_set_OS = temp_i_OS;
            temp_i_OS = 0;
            num_of_digits_OS = 0;
                
        }
        vTaskDelay(KEYPAD_SERVICE_PEROIDICTY);
    }
}

u8 get_set_temp_OS(void)
{
    return temp_set_OS;
}