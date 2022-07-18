#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_


#define SPDR                *((volatile u8*)0x2F) /*SPI Data Register*/
					        
#define SPSR                *((volatile u8*)0x2E)  /*SPI Status Register*/

#define SPSR_SPIF           7
#define SPSR_WCOL           6
#define SPSR_SPI2X          0

#define SPCR                *((volatile u8*)0x2D) /*SPI Control Register*/

#define SPCR_SPIE           7
#define SPCR_SPE            6
#define SPCR_DORD           5
#define SPCR_MSTR           4
#define SPCR_CPOL           3
#define SPCR_CPHA           2
#define SPCR_SPR1           1
#define SPCR_SPR0           0
#endif
