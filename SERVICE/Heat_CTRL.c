/******************************************************************************
 *
 * File Name:   Heat_CTRL.c
 *
 * Description: A source file in the Service layer of the project
 * 				which is responsible for controlling the pwm
 *
 * Date:        10/6/2021
 *
 * Author:      Sherif Esam		Mostafa Amr		Muhammed el Said
 * 				Ahmed Khaled	Muhammed Ehab	Mostafa Abdelmohsen
 ******************************************************************************/

#include "../STD_Types.h"
#include "../macros.h"

#include "../HAL/TC72_Driver.h"
#include "../MCAL/TIMER0_config.h"
#include "../MCAL/TIMER0_interface.h"
#include "../MCAL/ADC_OS.h"
#include "Heat_CTRL.h"



/******************************************************************************
 *
 * Function Name: Heat_CNRL_Duty_Cycle
 *
 * Description: A Function that is responsible for calculating the duty cycle
 * 				according to the difference between the set temperature
 * 				and the current temperature and then giving that value to the 	
 * 				timer to generate the PWM
 * 
 * 
 * Arguments: 	u8 Current_Temp, u8 Set_Temp
 * Return:      void 
 *
 *****************************************************************************/
void Heat_CNRL_Duty_Cycle(u8 Current_Temp, u8 Set_Temp)
{
	f32 Temp_Volt = 0;
	f32 Potontiometer_Volt = 0;
	f32 Duty_value=0;
	u8 PWM_dutyCycle=0;
	
	Temp_Volt = ((f32)( (f32)Set_Temp - (f32)Current_Temp) / (f32)100.0 ) * (f32)10.0 ;
	Potontiometer_Volt  = ADC_OS_GetValue();
	Duty_value = (f32)((( (f32)Potontiometer_Volt * (f32)2.0 ) / (f32)10.0 ) * (f32)Temp_Volt ) / (f32)10.0;
	PWM_dutyCycle= Heat_CNRL_Duty_Value_Map(Duty_value);
	TIMER0_void_fastPWM(PWM_dutyCycle);
	
}



/******************************************************************************
 *
 * Function Name: Heat_CNRL_Duty_Value_Map
 *
 * Description: A Function that is responsible for mapping the duty cycle from
 * 				a float number to an integer rom 0 to 255
 * 
 * 
 * Arguments: 	f32 Duty_Value
 * Return:      u8
 *
 *****************************************************************************/
u8 Heat_CNRL_Duty_Value_Map(f32 Duty_Value)
{
	/* [MISRA-VIOLATION] (10.1, 10.3, 10.4) Our calculations depend on these castings only */
	u8 PWM_duty =  (u8)(255 - (u8)(Duty_Value * 255));
	return PWM_duty ;
	
}


/******************************************************************************
 *
 * Function Name: stop_pwm
 *
 * Description: A Function that is responsible for stopping the pwm
 * 
 * 
 * Arguments: 	void
 * Return:      void
 *
 *****************************************************************************/

void stop_pwm(void)
{
	TIMER0_void_fastPWM(STOP_PWM_VALUE);
}



