
#include "../STD_Types.h"
#include "../MCAL/DIO.h"
#include "../macros.h"

/*Local defines*/

/* PORTA Registers*/

#define DDRA_REGISTER  (*((volatile u8*) 0x3A))
#define PORTA_REGISTER  (*((volatile u8*) 0x3B))
#define PINA_REGISTER    (*((volatile u8*) 0x39))

/*PORTB Registers*/
#define DDRB_REGISTER  (*((volatile u8*) 0x37))
#define PORTB_REGISTER  (*((volatile u8*) 0x38))
#define PINB_REGISTER    (*((volatile u8*) 0x36))

/*PORTC Registers*/
#define DDRC_REGISTER  (*((volatile u8*) 0x34))
#define PORTC_REGISTER  (*((volatile u8*) 0x35))
#define PINC_REGISTER    (*((volatile u8*) 0x33))

/*PORTD Registers*/
#define DDRD_REGISTER  (*((volatile u8*) 0x31))
#define PORTD_REGISTER  (*((volatile u8*) 0x32))
#define PIND_REGISTER    (*((volatile u8*) 0x30))



void DIO_vidSetPortDir(u8 u8portName, u8 u8PortDir)
{
	switch (u8portName)
	{
		case PORTA :
		{
			if(u8PortDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRA_REGISTER = (u8)0x00 ;
			}
			else
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			    DDRA_REGISTER = (u8)0xFF ;
			}
		}break;

		case PORTB :
		{
			if(u8PortDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRB_REGISTER = (u8)0x00 ;
			}
			else
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRB_REGISTER = (u8)0xFF ;
			}
		}break;

		case PORTC :
		{
			if(u8PortDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRC_REGISTER = (u8)0x00 ;
			}
			else
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRC_REGISTER = (u8)0xFF;
			}
		}break;

		case PORTD :
		{
			if(u8PortDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRD_REGISTER = (u8)0x00;
			}
			else
			{
			    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
				DDRD_REGISTER = (u8)0xFF ;
			}
		}break;

		default:
		    break;
	}
}



void DIO_vidSetPinDir(u8 u8portName, u8 u8pinNo , u8 u8PinDir){
	switch (u8portName)
	{
		case PORTA :
		{
			if (u8PinDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				clr_bit(DDRA_REGISTER ,u8pinNo);
			}
			else if (u8PinDir == OUTPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				set_bit(DDRA_REGISTER , u8pinNo );
			}
			else
			{
				/*Invalid Input*/
			}

		}break;

		case PORTB :
		{
			if (u8PinDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				clr_bit(DDRB_REGISTER ,u8pinNo);
			}
			else if (u8PinDir == OUTPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				set_bit(DDRB_REGISTER , u8pinNo);
			}
			else
			{
				/*Invalid Input*/
			}
		}break;

		case PORTC :
		{
			if (u8PinDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				clr_bit(DDRC_REGISTER ,u8pinNo);
			}
			else if (u8PinDir == OUTPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				set_bit(DDRC_REGISTER , u8pinNo );
			}
			else
			{
				/*Invalid Input*/
			}

		}break;
		case PORTD :
		{
			if (u8PinDir == INPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				clr_bit(DDRD_REGISTER ,u8pinNo);
			}
			else if (u8PinDir == OUTPUT)
			{
			    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
				set_bit(DDRD_REGISTER , u8pinNo );
			}
			else
			{
				/*Invalid Input*/
			}
		}break;
		default:
		    break;
	}
}


void DIO_vidSetPortValue (u8 u8PortName , u8 u8PortValue)
{
	switch (u8PortName)
	{
		case PORTA :
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			PORTA_REGISTER = u8PortValue;
		}break;

		case PORTB :
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			PORTB_REGISTER = u8PortValue;
		}break ;

		case PORTC :
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			PORTC_REGISTER = u8PortValue;
		}break ;

		case PORTD :
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			PORTD_REGISTER = u8PortValue;
		}break ;
		default:
		    break;
	}
}



