#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GIE_config.h"
#include "GIE_interface..h"
#include "GIE_private.h"
#include "GIE_registers.h"


void GIE_voidEnable(void) 
{
	SET_BIT(SREG,SREG_I);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
