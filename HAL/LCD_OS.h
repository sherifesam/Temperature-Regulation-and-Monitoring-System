#ifndef HAL_LCD_OS_H_
#define HAL_LCD_OS_H_

extern void LCD_OS_vidInit(void);

extern u8 LCD_OS_WriteChar(u8 ch);

void LCD_OS_Task(void* pvoid);
u8 LOC_vidSendCommand(u8 u8CmdCpy);
u8 LCD_OS_WriteChar_API(void);
u8 is_wreq_available(void);
u8 getCursorCommand(u8 row, u8 col);

#endif /* HAL_LCD_OS_H_ */