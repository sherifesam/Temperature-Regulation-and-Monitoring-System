#include "../STD_Types.h"
#include "../MCAL/DIO.h"
#include "Keypad_OS_cfg.h"
#include "Keypad_OS.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

static u8 Rows[] = {R1_PIN, R2_PIN, R3_PIN, R4_PIN};
static u8 Columns[] = {C1_PIN, C2_PIN, C3_PIN};

/* Global variable to be returned to the SERVICE layer */
static u8 u8PressedKey;

void KEYPAD_OS_vidInit(void)
{
	u8 KEYPAD_u8PinNo = 0;

	/* Initialize the rows */
	for(KEYPAD_u8PinNo = (u8)0; KEYPAD_u8PinNo < NO_OF_ROWS; ++KEYPAD_u8PinNo)
	{
		DIO_vidSetPinDir(R_PORT, Rows[KEYPAD_u8PinNo], INPUT);
		DIO_vidSetPinValue(R_PORT,Rows[KEYPAD_u8PinNo],HIGH);
	}

	/* Initialize the columns */
	for(KEYPAD_u8PinNo = (u8)0; KEYPAD_u8PinNo < NO_OF_COLS; ++KEYPAD_u8PinNo)
	{
		DIO_vidSetPinDir(C_PORT, Columns[KEYPAD_u8PinNo], OUTPUT);
		DIO_vidSetPinValue(C_PORT,Columns[KEYPAD_u8PinNo],HIGH);
	}
}

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition*/
void KEYPAD_OS_Task(void *pvoid)
{
	u8 u8ColNo;
	u8 u8RowNo;
	u8 u8PressedState = HIGH;
	u8 KEYPAD_keys[4][3]={{'7','8','9'},{'4','5','6'},{'1','2','3'},{'A','0','='}};
	
	/* for using TaskDelayUnitl() to make the task periodic */
	portTickType xLastWakeTime_KEYPAD;
	xLastWakeTime_KEYPAD = xTaskGetTickCount();
	
	while(1)
	{
		u8 KEYPAD_flag = LOW;
		u8PressedKey = (u8)0;
		for(u8ColNo = (u8)0; u8ColNo < NO_OF_COLS; ++u8ColNo)
		{
			DIO_vidSetPinValue(C_PORT, Columns[u8ColNo], LOW);

			for(u8RowNo = (u8)0; u8RowNo < NO_OF_ROWS; ++u8RowNo)
			{
				u8PressedState = DIO_u8GetPinValue(R_PORT, Rows[u8RowNo]);
				if(u8PressedState == LOW)
				{
					u8PressedKey = KEYPAD_keys[u8RowNo][u8ColNo];
					
					/* Remain until the key is released ==> HIGH */
					while(KEYPAD_flag == LOW)
					{
						KEYPAD_flag = DIO_u8GetPinValue(R_PORT, Rows[u8RowNo]);
					}
				}
			}
			DIO_vidSetPinValue(C_PORT, Columns[u8ColNo], HIGH);
		}
		vTaskDelayUntil( (portTickType *)&xLastWakeTime_KEYPAD , (portTickType)KEYPAD_TASK_PERIODICTIY );
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}

u8 KEYPAD_u8GetPressedKey_OS(void)
{
	return u8PressedKey;
}
