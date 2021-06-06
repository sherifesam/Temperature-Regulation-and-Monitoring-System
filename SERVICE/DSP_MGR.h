#ifndef SERVICE_DSP_OS_H_
#define SERVICE_DSP_OS_H_

#include "../HAL/LCD_OS.h"
#include "../HAL/Keypad_OS.h"

#define NORMAL_ID           0
#define STANDBY_ID          1
#define OPERATION_ID        2
#define ERROR_ID            3
#define INITIAL_STATE_ID    4
#define INITIAL_TEMP_ID     5


//char set_temp[] = {'1', '2', '\0'};
//char crt_temp[] = {'3', '4', '\0'};

void DISP_WRITE_STATE(u8 mode_id, u8 row, u8 col, u8 *i);
void DISP_WRITE_TEMP(u8 set_temp, u8 crt_temp);

#endif