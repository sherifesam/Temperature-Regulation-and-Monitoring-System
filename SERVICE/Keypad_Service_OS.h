#ifndef SERVICE_KEYPAD_OS_H_
#define SERVICE_KEYPAD_OS_H_

#include "HAL/Keypad_OS.h"

#define KD_ERROR 0
#define KEYPAD_SERVICE_PEROIDICTY 100

void Keypad_service_OS_Task(void *pvoid);
u8 get_set_temp_OS(void);

#endif