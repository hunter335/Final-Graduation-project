/**************************************************************/
/**************************************************************/
/************  Author : Mustafa Elsyad   **********************/
/************  Layer  : MCAL             **********************/
/************  SWC    : ADC              **********************/
/**************************************************************/
/**************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"



#include "ADC_int.h"
#include "ADC_priv.h"
#include "ADC_reg.h"
#include "ADC_config.h"


static void (*ADC_Global_pu8NotificationFunc) (void) = NULL ;
static u16  *ADC_Global_pu16Result = NULL ;
static u8  *ADC_Global_pu8Result = NULL ;
u8  ADC_u8BusyState = IDLE ;
static  u8  *ADC_Global_pu8ChannelArray = NULL ;
static  u16 *ADC_Global_pu16ResultArray = NULL ;
static  u8  ADC_Global_copyu8Chainsize;
static  u8  ADC_Global_copyu8ChainIndex = 0 ;
static  u8  ADC_IsrSource ;

s16 MAP(s16 Copy_sint16InputMin, s16 Copy_sint16InputMax, s16 Copy_sint16OutputMin, s16 Copy_sint16OutputMax, s16 Copy_sint16InputValue)
 {
	/*Local variable to Store in it the return value*/
	s16 Local_sint16ReturnX;
	/*Calculating the slope of the Linear graph*/
	s16 Slope = (Copy_sint16InputMax-Copy_sint16InputMin)/(Copy_sint16OutputMax-Copy_sint16OutputMin);
	/*Getting the Entered Value in the variable Y*/
	s16 Y = Copy_sint16InputValue;
	/*Define a variable to store the opposite value on the line*/
	s16 X = 0;

	/*Calculating the wanted oppisite value on the line*/
     X = ((Y - Copy_sint16InputMin)/Slope)+Copy_sint16OutputMin;

	/*Check if the Entered value Smaller than the minimum*/
     if(Copy_sint16InputValue < Copy_sint16InputMin)
     {
		/*Return the MIN value*/
    	 Local_sint16ReturnX = Copy_sint16OutputMin;
     }
	 /*Check if the Entered value Bigger than the maximum*/
     else if(Copy_sint16InputValue > Copy_sint16InputMax)
     {
		/*Return the MAX value*/
    	 Local_sint16ReturnX = Copy_sint16OutputMax;
     }
     else
     {
		/*Return the Calculated value*/
    	 Local_sint16ReturnX = X;
     }


    return Local_sint16ReturnX;
 }
void ADC_voidInit(void)
{
	/*ADC Enable*/
	SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADEN);
	/*ADC Prescaler Selections*/
	SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADPS0);
	SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADPS1);
	SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADPS2);
	/*Voltage Reference Selection*/
#if VOLTAGE_REFRENCE == AREF
	CLR_BIT(ADC_ADMUX,ADC_ADMUX_REFS0);
	CLR_BIT(ADC_ADMUX,ADC_ADMUX_REFS1);
#elif VOLTAGE_REFRENCE == AVCC
	SET_BIT(ADC_ADMUX,ADC_ADMUX_REFS0);
	CLR_BIT(ADC_ADMUX,ADC_ADMUX_REFS1);
#elif VOLTAGE_REFRENCE == INTERNAL
	SET_BIT(ADC_ADMUX,ADC_ADMUX_REFS0);
	SET_BIT(ADC_ADMUX,ADC_ADMUX_REFS1);
#endif
	/*ADC  Adjust Result*/

#if RESOLUTION == TEN_BITS
	CLR_BIT(ADC_ADMUX,ADC_ADMUX_ADLAR);
#elif RESOLUTION == EIGHT_BITS
	SET_BIT(ADC_ADMUX,ADC_ADMUX_ADLAR);
#endif
}


