
/******************************************************************************
 *
 * File Name:   TC72_Driver.c
 *
 * Description: A source file in the HAL layer of the project
 * 				which is responsible for the APIs of the TC72 Module
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/


#include "../FreeRTOS/FreeRTOS.h"

#include "TC72_Driver.h"
#include "TC72_Driver_cfg.h"

#include "../MCAL/DIO.h"
#include "../MCAL/SPI.h"


static u8 temp_data=0;
static u8 TC72_Permission = 0;



/******************************************************************************
 *
 * Function Name: TC72_init
 *
 * Description: A function responsible for intializing the sensor
 *
 * Arguments:   void
 * Return:      void
 *
 *****************************************************************************/

void TC72_init(void)
{
	/* Setting Direction */
	DIO_vidSetPinDir(TC72_CEPort, TC72_CEPin, OUTPUT);
	DIO_vidSetPinDir(TC72_SDIPort, TC72_SDIPin, OUTPUT);
	DIO_vidSetPinDir(TC72_SCKPort, TC72_SCKPin, OUTPUT);
	
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, HIGH);

	/*Select Control Register*/
	SPI_SendData(CONTROL_REGISTER_WRITE);
	/*Select Continuous temperature Conversion*/
	SPI_SendData(CONTINUOUS_MODE);
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, LOW);

}


/******************************************************************************
 *
 * Function Name: TC72_readTemperature
 *
 * Description: A function responsible for reading from the sensor
 *
 * Arguments:   void
 * Return:      void
 *
 *****************************************************************************/

void TC72_readTemperature(void)
{
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, HIGH);
	/*Read the MSB*/
	SPI_SendData(MSB_READ);
	/*Issue one more clock frame
	to force data out*/
	SPI_SendData(DUMMY_DATA);
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, LOW);
  
	temp_data = SPI_ReceiveData();

}



/******************************************************************************
 *
 * Function Name: TC72_Task_OS
 *
 * Description: A FreeRTOS task that is responsible for updating the value read
 * 				from the sensor every 200ms
 *
 * Arguments:   void *pvoid
 * Return:      void
 *
 *****************************************************************************/

/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
void TC72_Task_OS(void *pvoid)
{
	/* for using TaskDelayUnitl() to make the task periodic */
	portTickType xLastWakeTime_TC72;
	/* [MISRA-VIOLATION] (8.1, 8.6, 10.1) Standard RTOS Function typing */
	xLastWakeTime_TC72 = xTaskGetTickCount();
	
	while (1)
	{
		if(TC72_Permission == (u8)1)
		{
			TC72_readTemperature();
		}
		else
		{
			/* Do nothing */
		}
		/* [MISRA-VIOLATION] () RTOS Standrd function prototype defined in the RTOS files */
		vTaskDelayUntil( (portTickType *)&xLastWakeTime_TC72 , (portTickType)200 );
	}
	/* [MISRA VIOLATION] RULE(16.7): It is an RTOS API and a standard definition */
}


/******************************************************************************
 *
 * Function Name: get_crt_temp_OS
 *
 * Description: A function responsible for returning the static variable
 * 				temp_data which holds the value of the last reading of the 
 * 				temperature sensor
 *
 * Arguments:   void
 * Return:      u8
 *
 *****************************************************************************/
u8 get_crt_temp_OS(void)
{
	return temp_data;
}



/******************************************************************************
 *
 * Function Name: TC72_OS_Activate
 *
 * Description: A function that is responsible for updating a static variable called
 * 				TC72_Permission which enables or disables the TC72_Task_OS
 *
 * Arguments:   u8 flag
 * Return:      void
 *
 *****************************************************************************/
void TC72_OS_Activate(u8 flag)
{
	TC72_Permission = flag;
}
