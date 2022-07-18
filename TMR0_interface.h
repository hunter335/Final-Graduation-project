/*
 * TMR_interface.h
 *
 *  Created on: Sep 11, 2021
 *      Author: dell
 */

#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

void M_TMR0_void_init(void);
void M_TMR0_void_MeasureTimeAsync(void (*ptr_SetCallBack)(void));
void M_TMR0_void_SetCompareMatchValue(u8 copy_u8_Value);


#endif /* TMR0_INTERFACE_H_ */
