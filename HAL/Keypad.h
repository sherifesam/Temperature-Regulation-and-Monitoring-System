#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../STD_Types.h"
#include "../MCAL/DIO.h"
void KEYPAD_vidInit(void);
u8 KEYPAD_u8GetPressedKey(void);

#endif /* KEYPAD_H_ */
