#include "STD_Types.h"
#include "DIO.h"
#include "Keypad_OS_cfg.h"
#include "Keypad_OS.h"

static u8 Rows[] = {R1_PIN, R2_PIN, R3_PIN, R4_PIN};
static u8 Columns[] = {C1_PIN, C2_PIN, C3_PIN};

// NOT INITALIZED TO SAVE MEMORY, WATCH THE VIDEO...
static u8 u8PressedKey;

void KEYPAD_OS_vidInit(void)
{
    u8 u8PinNo = 0;

    // Initialize the rows...
    for(u8PinNo = 0; u8PinNo < NO_OF_ROWS; ++u8PinNo)
    {
        DIO_vidSetPinDir(R_PORT, Rows[u8PinNo], INPUT);
        DIO_vidSetPinValue(R_PORT,Rows[u8PinNo],HIGH);
    }

    // Initialize the columns...
    for(u8PinNo = 0; u8PinNo < NO_OF_COLS; ++u8PinNo)
    {
        DIO_vidSetPinDir(R_PORT, Columns[u8PinNo], OUTPUT);
        DIO_vidSetPinValue(R_PORT,Columns[u8PinNo],HIGH);
    }
}

void KEYPAD_OS_Task(void *pvoid)
{
    u8 u8ColNo;
    u8 u8RowNo;
    u8 u8PressedState = HIGH;
    u8 KEYPAD_keys[4][3]={{'7','8','9'},{'4','5','6'},{'1','2','3'},{'A','0','='}};
    while(1)
    {
        u8PressedKey = 0;
        for(u8ColNo = 0; u8ColNo < NO_OF_COLS; ++u8ColNo)
        {
            DIO_vidSetPinValue(C_PORT, Columns[u8ColNo], LOW);

            for(u8RowNo = 0; u8RowNo < NO_OF_ROWS; ++u8RowNo)
            {
                u8PressedState = DIO_u8GetPinValue(R_PORT, Rows[u8RowNo]);
                if(u8PressedState == LOW)
                {
                    u8PressedKey = KEYPAD_keys[u8RowNo][u8ColNo];
                    // Remain until the key is released ==> HIGH...
                    while(DIO_u8GetPinValue(R_PORT, Rows[u8RowNo]) == LOW);
                }
            }
            DIO_vidSetPinValue(C_PORT, Columns[u8ColNo], HIGH);
        }
        vTaskDelay(KEYPAD_TASK_PERIODICTIY);
    }
}

u8 KEYPAD_u8GetPressedKey_OS(void)
{
    return u8PressedKey;
}