#include "../STD_Types.h"
#include "../HAL/LCD_OS.h"
#include "../HAL/Keypad_OS.h"
#include "DSP_MGR.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"


char normal[] =    {'N', 'O', 'R', 'M', 'A', 'L', ' ', ' ', ' ', '\0'};
char standby[] =   {'S', 'T', 'A', 'N', 'D', 'B', 'Y', ' ', ' ', '\0'};
char operation[] = {'O', 'P', 'E', 'R', 'A', 'T', 'I', 'O', 'N', '\0'};
char error[]     = {'E', 'R', 'R', 'O', 'R', ' ', ' ', ' ', ' ', '\0'};
char welcome[]   = {' ', ' ',' ',' ',' ',' ',' ',' ',' ','W', 'E', 'L', 'C', 'O', 'M', 'E', '\0'};

char initial_temp[] = "SET:15    CRT:25";
char initial_state[] = "STATE:STANDBY";


char* modes[] = {normal, standby, operation, error, initial_state, initial_temp, welcome};

static u8 DISP_FIN_WRITING = 0;
void DISP_WRITE_STATE(u8 mode_id, u8 row, u8 col, u8 *i)
{
	u8 code = getCursorCommand(row, col+(*i));
	while(LOC_vidSendCommand(code) != (u8)1)
	{
		/* DO NOTHING */
	}
	char *mode = modes[mode_id];
	if(is_wreq_available())
	{
		/* [MISRA VIOLATION] RULE(17.4): It is more convenient to write it this way, and we are sure that we will not pass the possible limit*/
		u8 char_to_be_written = *(mode + (*i));
		if(char_to_be_written != (u8)'\0')
		{
			DISP_FIN_WRITING = (u8)0;
			LCD_OS_WriteChar(char_to_be_written);
			(*i) = (*i) + (u8)1;
		}
		else
		{
			(*i) = (u8)0;
			DISP_FIN_WRITING = (u8)1;
		}
	}
}

void DISP_WRITE_TEMP(u8 set_temp, u8 crt_temp)
{
	/* working on set_temp */
	u8 cursor_code = (u8)0;
	static u8 temp_turn = 0;
	u8 set_temp_ones = (u8)(set_temp % (u8)10);
	u8 set_temp_tens = (u8)(set_temp / (u8)10);
	static u8 index = (u8)0;
	u8 check_wreq = (u8)is_wreq_available();
	if((check_wreq == (u8)1) && (temp_turn == (u8)0))
	{
		if(index == (u8)0)
		{
			cursor_code = getCursorCommand((u8)1, (u8)5);
			while(LOC_vidSendCommand(cursor_code) != (u8)1)
			{
				/* DO NOTHING */
			}
			LCD_OS_WriteChar(set_temp_tens+(u8)48);
			index++;
		}
		else
		{
			cursor_code = getCursorCommand((u8)1, (u8)6);
			while(LOC_vidSendCommand(cursor_code) != (u8)1)
			{
				/* DO NOTHIBG */
			}
			LCD_OS_WriteChar(set_temp_ones+(u8)48);
			index = (u8)0;
			temp_turn++;
		}

	}
	/* working on crt_temp */
	u8 crt_temp_ones = (u8)(crt_temp % (u8)10);
	u8 crt_temp_tens = (u8)(crt_temp / (u8)10);
	static u8 index2 = (u8)0;
	check_wreq = (u8)is_wreq_available();
	if((check_wreq == (u8)1) && (temp_turn == (u8)1))
	{
		if(index2 == (u8)0)
		{
			cursor_code = getCursorCommand((u8)1, (u8)15);
			while(LOC_vidSendCommand(cursor_code) != (u8)1)
			{
				/* DO NOTHING */
			}
			LCD_OS_WriteChar(crt_temp_tens+(u8)48);
			index2++;
		}
		else
		{
			cursor_code = getCursorCommand((u8)1, (u8)16);
			while(LOC_vidSendCommand(cursor_code) != (u8)1)
			{
				/* DO NOTHING */
			}
			LCD_OS_WriteChar(crt_temp_ones+(u8)48);
			index2 = (u8)0;
			temp_turn = (u8)0;
		}
	}
}


/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition*/
void WELCOME_OS_TASK(void* pvoid)
{
	u8 WELCOME_STATE = 0;
	u8 WELCOME_IT = 0;
	u8 WELCOME_CTR = 0;

	while(1)
	{
		switch(WELCOME_STATE)
		{
			case (u8)0:
			{
				DISP_WRITE_STATE(WELCOME_ID, (u8)1, (u8)1, &WELCOME_IT);
				if((IS_WRITING_FINISHED() == (u8)1))
				{
					WELCOME_STATE++;
				}
			}
			break;


			case (u8)1:
			{
				while(LOC_vidSendCommand((u8)0x18) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)2:
			{
				while(LOC_vidSendCommand((u8)0x1c) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)3:
			{
				while(LOC_vidSendCommand((u8)0x18) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
				{
					while(LOC_vidSendCommand((u8)0x1c) != (u8)1)
					{
						/* DO NOTHING */
					}
					WELCOME_CTR++;
					if(WELCOME_CTR == (u8)9)
					{
						WELCOME_CTR = (u8)0;
						WELCOME_STATE++;
					}
				}
				break;
			}

			case (u8)4:
			{
				while(LOC_vidSendCommand((u8)0x1c) != (u8)1)
				{

				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)5:
			{
				while(LOC_vidSendCommand((u8)0x18) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case(u8)6:
			{
				while(LOC_vidSendCommand((u8)0x1c) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)7:
			{
				while(LOC_vidSendCommand((u8)0x18) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)9)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)8:
			{
				while(LOC_vidSendCommand((u8)0x1c) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)10)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)9:
			{
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)10)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)10:
			{
				while(LOC_vidSendCommand((u8)0x01) != (u8)1)
				{
					/* DO NOTHING */
				}
				WELCOME_STATE++;
			}
			break;
			default:
			break;
		}
		vTaskDelay(DSP_MGR_PEROIDICTY);
	}
}

u8 IS_WRITING_FINISHED(void)
{
	u8 cond = (u8)0;
	if(DISP_FIN_WRITING == (u8)1)
	{
		cond = (u8)1;
		DISP_FIN_WRITING = (u8)0;
	}
	return cond;
}
