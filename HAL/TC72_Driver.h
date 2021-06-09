
#ifndef TC72_H_
#define TC72_H_

#include "../STD_Types.h"
#include "../MCAL/DIO.h"

void TC72_init(void);
void TC72_readTemperature(void);


void TC72_Task_OS(void *pvoid);
u8 get_crt_temp_OS(void);
void TC72_OS_Activate(u8 flag);


#endif /* TC72_H_ */