void DIO_vidSetPinValue (u8 u8portName , u8 u8pinNo , u8 u8pinValue)
{
	switch (u8portName)
	{
		case PORTA :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
		    /* [MISRA VIOLATION] RULE(12.2): assigning bit in a register would not result an error*/
			assign_bit(PORTA_REGISTER,u8pinNo,u8pinValue) ;
		}break;

		case PORTB :
		{
            /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
            /* [MISRA VIOLATION] RULE(12.2): assigning bit in a register would not result an error*/
			assign_bit(PORTB_REGISTER,u8pinNo,u8pinValue) ;
		}break ;

		case PORTC :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
		    /* [MISRA VIOLATION] RULE(12.2): assigning bit in a register would not result an error*/
		    assign_bit(PORTC_REGISTER,u8pinNo,u8pinValue) ;
		}break ;

		case PORTD :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
		    /* [MISRA VIOLATION] RULE(12.2): assigning bit in a register would not result an error*/
		    assign_bit(PORTD_REGISTER,u8pinNo,u8pinValue) ;
		}break;
		default:
		    break;
	}
}



u8 DIO_vidGetPortValue(u8 u8PortName)
{
	u8 retVal ;
	switch(u8PortName)
	{
		case PORTA:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			retVal = PINA_REGISTER;
		}break ;

		case PORTB:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			retVal = PINB_REGISTER;
		}break ;

		case PORTC:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			retVal = PINC_REGISTER;
		}break ;

		case PORTD:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
			retVal = PIND_REGISTER;
		}break ;
		default:
		    break;
	}

	return retVal;
}



u8 DIO_u8GetPinValue (u8 u8PortName , u8 u8PinNo )
{
	u8 Value ;
	switch (u8PortName)
	{
		case PORTA :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
			Value =  get_bit(PINA_REGISTER, u8PinNo);
		}break ;
		case PORTB :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
			Value =  get_bit(PINB_REGISTER, u8PinNo);
		}break ;
		case PORTC :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
			Value =  get_bit(PINC_REGISTER, u8PinNo);
		}break ;

		case PORTD :
		{
		    /* [MISRA VIOLATION] RULE(11.3): bitwise operations inside registers would not result an error*/
			Value =  get_bit(PIND_REGISTER, u8PinNo);
		}break ;
		default:
		    break;
	}

	return Value ;
}

void DIO_vidSetLowNibbleValue(u8 u8PortName, u8 u8LowNibbleValue)
{
	u8LowNibbleValue &= (u8)0x0f;
	switch(u8PortName)
	{
		case PORTA:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTA_REGISTER &= (u8)0xf0;
            PORTA_REGISTER |= u8LowNibbleValue;
		}
		break;
		case PORTB:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTB_REGISTER &= (u8)0xf0;
            PORTB_REGISTER |= u8LowNibbleValue;
		}
		break;
		case PORTC:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTC_REGISTER &= (u8)0xf0;
            PORTC_REGISTER |= u8LowNibbleValue;
		}
		break;
		case PORTD:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTD_REGISTER &= (u8)0xf0;
            PORTD_REGISTER |= u8LowNibbleValue;
		}
		break;
		default:
		    break;
	}
}

void DIO_vidSetHighNibbleValue(u8 u8PortName, u8 u8HighNibbleValue)
{
	u8HighNibbleValue <<= 4;
	switch(u8PortName)
	{
		case PORTA:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
            PORTA_REGISTER &= (u8)0x0f;
            PORTA_REGISTER |= u8HighNibbleValue;
		}
		break;
		case PORTB:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTB_REGISTER &= (u8)0x0f;
            PORTB_REGISTER |= u8HighNibbleValue;
		}
		break;
		case PORTC:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTC_REGISTER &= (u8)0x0f;
            PORTC_REGISTER |= u8HighNibbleValue;
		}
		break;
		case PORTD:
		{
		    /* [MISRA VIOLATION] RULE(11.3): writing on register would not result an error*/
		    PORTD_REGISTER &= (u8)0x0f;
            PORTD_REGISTER |= u8HighNibbleValue;
		}
		break;
		default:
		    break;
	}
}













