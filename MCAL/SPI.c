/******************************************************************************
 *
 * File Name:   SPI.c
 *
 * Description: A source file in the MCAL layer of the project
 * 				which is responsible for the APIs of the SPI Module
 * 				
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/

#include "../STD_Types.h"
#include "../macros.h"
#include "DIO.h"
#include "SPI_priv.h"
#include "SPI.h"




/******************************************************************************
 *
 * Function Name: SPI_init
 *
 * Description: A Function that is responsible for initializing the SPI module
 * 
 * Arguments: 	u8 flag
 * Return:      void 
 *
 *****************************************************************************/

void SPI_init(void)
{
    /*configuring master*/
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    set_bit(SPCR,PIN4);
    /*setup then sample with a leading rising edge (CPHA)*/
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    set_bit(SPCR,PIN2);
    /*set prescaller 128*/
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    set_bit(SPCR,PIN1);
    set_bit(SPCR,PIN0);
    /*enable SPI*/
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    set_bit(SPCR,PIN6);
}



/******************************************************************************
 *
 * Function Name: SPI_SendData
 *
 * Description: A Function that is responsible for putting data in the SPDR register
 *              to be sent through SPI communication
 * 
 * Arguments: 	u8 u8data
 * Return:      void 
 *
 *****************************************************************************/

void SPI_SendData(u8 u8data){
    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
    SPDR = u8data;
    u8 send_flag = 0;
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    send_flag = get_bit(SPSR,PIN7);
    while(send_flag != ((u8)1))
    {
        /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
        send_flag = get_bit(SPSR,PIN7);
    }
}


/******************************************************************************
 *
 * Function Name: SPI_ReceiveData
 *
 * Description: A Function that is responsible for taking te value from the
 *              SPDR register whenever the recieving flag is set to 1
 * 
 * Arguments: 	u8 u8data
 * Return:      void 
 *
 *****************************************************************************/

u8 SPI_ReceiveData(void){
    u8 recieve_flag = 0;
    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
    recieve_flag = get_bit(SPSR,PIN7);
    while(recieve_flag != ((u8)1))
    {
        /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
        recieve_flag = get_bit(SPSR,PIN7);
    }
    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
	return (u8)SPDR;
}
