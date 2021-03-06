#ifndef KEYPAD_OS_CFG_H_
#define KEYPAD_OS_CFG_H_

#define NO_OF_ROWS ((u8)4)
#define NO_OF_COLS ((u8)3)

#define KEYPAD_TASK_PERIODICTIY (25)

/*Configure Columns port and pins*/
#define C_PORT	(PORTA)
#define C1_PIN	(PIN4)
#define C2_PIN	(PIN5)
#define C3_PIN	(PIN6)
#define C4_PIN	(PIN7)

/*Configure Rows port and pins*/
#define R_PORT	(PORTD)
#define R1_PIN	(PIN0)
#define R2_PIN	(PIN1)
#define R3_PIN	(PIN2)
#define R4_PIN	(PIN3)



#endif /* KEYPAD_OS_CFG_H_ */
