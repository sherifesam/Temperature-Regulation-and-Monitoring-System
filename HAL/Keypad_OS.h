#ifndef HAL_KEYPAD_OS_H_
#define HAL_KEYPAD_OS_H_

void KEYPAD_OS_vidInit(void);
void KEYPAD_OS_Task(void *pvoid);
u8 KEYPAD_u8GetPressedKey_OS(void);

#endif /* HAL_KEYPAD_OS_H_ */
