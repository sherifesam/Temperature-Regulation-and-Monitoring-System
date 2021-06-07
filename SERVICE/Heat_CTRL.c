#define F_CPU 4000000

#include "../STD_Types.h"
#include "../macros.h"

#include "../HAL/TC72_Driver.h"
<<<<<<< HEAD
#include "../MCAL/TIMER0_config.h"
#include "../MCAL/TIMER0_interface.h"
=======
#include "../MCAL/PWM_TIMER0/TIMER0_config.h"
#include "../MCAL/PWM_TIMER0/TIMER0_interface.h"
>>>>>>> 0a15d8d38eed37cdd23fc0da873697d4184fd460
#include "../MCAL/ADC_OS.h"
#include "Heat_CTRL.h"


<<<<<<< HEAD
=======

>>>>>>> 0a15d8d38eed37cdd23fc0da873697d4184fd460
void Heat_CNRL_Duty_Cycle(u8 Current_Temp, u8 Set_Temp)
{
	f32 Temp_Volt = 0;
	f32 Potontiometer_Volt = 0;
	f32 Duty_value=0;
	u8 PWM_dutyCycle=0;
	
	Temp_Volt = (( (f32)Set_Temp - (f32)Current_Temp) / (f32)100.0 ) * (f32)10.0 ;
	Potontiometer_Volt  = ADC_OS_GetValue();
<<<<<<< HEAD
	//Potontiometer_Volt = 5;
=======
>>>>>>> 0a15d8d38eed37cdd23fc0da873697d4184fd460
	Duty_value = ((( Potontiometer_Volt * (f32)2.0 ) / (f32)10.0 ) * Temp_Volt ) / (f32)10.0;
	PWM_dutyCycle= Heat_CNRL_Duty_Value_Map(Duty_value);
	TIMER0_void_fastPWM(PWM_dutyCycle);
	
}


u8 Heat_CNRL_Duty_Value_Map(f32 Duty_Value)
{
<<<<<<< HEAD
	u8 PWM_duty = (u8)((u8)255 - (u8)(Duty_Value * (u8)255));
=======
	u8 PWM_duty = ((u8)((u8)Duty_Value * (u8)255));
>>>>>>> 0a15d8d38eed37cdd23fc0da873697d4184fd460
	return PWM_duty;
	
}

void stop_pwm(void)
{
	TIMER0_void_fastPWM(STOP_PWM_VALUE);
}



