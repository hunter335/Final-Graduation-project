#ifndef SCH_PRIVATE_H_
#define SCH_PRIVATE_H_


typedef struct {
	u16 periodicity ;
    void (*taskFunc)(void);	
}task_t;

static task_t taskARR[MAX_TASKS]={{0}};
static void schedule (void); 




#endif