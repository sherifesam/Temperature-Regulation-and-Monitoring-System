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
	f32 Temp_Volt = 0;
	f32 Potontiometer_Volt = 0;

	Temp_Volt = (( Set_Temp - Current_Temp) / 100.0 ) * 10.0 ;
	Potontiometer_Volt  = ADC_GetValue() ;
	*Duty_Value = ((( Potontiometer_Volt * 2.0 ) / 10.0 ) * Temp_Volt ) / 10.0;
}


void Heat_CNRL_Duty_Value_Map(f32 Duty_Value , u16 * PWM_Duty )
{
	*PWM_Duty = ( 255 - (u16)(Duty_Value * 255));
}



