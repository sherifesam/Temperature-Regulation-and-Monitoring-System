/*
 * ADC.h
 *
 * Created: 6/2/2021 6:04:15 PM
 * Author : mostafa amr
 */ 
#ifndef _ADC_OS_H
#define _ADC_OS_H

void ADC_OS_init(void);
void ADC_OS_Task(void* pvoid);
f32 ADC_OS_GetValue(void);

#endif
