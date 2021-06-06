#ifndef HAL_KEYPAD_OS_H_
#define HAL_KEYPAD_OS_H_

#define NO_OF_ROWS ((u8)4)
#define NO_OF_COLS ((u8)3)
#define KEYPAD_TASK_PERIODICTIY 200

void KEYPAD_OS_vidInit(void);
void KEYPAD_OS_Task(void *pvoid);
u8 KEYPAD_u8GetPressedKey_OS(void);

#endif /* HAL_KEYPAD_OS_H_ */