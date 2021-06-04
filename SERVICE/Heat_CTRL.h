#ifndef Heat_CNRL_H_
#define Heat_CNRL_H_

void Heat_CNRL_Duty_Cycle(s8 Current_Temp, s8 Set_Temp, f32 * Duty_Value);
void Heat_CNRL_Duty_Value_Map(f32 Duty_Value , u16 * PWM_Duty );

#endif /* Heat_CNRL_H_ */