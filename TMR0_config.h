/*
 * TMR_config.h
 *
 *  Created on: Sep 11, 2021
 *      Author: dell
 */

#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_

/* SELCET THE REQUIRED CLOCK SELECT :
 *TMR0_CLOCK_SELECT_NOCLOCK
 *TMR0_CLOCK_SELECT_PRESCALLER_1
 *TMR0_CLOCK_SELECT_PRESCALLER_8
 *TMR0_CLOCK_SELECT_PRESCALLER_64
 *TMR0_CLOCK_SELECT_PRESCALLER_256
 *TMR0_CLOCK_SELECT_PRESCALLER_1024
 *TMR0_CLOCK_SELECT_EXTERNAL_FALLING
 *TMR0_CLOCK_SELECT_EXTERNAL_RISING
 *
 * */

#define TMR0_CLOCK_SELECT TMR0_CLOCK_SELECT_PRESCALLER_8


/*SELECT THE REQUIRED TIMER MODE :
 *TMR0_MODE_NORMAL
 *TMR0_MODE_PWM_PHASE_CORRECT
 *TMR0_MODE_CTC
 *TMR0_MODE_FAST_PWM
 */
#define TMR0_Mode TMR0_MODE_CTC

/*SET THE REQUIRED TOP VALUE OF CTC
 * 0 : 255
  */
#define TMR0_CTC_TOP  255
/*SET THE REQUIRED PRELOAD VALUE
 * 0 : 255
  */

#define TMR0_PRELOAD_VALUE 0
#define NEEDED_OVERFLOW    4




#endif /* TMR0_CONFIG_H_ */
