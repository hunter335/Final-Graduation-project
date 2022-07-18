#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TMR1_interface.h"
#include "TMR1_registers.h"



void M_TMR1_void_init(void)
{
	/*Timer 1 Mode = FastPWm Set on top Clear on compare*/
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	/*Choosing the wave generation mode for fast pwm icr1 is the top value*/
	SET_BIT(TCCR1A,TCCR1A_WGM11); // TCCR1A REG
	CLR_BIT(TCCR1A,TCCR1A_WGM10); // TCCR1A REG
	SET_BIT(TCCR1B,TCCR1B_WGM13); // TCCR1B REG
	SET_BIT(TCCR1B,TCCR1B_WGM12); // TCCR1B REG
	/*prescaller Choosing  = div by 8 */
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
}

void M_TMR1_void_SetTopValue(u16 copy_u16_Value)
{
	ICR1L = copy_u16_Value ;


}

void M_TMR1_void_SetCompareMatchValue(u16 copy_u16_Value)
{
	OCR1AL = copy_u16_Value ;

}


