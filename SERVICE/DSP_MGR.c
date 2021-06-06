
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
