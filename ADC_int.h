/**************************************************************/
/**************************************************************/
/************  Author : Mustafa Elsyad   **********************/
/************  Layer  : MCAL             **********************/
/************  SWC    : ADC              **********************/
/**************************************************************/
/**************************************************************/

#ifndef ADC_INT_H_
#define ADC_INT_H_

typedef struct
{
	u8 *Channels ;
	u16 *result ;
	u8 size   ;
	void (*NotiFunc)(void);

} chain_t ;

#define GET_TEMP(ADC_VALUE) (u16)(((u32)ADC_VALUE * 5000UL) / 1024UL)/10

void ADC_voidInit(void);
u8 ADC_u8Read(u8 copy_u8Channel, u8 * copy_pu8Result);
u8 ADC_u8ReadI(u8 copy_u8Channel, u16 * copy_pu16Result,void(*copy_pu8CallBack)(void));//single ended input
u8 ADC_u8ReadChainI(chain_t * copy_Chain);
s16 MAP(s16 Copy_sint16InputMin, s16 Copy_sint16InputMax, s16 Copy_sint16OutputMin, s16 Copy_sint16OutputMax, s16 Copy_sint16InputValue);
/*Channles*/
#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5
#define ADC6  6
#define ADC7  7










#endif
