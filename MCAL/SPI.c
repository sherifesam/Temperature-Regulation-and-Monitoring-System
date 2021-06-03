/*
 * SPI.c
 *
 */

#include "../STD_Types.h"
#include "../macros.h"
#include "DIO.h"
#include "SPI_priv.h"


void SPI_init(void)
{
/*configuring master*/
set_bit(SPCR,PIN4);
/*setup then sample with a leading rising edge (CPHA)*/
set_bit(SPCR,PIN2);
/*set prescaller 128*/
set_bit(SPCR,PIN1);
set_bit(SPCR,PIN0);
/*enable SPI*/
set_bit(SPCR,PIN6);
}

void SPI_SendData(s8 u8data){
SPDR=u8data;
u8 flag=get_bit(SPSR,PIN7);
while(flag!=1){
	flag=get_bit(SPSR,PIN7);
}
}

s8 SPI_ReceiveData(){
u8 flag=get_bit(SPSR,PIN7);
while(flag!=1){
	flag=get_bit(SPSR,PIN7);
}
	return SPDR;
}
