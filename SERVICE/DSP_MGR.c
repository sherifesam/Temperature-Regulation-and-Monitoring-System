
#include "DSP_MGR.h"


char normal[] =    {'N', 'O', 'R', 'M', 'A', 'L', ' ', ' ', ' ', '\0'};
char standby[] =   {'S', 'T', 'A', 'N', 'D', 'B', 'Y', ' ', ' ', '\0'};
char operation[] = {'O', 'P', 'E', 'R', 'A', 'T', 'I', 'O', 'N', '\0'};
char error[]     = {'E', 'R', 'R', 'O', 'R', ' ', ' ', ' ', ' ', '\0'};

char initial_temp[] = "SET:15    CRT:25";
char initial_state[] = "STATE:STANDBY";


char* modes[] = {normal, standby, operation, error, initial_state, initial_temp};



void DISP_WRITE_STATE(u8 mode_id, u8 row, u8 col, u8 *i)
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

void DISP_WRITE_TEMP(u8 set_temp, u8 crt_temp)
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
	// working on crt_temp...
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
