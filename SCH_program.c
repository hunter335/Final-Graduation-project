#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TMR0_interface.h"
#include "SCH_interface.h"
#include "SCH_config.h"
#include "SCH_private.h"

void SCH_Start(void){
	// 1- init for timer 
	// 2- measure time async takes schedule as i/p 
	M_TMR0_void_init();
	M_TMR0_void_MeasureTimeAsync(&schedule);
	
}
void SCH_Create(u8 Copy_u8_Priority,u16 Copy_u16_Periodicity,void(*ptr_Task_func)(void))
 {
	 taskARR[Copy_u8_Priority].periodicity = Copy_u16_Periodicity;
	 taskARR[Copy_u8_Priority].taskFunc = ptr_Task_func;
	 
 }
 static void schedule (void) {
	 
	 // called at fixed time 
	 static u16 Local_u16_TickCount = 0 ;
	 Local_u16_TickCount++;
	 for (u8 Local_u8_TaskCount = 0 ; Local_u8_TaskCount < MAX_TASKS; Local_u8_TaskCount++ )
	 {
		 if (Local_u16_TickCount % taskARR[Local_u8_TaskCount].periodicity == 0 ) 
		 {
			 taskARR[Local_u8_TaskCount].taskFunc();
		 }
	 }
 }
