/*
 * TMR1_registers.h
 *
 *  Created on: Sep 13, 2021
 *      Author: dell
 */

#ifndef TMR1_REGISTERS_H_
#define TMR1_REGISTERS_H_

/*Timer/Counter1 Control Register A – TCCR1A*/
#define TCCR1A         *((volatile u8*)0x4F)
#define TCCR1A_COM1A1  7
#define TCCR1A_COM1A0  6
#define TCCR1A_COM1B1  5
#define TCCR1A_COM1B0  4
#define TCCR1A_FOC1A   3
#define TCCR1A_FOC1B   2
#define TCCR1A_WGM11   1
#define TCCR1A_WGM10   0
/*Timer/Counter1 Control Register B – TCCR1B*/

#define TCCR1B         *((volatile u8*)0x4E)
#define TCCR1B_ICNC1   7
#define TCCR1B_ICES1   6
#define TCCR1B_WGM13   4
#define TCCR1B_WGM12   3
#define TCCR1B_CS12    2
#define TCCR1B_CS11    1
#define TCCR1B_CS10    0
/*Timer/Counter1 – TCNT1H and TCNT1L*/
#define TCNT1L        *((volatile u16*)0x4C)
#define TCNT1H		  *((volatile u8*)0x4D)
/*Output Compare Register 1 A – OCR1AH and OCR1AL */
#define OCR1AL        *((volatile u16*)0x4A)
/*Output Compare Register 1 B  – OCR1BH and OCR1BL*/
#define OCR1BL        *((volatile u16*)0x48)
/*Input Capture Register 1 – ICR1H and ICR1L*/
#define ICR1L         *((volatile u16*)0x46)
/*Timer/Counter Interrupt Mask Register – TIMSK*/

#define TIMSK		  *((volatile u8*)0x59)
#define TIMSK_TICIE1  5
#define TIMSK_OCIE1A  4
#define TIMSK_OCIE1B  3
#define TIMSK_TOIE1   2



#endif /* TMR1_REGISTERS_H_ */
