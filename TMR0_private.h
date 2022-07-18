/*
 * TMR_private.h
 *
 *  Created on: Sep 11, 2021
 *      Author: dell
 */

#ifndef TMR0_PRIVATE_H_
#define TMR0_PRIVATE_H_

#define TMR0_CLOCK_SELECT_MASKING   0b11111100
 /*CLOCK SELECTION*/
#define TMR0_CLOCK_SELECT_NOCLOCK						0
#define TMR0_CLOCK_SELECT_PRESCALLER_1					1
#define TMR0_CLOCK_SELECT_PRESCALLER_8					2
#define TMR0_CLOCK_SELECT_PRESCALLER_64					3
#define TMR0_CLOCK_SELECT_PRESCALLER_256				4
#define TMR0_CLOCK_SELECT_PRESCALLER_1024               5
#define TMR0_CLOCK_SELECT_EXTERNAL_FALLING              6
#define TMR0_CLOCK_SELECT_PRESCALLER_EXTERNAL_RISING    7



/*MODE SELECTION*/
#define TMR0_MODE_NORMAL 				0
#define TMR0_MODE_PWM_PHASE_CORRECT    	1
#define TMR0_MODE_CTC    				2
#define TMR0_MODE_FAST_PWM  			3

/*ISR COMPILER ATTRIBUTES :  CTC_INT    OV_INT*/
void __vector_10 (void)__attribute__((signal)) ;
void __vector_11 (void)__attribute__((signal)) ;


#endif /* TMR0_PRIVATE_H_ */
