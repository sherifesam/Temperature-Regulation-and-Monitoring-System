#define F_CPU 16000000

#include "../STD_Types.h"
#include "../macros.h"

#include "../HAL/TC72_Driver.h"
#include "../MCAL/Timer.h"
#include "../MCAL/ADC.h"
#include "../MCAL/Timer.h"

#include <util/delay.h>



void Heat_CNRL_Duty_Cycle(s8 Current_Temp, s8 Set_Temp, f32* Duty_Value)
{
	u16 Temp_Volt = 0;
	u16 Potontiometer_Volt = 0;

	Temp_Volt = (( Set_Temp - Current_Temp) / 100 ) * 10 ;
	//Potontiometer_Volt  = (ADC_u16Read() * (5/255));
	/*if ((u16)ADC_u16Read() > 280 )
	{
		*Duty_Value = 6;
	}
	else
	{
		*Duty_Value = 2;
	}*/
	
	Potontiometer_Volt = 5;
	*Duty_Value = ((( Potontiometer_Volt * 2 ) / 10 ) * Temp_Volt ) / 10;
}


void Heat_CNRL_Duty_Value_Map(f32 Duty_Value , u16 * PWM_Duty )
{
	*PWM_Duty = (u16)Duty_Value * 255;
}



