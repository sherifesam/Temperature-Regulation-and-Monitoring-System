#ifndef SERVICE_KEYPAD_OS_H_
#define SERVICE_KEYPAD_OS_H_

#include "HAL/Keypad_OS.h"

#define KEYPAD_SERVICE_PEROIDICTY 200

void Keypad_service_OS_Task(void *pvoid);
u8 get_set_temp_OS(void);

#endif