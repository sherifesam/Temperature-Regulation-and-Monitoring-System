
#ifndef _ADC_OS_H
#define _ADC_OS_H

void ADC_OS_init(void);
void ADC_OS_Task(void* pvoid);
f32 ADC_OS_GetValue(void);
void ADC_OS_Activate(u8 flag);

#endif