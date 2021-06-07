#ifndef Heat_CNRL_H_
#define Heat_CNRL_H_


#define STOP_PWM_VALUE	((u8)255)

void Heat_CNRL_Duty_Cycle(u8 Current_Temp, u8 Set_Temp);
u8 Heat_CNRL_Duty_Value_Map(f32 Duty_Value);
void stop_pwm(void);

#endif /* Heat_CNRL_H_ */
