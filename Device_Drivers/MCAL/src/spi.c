/*
* spi.c
*
* Created: 6/7/2020 10:29:39 AM
*  Author: Raafat
*/
#include "spi.h"


void	SPI_Init(SPI_Mode spiMode){
	switch(spiMode)
	{
		case MODE_MASTER:
		/* Out */
		setBit(SPI_DDR, SPI_MOSI);
		setBit(SPI_DDR, SPI_SCK);
		setBit(SPI_DDR, SPI_SS);
		/* In */
		clearBit(SPI_DDR, SPI_MISO);
		/* Unselect for Slave*/
		setBit(SPI_PORT, SPI_SS);
		/* Master Mode Select*/
		setBit(SPCR, MSTR);
		break;
		case MODE_SLAVE:
		/* In */
		clearBit(SPI_DDR, SPI_MOSI);
		clearBit(SPI_DDR, SPI_SCK);
		clearBit(SPI_DDR, SPI_SS);
		/* Out	 */
		setBit(SPI_DDR, SPI_MISO);
		/* Slave Mode Select*/
		clearBit(SPCR, MSTR);
		break;
	}
	/* Enable SPI */
	setBit(SPCR, SPE);
	_delay_ms(10);
}

INT8U	SPI_Tranceive(INT8U u8Data){
	/* Update DR */
	SPDR = u8Data;	/* Shift Started */
	/* Wait for Shift Complete Flag  SPIF */
	while( !(readBit(SPSR, SPIF)) );
	/* Return DR */
	return SPDR;
}