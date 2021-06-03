/*
 * TC72_Driver_cfg.h
 *
 * Created: 6/2/2021 4:44:40 PM
 *  Author: hp
 */ 

#ifndef TC72_DRIVER_CFG_H_
#define TC72_DRIVER_CFG_H_


#define CONTROL_REGISTER_WRITE  ((u8)0x80)
#define CONTINUOUS_MODE			((u8)0x04)
#define MSB_READ				((u8)0x02)
#define DUMMY_DATA				((u8)0x00)




#define TC72_DataPort    PORTB

#define TC72_SDIPort     PORTB
#define TC72_SDIPin      PIN5

#define TC72_SDOPort     PORTB
#define TC72_SDOPin      PIN6

#define TC72_SCKPort	 PORTB
#define TC72_SCKPin      PIN7

#define TC72_CEPort		 PORTB
#define TC72_CEPin		 PIN4


#endif /* TC72_DRIVER_CFG_H_ */