#ifndef SERVICE_KEYPAD_OS_H_
#define SERVICE_KEYPAD_OS_H_

#include "../HAL/Keypad_OS.h"

#define HASH_PRESSED 1
#define HASH_NOT_PRESSED 0
#define KEYPAD_SERVICE_PEROIDICTY 50

void Keypad_service_OS_Task(void *pvoid);
u8 get_set_temp_OS(void);
u8 check_hash_key(void);


#endif