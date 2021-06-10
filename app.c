/******************************************************************************
 *
 * File Name:   app.c
 *
 * Description: A source file in the application layer of the project
 * 				that is responsible for switching between modes of the system
 * 				according to the difference between the set temperature and 
 * 				Temperature. It handles the mode switching operation with FreeRTOS
 * 				tasks.
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/


#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/FreeRTOSConfig.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/timers.h"
#include "STD_Types.h"
#include "HAL/LCD_OS.h"
#include "HAL/Keypad_OS.h"
#include "MCAL/SPI.h"
#include "MCAL/ADC_priv.h"
#include "MCAL/ADC_OS.h"
#include "MCAL/TIMER0_PRIV.h"
#include "MCAL/TIMER0_config.h"
#include "MCAL/TIMER0_interface.h"
#include "HAL/TC72_Driver_cfg.h"
#include "HAL/TC72_Driver.h"
#include "SERVICE/Keypad_Service_OS.h"
#include "SERVICE/DSP_MGR.h"
#include "SERVICE/Heat_CTRL.h"


/* Change this value to get more convenient results as it depends on the system (differs from one system to another) */
#define SW_TIMER_THRESHOLD (7000)

static u8 init_flag=0;

xTaskHandle * keypad_service_handler = NULL;
xTaskHandle * adc_handler = NULL;
xTaskHandle * sensor_handler = NULL;

xTimerHandle Timer_Function1;

static void MyTimer(xTimerHandle Timer_Function);
void APP_OS_TASK(void* pvoid);
void WELCOME_OS_TASK(void* pvoid);
void Init_Task(void* pvoid);


/******************************************************************************
 *
 * Function Name: MyTimer
 *
 * Description: Call Back function for the software timer 
 *
 * Arguments:   xTimerHandle Timer_Function
 * Return:      void
 *
 *****************************************************************************/

static void MyTimer(xTimerHandle Timer_Function)
{
	/* Check SW_TIMER_THRESHOLD to adjust the time required for your system */ 
	/* Empty Function For the Timer */
}



/******************************************************************************
 *
 * Function Name: APP_OS_TASK
 *
 * Description: A FreeRTOS task responsible for mode switching in the system
 *
 * Arguments:   void* pvoid
 * Return:      void
 *
 *****************************************************************************/

void APP_OS_TASK(void* pvoid)
{
	u8 current_value = 0;
	u8 set_value = 0;
	u8 standby_flag=1;
	u8 error_flag=0;
	u8 operational_flag=0;
	
	portTickType Entered_Time=0;
	portTickType Time_Now=0;

	/* setting directions.. */
	DIO_vidSetPinDir(PORTB, PIN3, OUTPUT);  /* PWM pin */
	u8 j=0;
	static u8 ctr=0;
	/* for using TaskDelayUnitl() to make the task periodic */
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		/* Getting Temperature Values */
		current_value = get_crt_temp_OS();
		set_value = get_set_temp_OS();
		
		
		if(check_hash_key())
		{
			/* Activating sensor and ADC if the State isn't STANDBY */
			ADC_OS_Activate((standby_flag));
			TC72_OS_Activate((standby_flag));
			
			/* Switching to Operational | Normal */
			standby_flag = !standby_flag;
			
		}
		if((standby_flag == (u8)1) && (error_flag == (u8)0))  /* STANDBY */
		{
			operational_flag = (u8)0;
			DISP_WRITE_STATE(STANDBY_ID, (u8)2, (u8)7, &j);
			DISP_WRITE_TEMP(set_value,current_value);
			
			stop_pwm();
			
		}
		else if(error_flag == (u8)1)  /* ERROR */
		{
			DISP_WRITE_STATE(ERROR_ID, (u8)2, (u8)7, &j);

			stop_pwm();
			ADC_OS_Activate((!error_flag));
			TC72_OS_Activate((!error_flag));
		}
		else
		{
			if((set_value - current_value) > (u8)5)  /* OPERATIONAL */
			{
				if(operational_flag == (u8)0)
				{
					Entered_Time = xTaskGetTickCount();
					operational_flag = (u8)1;
				}
				else if((Time_Now - Entered_Time) > (portTickType)SW_TIMER_THRESHOLD)
				{
					/* Check SW_TIMER_THRESHOLD to adjust the time required for your system */
					error_flag = (u8)1;
				}
				else
				{
				    /* DO NOTHING */
				}
				
				Time_Now = xTaskGetTickCount();
				DISP_WRITE_STATE(OPERATION_ID, (u8)2, (u8)7, &j);
				DISP_WRITE_TEMP(set_value,current_value);
			
				Heat_CNRL_Duty_Cycle(current_value, set_value);
				
				
			}
			else if (((set_value - current_value) >= (u8)0) && ((set_value - current_value) <= (u8)5)) /* NORMAL */
			{
				operational_flag = (u8)0;
				DISP_WRITE_STATE(NORMAL_ID, (u8)2, (u8)7, &j);
				DISP_WRITE_TEMP(set_value,current_value);
				stop_pwm();
			}
			else if (((current_value - set_value) >= (u8)0) && ((current_value - set_value) < (u8)10)) /* NORMAL */
			{
				operational_flag = (u8)0;
				DISP_WRITE_STATE(NORMAL_ID, (u8)2, (u8)7, &j);
				DISP_WRITE_TEMP(set_value,current_value);
				stop_pwm();
			}
			else     /* ERROR */
			{
				DISP_WRITE_TEMP(set_value,current_value);
				if(ctr == (u8)4)
				{
					error_flag = (u8)1;
				}
				ctr++;
			}		
		}
		
		/* [MISRA-VIOLATION] */
		vTaskDelayUntil( (portTickType *)&xLastWakeTime, (portTickType)25 );
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}



