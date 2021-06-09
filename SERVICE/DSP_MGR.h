#ifndef SERVICE_DSP_OS_H_
#define SERVICE_DSP_OS_H_

#define DSP_MGR_PEROIDICTY ((u32)100)

#define NORMAL_ID           ((u8)0)
#define STANDBY_ID          ((u8)1)
#define OPERATION_ID        ((u8)2)
#define ERROR_ID            ((u8)3)
#define INITIAL_STATE_ID    ((u8)4)
#define INITIAL_TEMP_ID     ((u8)5)
#define WELCOME_ID			((u8)6)


#define CRT_TEMP_ROW			((u8)1)
#define CRT_TEMP_COL			((u8)15)
#define SET_TEMP_ROW			((u8)1)
#define SET_TEMP_COL			((u8)5)



void DISP_WRITE_STATE(u8 mode_id, u8 row, u8 col, u8 *i);
void DISP_WRITE_TEMP(u8 set_temp, u8 crt_temp);
u8 IS_WRITING_FINISHED(void);
u8 IS_TEMP_DISPLAYED(void);

#endif
