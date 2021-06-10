/******************************************************************************
 *
 * File Name:   ADC_OS.c
 *
 * Description: A source file in the MCAL layer of the project
 * 				which is responsible for the APIs of the ADC Module
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/

#include "../FreeRTOS/FreeRTOS.h"
#include "../STD_Types.h"
#include "../macros.h"
#include "../MCAL/DIO.h"
#include "ADC_priv.h"
#include "ADC_OS.h"


static f32 ADC_value = 0;
static u8 ADC_Permission = 0;




/******************************************************************************
 *
 * Function Name: ADC_OS_init
 *
 * Description: A Function that is responsible for initializing the ADC module
 *
 * Arguments: 	void
 * Return:      void 
 *
 *****************************************************************************/

void ADC_OS_init(void)
{
	/*SET PINS DIR*/
	DIO_vidSetPinDir(PORTA, PIN0, INPUT);

	/*ADC ON*/
	/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
	set_bit(MADC->ADCSRA,ADEN);
	/*V reference*/
	/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
	set_bit(MADC->ADMUX,REFS0);

	/*READ ADCH ONLY*/
	/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
	set_bit(MADC->ADMUX,ADLAR);
}



/******************************************************************************
 *
 * Function Name: ADC_OS_Task
 *
 * Description: A FreeRTOS task that is responsible for getting an ADC value
 * 				Every 500ms
 *
 * Arguments: 	void* pvoid
 * Return:      void 
 *
 *****************************************************************************/

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
void ADC_OS_Task(void* pvoid)
{
	u8 high;
	
	/* for using TaskDelayUnitl() to make the task periodic */
	portTickType xLastWakeTime_ADC;
	/* [MISRA-VIOLATION] (8.1, 8.6, 10.1) This is a standard typing from RTOS */
	xLastWakeTime_ADC = xTaskGetTickCount();
	
	while (1)
	{
		if(ADC_Permission == (u8)1)
		{
			/*start conversion*/
			/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
			set_bit(MADC->ADCSRA,ADSC);

			/*polling*/
			/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
			while(is_bit_clr(MADC->ADCSRA,ADIF))
			{
				/* DO NOTHING */
			}
			/* clear ADIF */
			/* [MISRA-VIOLATION] (11.3) Standard function-like macro */
			set_bit(MADC->ADCSRA,ADIF);

			/* [MISRA-VIOLATION] (11.3) Standard locations */
			high = MADC->ADCH;
			
			ADC_value = (f32)(((f32)high*(f32)5)/(f32)256);

		}
		else
		{
			/* Do nothing */
		}
		
		/* [MISRA-VIOLATION] (8.1, 8.6) Function prototype defined in the RTOS files */
		vTaskDelayUntil( (portTickType *)&xLastWakeTime_ADC , (portTickType)500 );
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}



/******************************************************************************
 *
 * Function Name: ADC_OS_GetValue
 *
 * Description: A FreeRTOS task that is responsible for returning the last updated
 * 				ADC value
 *
 * Arguments: 	void
 * Return:      f32 
 *
 *****************************************************************************/

f32 ADC_OS_GetValue(void)
{
	return ADC_value;
}




/******************************************************************************
 *
 * Function Name: ADC_OS_Task
 *
 * Description: A function that is responsible for updating a static variable called
 * 				ADC_Permission which enables or disables the ADC_OS_Task
 * 
 * 
 * Arguments: 	u8 flag
 * Return:      void 
 *
 *****************************************************************************/

void ADC_OS_Activate(u8 flag)
{
	ADC_Permission = flag;
}