/******************************************************************************
 *
 * Function Name: WELCOME_OS_TASK
 *
 * Description: A FreeRTOS task responsible for the welcome screen
 *
 * Arguments:   void* pvoid
 * Return:      void
 *
 *****************************************************************************/


/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
void WELCOME_OS_TASK(void* pvoid)
{
	u8 WELCOME_STATE = 0;
	u8 WELCOME_IT = 0;
	u8 WELCOME_CTR = 0;
	u8 turn = 0;
	u8 STATE_ITE = 0;
	u8 TEMP_ITE = 0;
	
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
			case (u8)11:
			{
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)10)
				{
					WELCOME_CTR = (u8)0;
					WELCOME_STATE++;
				}
			}
			break;
			case (u8)12:
			{
				if(turn == (u8)0)
				{
					DISP_WRITE_STATE(INITIAL_STATE_ID, (u8)2, (u8)1, &STATE_ITE);
				}
				else if(turn == (u8)1)
				{
					DISP_WRITE_STATE(INITIAL_TEMP_ID, (u8)1, (u8)1, &TEMP_ITE);
				}
				else
				{
				    /* DO NOTHING */
				}
				turn = (turn + (u8)1) % (u8)2;
				WELCOME_CTR++;
				if(WELCOME_CTR == (u8)40)
				{
					WELCOME_CTR = (u8)0;
					init_flag = (u8)1;
					/* task deletion */
					vTaskDelete((xTaskHandle)NULL);
					WELCOME_STATE++; /* NOT NEEDED */
				}
				else
				{
				    /* DO NOTHING */
				}
			}
			break;
			
			default:
			    break;
		}
		/* [MISRA VIOLATION] RULE(8.1 8.6): It is an RTOS API and a standard definition */
		vTaskDelay(100);
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}


/******************************************************************************
 *
 * Function Name: Init_Task
 *
 * Description: A FreeRTOS task responsible for the initializing the system
 *
 * Arguments:   void* pvoid
 * Return:      void
 *
 *****************************************************************************/

void Init_Task(void* pvoid)
{
	
	while(1)
	{
		if(init_flag == (u8)1)
		{
			/* initializations */
			TIMER0_void_Init();
			KEYPAD_OS_vidInit();
			SPI_init();
			TC72_init();
			ADC_OS_init();
			
			/* [MISRA VIOLATION] RULE(10.1,16.9): It is an RTOS Function-like macro */
			xTaskCreate(APP_OS_TASK,NULL,150,NULL,2,NULL);
			
			/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
			xTaskCreate(TC72_Task_OS,NULL,configMINIMAL_STACK_SIZE,NULL,3,sensor_handler);
			
			/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
			xTaskCreate(ADC_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,3,adc_handler);
			
			/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
			xTaskCreate(KEYPAD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,1,NULL);

			/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
			xTaskCreate(Keypad_service_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,1,keypad_service_handler);
			
			vTaskDelete((xTaskHandle)NULL);
			
		}
		else
		{
			/* Do nothing */
		}
		vTaskDelay((portTickType)500);
	}
	
}



int main(void)
{
	LCD_OS_vidInit();
	
	/* [MISRA VIOLATION] RULE(16.9): Standard typing of the xTimerCreate function */
	Timer_Function1= xTimerCreate((const signed char*)"(MyTimer)", (portTickType)1, (unsigned portBASE_TYPE)pdTRUE, (void *) 0, MyTimer);

	/* [MISRA VIOLATION] RULE(10.1): It is an RTOS Function-like macro */
	xTimerStart( Timer_Function1, 0 );

	
	/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
	xTaskCreate(WELCOME_OS_TASK,NULL,configMINIMAL_STACK_SIZE,NULL,4,NULL);

	/* [MISRA VIOLATION] RULE(10.1, 16.9, 6.3): It is an RTOS Function-like macro */
	xTaskCreate(LCD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL);
	
	/* [MISRA VIOLATION] RULE(10.1 , 16.9): It is an RTOS Function-like macro */
	xTaskCreate(Init_Task,NULL,100,NULL,4,NULL);


	vTaskStartScheduler();

return 1;

}
