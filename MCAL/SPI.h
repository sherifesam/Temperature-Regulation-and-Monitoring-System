/*
 * SPI.h
 *
 *  Created on: Oct 12, 2018
 *      Author: hp
 */

#ifndef SPI_H_
#define SPI_H_

void SPI_SendData(s8 u8data);
s8 SPI_ReceiveData();
void SPI_init(void);

#endif /* SPI_H_ */
