/*
 * SPI_LOC.h
 *
 *  Created on: Oct 12, 2018
 *      Author: hp
 */

#ifndef SPI_LOC_H_
#define SPI_LOC_H_



#define SPCR  (*((volatile u8*)0x2D ))
#define SPSR  (*((volatile u8*)0x2E ))
#define SPDR  (*((volatile u8*)0x2F ))

#endif /* SPI_LOC_H_ */
