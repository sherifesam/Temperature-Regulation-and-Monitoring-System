#include "../STD_Types.h"
#include "../MCAL/DIO.h"
#include "TC72_Driver.h"
#include "TC72_Driver_cfg.h"
#include "../MCAL/DIO.h"
#include "../MCAL/SPI.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

/* Global variable to be returned to the SERVICE layer */
static u8 temp_data=0;


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


void TC72_Task_OS(void *pvoid)
{
	while (1)
	{
		TC72_readTemperature();
		vTaskDelay(TC72_TASK_PERIODICTIY);
	}
}

u8 get_crt_temp_OS(void)
{
	return temp_data;
}
