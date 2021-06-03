#include "Keypad_Service.h"

u8 temp = 25;
static u8 num_of_digits = 0;
static u8 temp_i = 0;

void get_set_temp(void)
{
	u8 pressed_key = 0;
	
	if(num_of_digits < 2)
	{
		pressed_key = KEYPAD_u8GetPressedKey();
		if(pressed_key != 'A' && pressed_key != '=' && pressed_key != 0)
		{
			if(num_of_digits == 0)
			{
				temp_i += ((pressed_key - 48) * 10);
			}
			else if (num_of_digits == 1)
			{
					
				temp_i += (pressed_key-48);
			}
			num_of_digits += 1;
		}
	}
	if(num_of_digits == 2)
	{
		temp = temp_i;
		temp_i = 0;
		num_of_digits = 0;
			
	}
}
