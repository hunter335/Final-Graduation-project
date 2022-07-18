/*
 * TMR_program.c
 *
 *  Created on: Sep 11, 2021
 *      Author: dell
 */
/*************
 * Inclusion *
 *************/
/* Library Files */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TMR0_config.h"
#include "TMR0_interface.h"
#include "TMR0_private.h"
#include "TMR0_registers.h"
/*global pointer to function*/
 void (*G_ptr_TMR0_Notification)(void)= 0;

void M_TMR0_void_init(void)
{
   /* set prescaller */
	TCCR0 = (TCCR0 & TMR0_CLOCK_SELECT_MASKING ) | TMR0_CLOCK_SELECT ;

	   CLR_BIT(TCCR0,TCCR0_WGM00);
	   CLR_BIT(TCCR0,TCCR0_WGM01);
	/* set mode */
 #if    TMR0_Mode == TMR0_MODE_NORMAL

	   CLR_BIT(TCCR0,TCCR0_WGM00);
	   CLR_BIT(TCCR0,TCCR0_WGM01);


#elif  TMR0_Mode == TMR0_MODE_CTC

	   CLR_BIT(TCCR0,TCCR0_WGM00);
	   SET_BIT(TCCR0,TCCR0_WGM01);
	   /*set the compare top value*/
	  	   OCR0 = TMR0_CTC_TOP ;

#elif  TMR0_Mode == TMR0_MODE_FAST_PWM

	   SET_BIT(TCCR0,TCCR0_WGM00);
	   SET_BIT(TCCR0,TCCR0_WGM01);
	   SET_BIT(TCCR0,TCCR0_COM01);
	   SET_BIT(TCCR0,TCCR0_COM00);




#endif*/


	/* set preload */
	   TCNT0 =TMR0_PRELOAD_VALUE ;


}
void M_TMR0_void_MeasureTimeAsync(void (*ptr_TMR0_SetCallBack)(void))
{
	/*enable the interupt for the required mode*/
 #if TMR0_Mode == TMR0_MODE_NORMAL
	SET_BIT(TIMSK,TIMSK_TOIE0);
#elif TMR0_Mode == TMR0_MODE_CTC
	SET_BIT(TIMSK,TIMSK_OCIE0);
#endif*/
	G_ptr_TMR0_Notification =  ptr_TMR0_SetCallBack ;
}

void M_TMR0_void_SetCompareMatchValue(u8 copy_u8_Value){

	OCR0 = copy_u8_Value ;
}
void __vector_10 (void)
{
/*CTC ISR*/

		G_ptr_TMR0_Notification();


}
void __vector_11 (void)
{
/*OV ISR*/
	G_ptr_TMR0_Notification();




}
