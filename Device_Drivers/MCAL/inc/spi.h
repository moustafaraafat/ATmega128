/*
 * spi.h
 *
 * Created: 6/7/2020 10:29:00 AM
 *  Author: Raafat
 */ 


#ifndef SPI_H_
#define SPI_H_


#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"

typedef enum{
	MODE_MASTER, MODE_SLAVE	
}SPI_Mode;

#define SPI_PORT		PORTB
#define SPI_DDR			DDRB

#define SPI_SS			PB0
#define SPI_SCK			PB1
#define SPI_MOSI		PB2
#define SPI_MISO		PB3

void	SPI_Init(SPI_Mode spiMode);
INT8U	SPI_Tranceive(INT8U u8Data);

#endif /* SPI_H_ */