#ifndef SPI_INT_H
#define SPI_INT_H

void Spi_voidMasterInit(void);
void Spi_voidSlaveInit(void);
u8  Spi_u8Trancieve(u8 copy_u8Data);
void MSPI_voidTranseiverDataAsynch(u8 *Copy_u8Data,void(*copy_pu8CallBack)(void));












#endif
