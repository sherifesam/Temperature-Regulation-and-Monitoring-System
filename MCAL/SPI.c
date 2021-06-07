#include "../STD_Types.h"
#include "../macros.h"
#include "DIO.h"
#include "SPI_priv.h"
#include "SPI.h"


void SPI_init(void)
{
    /*configuring master*/
    /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
    set_bit(SPCR,PIN4);
    /*setup then sample with a leading rising edge (CPHA)*/
    /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
    set_bit(SPCR,PIN2);
    /*set prescaller 128*/
    /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
    set_bit(SPCR,PIN1);
    set_bit(SPCR,PIN0);
    /*enable SPI*/
    /* [MISRA VIOLATION] RULE(11.3 & 10.5): Unsolvable*/
    set_bit(SPCR,PIN6);
}

void SPI_SendData(u8 u8data){
    /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
    SPDR = u8data;
    u8 send_flag = 0;
    /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
    send_flag = get_bit(SPSR,PIN7);
    while(send_flag != ((u8)1))
    {
        /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
        send_flag = get_bit(SPSR,PIN7);
    }
}

u8 SPI_ReceiveData(void){
    u8 recieve_flag = 0;
    /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
    recieve_flag = get_bit(SPSR,PIN7);
    while(recieve_flag != ((u8)1))
    {
        /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
        recieve_flag = get_bit(SPSR,PIN7);
    }
    /* [MISRA VIOLATION] RULE(11.3): Unsolvable*/
	return (u8)SPDR;
}