u8 ADC_u8Read(u8 copy_u8Channel , u8 *copy_pu8Result)
{

	u8 Local_u8ErrorState = OK ;
	u32 Local_u32Counter = 0  ;
	if (ADC_u8BusyState == IDLE)
	{
		ADC_u8BusyState = BUSY ;
		if (copy_pu8Result != NULL)
		{

			ADC_ADMUX = ((ADC_ADMUX) & (0b11100000)) | (copy_u8Channel) ; // selecting the channel
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADSC); // starting conversion

			while ( (GET_BIT(ADC_ADCSRA ,ADC_ADCSRA_ADIF)!= 1) && (Local_u32Counter != ADC_TIMEOUT) )
			{
				Local_u32Counter++;
			}
			if (Local_u32Counter == ADC_TIMEOUT)
			{
				Local_u8ErrorState = 1 ;
			}
			else
			{
				/* the conversion has completed before the time out */
			}
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADIF);


			*copy_pu8Result = ADC_ADCL ;
			ADC_u8BusyState = IDLE ;

		}
		else
		{
			Local_u8ErrorState= NULL_POINTER ;
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC ;
	}
	return Local_u8ErrorState ;
}
u8 ADC_u8ReadI(u8 copy_u8Channel, u16 * copy_pu16Result,void(*copy_pu8CallBack)(void))
{
	u8  Local_u8ErrorState = OK ;
	if ((copy_pu16Result == NULL) || (copy_pu8CallBack == NULL))
	{
		Local_u8ErrorState = NULL_POINTER ;
	}
	else
	{
		if (ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState = BUSY ; // making adc busy
			ADC_IsrSource = SINGLE_CHANNEL_ASYNC ;// setting the interrupt soucrce for isr
			ADC_Global_pu16Result=copy_pu16Result ; // making local result global for isr
			ADC_Global_pu8NotificationFunc = copy_pu8CallBack ; // making local function global for isr
			ADC_ADMUX = ((ADC_ADMUX) & (0b11100000)) | (copy_u8Channel) ; // selecting the channel

			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADSC); // starting conversion
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADIE); // enable interuppt
		}
		else if (ADC_u8BusyState == BUSY)
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;

}
u8 ADC_u8ReadChainI(chain_t * copy_Chain)
{
	u8 Local_u8ErrorState = OK;
	if (copy_Chain == NULL)
	{
		Local_u8ErrorState = NULL_POINTER ;
	}
	else
	{
		if (ADC_u8BusyState == IDLE)
		{
			ADC_u8BusyState = BUSY ; // Making ADC Busy
			ADC_IsrSource = CHAIN_ASYNC ; // setting the interrupt soucrce for isr
			/*intializing local to global to use them in isr*/
			ADC_Global_pu8ChannelArray = copy_Chain ->Channels;
			ADC_Global_copyu8Chainsize = copy_Chain ->size;
			ADC_Global_pu16ResultArray = copy_Chain -> result;
			ADC_Global_pu8NotificationFunc = copy_Chain->NotiFunc;
			ADC_ADMUX = ((ADC_ADMUX) & (0b11100000)) | (ADC_Global_pu8ChannelArray[ADC_Global_copyu8ChainIndex]);
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADSC); // starting conversion
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADIE); // enable interuppt





		}
		else if (ADC_u8BusyState == BUSY)
		{
			Local_u8ErrorState = BUSY_FUNC ;

		}
	}


	return Local_u8ErrorState ;
}
void __vector_16 (void)
{
	if (ADC_IsrSource == SINGLE_CHANNEL_ASYNC)
	{

		* ADC_Global_pu16Result = ADC_ADCL ;
		ADC_u8BusyState = IDLE ;

		ADC_Global_pu8NotificationFunc();

		CLR_BIT(ADC_ADCSRA,ADC_ADCSRA_ADIE); // disable interrupt
	}
	else if (ADC_IsrSource == CHAIN_ASYNC)
	{
		ADC_Global_pu16ResultArray[ADC_Global_copyu8ChainIndex] =ADC_ADCL;
		ADC_Global_copyu8ChainIndex++;

		if (ADC_Global_copyu8ChainIndex == ADC_Global_copyu8Chainsize)
		{
			/*Finished*/
			ADC_u8BusyState = IDLE ;
			ADC_Global_pu8NotificationFunc();
			CLR_BIT(ADC_ADCSRA,ADC_ADCSRA_ADIE); // disable interrupt
			ADC_Global_copyu8ChainIndex =0 ;


		}
		else
		{
			/*Not Finished*/
			/*Set New Channel*/
			ADC_ADMUX=((ADC_ADMUX) & (0b11100000)) | (ADC_Global_pu8ChannelArray[ADC_Global_copyu8ChainIndex]);
			SET_BIT(ADC_ADCSRA,ADC_ADCSRA_ADSC); // starting conversion






		}

	}
}



