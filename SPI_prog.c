#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_int.h"
#include "SPI_config.h"
#include "SPI_priv.h"
#include "SPI_reg.h"

u8 *MSPI_uint8ReceiveData=NULL;
static void (*SPI_Global_pu8NotificationFunc) (void) = NULL ;



void Spi_voidMasterInit(void)
{

	/*Master selection*/
	SET_BIT(SPCR,SPCR_MSTR);

	// Clock

	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);




}
void Spi_voidSlaveInit(void)
{
	CLR_BIT(SPCR,SPCR_MSTR);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

u8 Spi_u8Trancieve(u8 copy_u8Data)
{
	SPDR =copy_u8Data;
	while ((GET_BIT(SPSR,SPSR_SPIF)) == 0);

	return SPDR ;


}
void MSPI_voidTranseiverDataAsynch(u8 *Copy_u8Data,void(*copy_pu8CallBack)(void) )
{
	/*Enable Spi Interrupt*/
	//SPDR = *Copy_u8Data ;

	SET_BIT(SPCR,SPCR_SPIE);
	SPI_Global_pu8NotificationFunc=copy_pu8CallBack;
	MSPI_uint8ReceiveData = Copy_u8Data ;

}


void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	*MSPI_uint8ReceiveData = SPDR;
	SPI_Global_pu8NotificationFunc();





	CLR_BIT(SPCR,SPCR_SPIE);
}

