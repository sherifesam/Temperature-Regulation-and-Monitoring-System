#include "Keypad_Cfg.h"
#include "Keypad.h"



#define NO_OF_ROWS	((u8)4)
#define NO_OF_COLMS	((u8)3)

static u8 Columns[] = {C1_PIN , C2_PIN , C3_PIN} ;
static u8 Rows[] = {R1_PIN , R2_PIN , R3_PIN, R4_PIN} ;

void KEYPAD_vidInit(void)
{
	u8 u8PinNo ;

	for(u8PinNo = 0 ; u8PinNo < NO_OF_ROWS ; u8PinNo++)
	{
		/*Set Rows as input*/
		DIO_vidSetPinDir(R_PORT,Rows[u8PinNo],INPUT) ;

		/*Activate pull-up resistors */
		DIO_vidSetPinValue(R_PORT,Rows[u8PinNo],HIGH) ;
	}
	for (u8PinNo = 0 ; u8PinNo < NO_OF_COLMS ; u8PinNo++)
	{
		/*Set columns as output*/
		DIO_vidSetPinDir(C_PORT,Columns[u8PinNo],OUTPUT) ;

		/*Set Colomns HIGH*/
		DIO_vidSetPinValue(C_PORT,Columns[u8PinNo],HIGH);
	}
}

KeyPadKey KEYPAD_u8GetPressedKey(void)
{
	u8 KEYPAD_keys[4][3]={{'7','8','9'},{'4','5','6'},{'1','2','3'},{'A','0','='}};
	u8 u8ColNo , u8RowNo , u8RetVal = 0 ;

	for (u8ColNo = 0 ; u8ColNo < NO_OF_COLMS ; u8ColNo++)
	{
		/*Activate column*/
		DIO_vidSetPinValue(C_PORT , Columns[u8ColNo] , LOW) ;

		for(u8RowNo=0 ; u8RowNo < NO_OF_ROWS ; u8RowNo++)
		{
			if (DIO_u8GetPinaValue(R_PORT,Rows[u8RowNo] ) == LOW)
				{
					u8RetVal =  KEYPAD_keys[u8RowNo][u8ColNo] ;
					/*wait to depress the key*/
					while(DIO_u8GetPinaValue(R_PORT,Rows[u8RowNo] ) == LOW);
				}
		}

		/*Deactivate column*/
		DIO_vidSetPinValue(C_PORT , Columns[u8ColNo] , HIGH) ;
	}

	return u8RetVal ;
}

