#ifndef LCD_EXTRA_H_
#define LCD_EXTRA_H_

#define lcd_Clear           (0x01)          /* replace all characters with ASCII 'space'          */
#define lcd_Home            (0x02)          /* return cursor to first position on first line      */
#define lcd_EntryMode       (0x06)          /* shift cursor from left to right on read/write      */
#define lcd_DisplayOff      (0x08)          /* turn display off                                   */
#define lcd_DisplayOn       (0x0C)          /* display on, cursor off, don't blink character      */
#define lcd_FunctionReset   (0x30)          /* reset the LCD                                      */
#define lcd_FunctionSet8bit (0x38)          /* 8-bit data, 2-line display, 5 x 7 font             */
#define lcd_FunctionSet4bit (0x28)          /* 4-bit data, 2-line display, 5 x 7 font             */
#define lcd_SetCursor       (0x80)          /* set cursor position                                */
#define lcd_ShiftRight		(0b00011100)	/* Shift display right without changing DDRAM content */
#define lcd_ShiftLeft		(0b00011000)	/* Shift display left without changing DDRAM content  */

/*States*/
#define STATE_INIT_0	((u8)0)
#define STATE_INIT_1	((u8)1)
#define STATE_INIT_2	((u8)2)
#define STATE_INIT_3	((u8)3)
#define STATE_INIT_4	((u8)4)
#define STATE_0			((u8)5)
#define STATE_1			((u8)6)

#define ON_GOING		((u8)0)
#define DONE			((u8)1)

#define E_OK ((u8)0)
#define E_NOK ((u8)1)

#define LCD_TASK_PERIODICTIY ((u32)5)

#define RS_PORT			(PORTC)
#define RS_PIN			(PIN0)
#define RW_PORT			(PORTC)
#define RW_PIN			(PIN1)
#define ENABLE_PORT		(PORTC)
#define ENABLE_PIN		(PIN2)
#define DATA_PORT		(PORTD)


#endif /* LCD_EXTRA_H_ */