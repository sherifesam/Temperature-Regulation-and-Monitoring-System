#ifndef HAL_KEYPAD_OS_H_
#define HAL_KEYPAD_OS_H_

#include "../STD_Types.h"
#include "../MCAL/DIO.h"

#define u8 NO_OF_ROWS ((u8)4)
#define u8 NO_OF_COLS ((u8)3)
#define KEYPAD_TASK_PERIODICTIY 200

void KEYPAD_OS_vidInit(void);
void KEYPAD_OS_Task(void *pvoid);
u8 KEYPAD_u8GetPressedKey(void);

#endif /* HAL_KEYPAD_OS_H_ */