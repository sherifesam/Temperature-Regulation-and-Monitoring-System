#define F_CPU 4000000

#include "../STD_Types.h"
#include "../macros.h"

#include "../HAL/TC72_Driver.h"
#include "../MCAL/TIMER0_config.h"
#include "../MCAL/TIMER0_interface.h"
#include "../MCAL/ADC_OS.h"
#include "Heat_CTRL.h"


void Heat_CNRL_Duty_Cycle(u8 Current_Temp, u8 Set_Temp)
{
	f32 Temp_Volt = 0;
	f32 Potontiometer_Volt = 0;
	f32 Duty_value=0;
	u8 PWM_dutyCycle=0;
	
	Temp_Volt = (( (f32)Set_Temp - (f32)Current_Temp) / (f32)100.0 ) * (f32)10.0 ;
	Potontiometer_Volt  = ADC_OS_GetValue();
	//Potontiometer_Volt = 5;
	Duty_value = ((( Potontiometer_Volt * (f32)2.0 ) / (f32)10.0 ) * Temp_Volt ) / (f32)10.0;
	PWM_dutyCycle= Heat_CNRL_Duty_Value_Map(Duty_value);
	TIMER0_void_fastPWM(PWM_dutyCycle);
	
}


u8 Heat_CNRL_Duty_Value_Map(f32 Duty_Value)
{
	u8 PWM_duty = (u8)((u8)255 - (u8)(Duty_Value * (u8)255));
	return PWM_duty;
	
}

void stop_pwm(void)
{
	TIMER0_void_fastPWM(STOP_PWM_VALUE);
}



