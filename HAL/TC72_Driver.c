/*
 * TC72_Driver.c
 *
 */
#define F_CPU 16000000

#include "../STD_Types.h"
#include "../macros.h"

#include "TC72_Driver.h"
#include "TC72_Driver_cfg.h"

#include "../MCAL/DIO.h"
#include "../MCAL/SPI.h"


#include <util/delay.h>


void TC72_init(void)
{
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, HIGH);

	/*Select Control Register*/
	SPI_SendData(CONTROL_REGISTER_WRITE);
	/*Select Continuous temperature Conversion*/
	SPI_SendData(CONTINUOUS_MODE);
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, LOW);

	_delay_ms(150);
}

void TC72_readTemperature(s8 * data)
{
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, HIGH);
	/*Read the MSB*/
	SPI_SendData(MSB_READ);
	/*Issue one more clock frame
	to force data out*/
	SPI_SendData(DUMMY_DATA);
	DIO_vidSetPinValue(TC72_CEPort,TC72_CEPin, LOW);
  
	_delay_ms(1);
	*data = SPI_ReceiveData();
	//return data;

}