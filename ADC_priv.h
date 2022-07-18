#ifndef ADC_PRI_H_ 
#define ADC_PRI_H_ 

#define AREF       0
#define AVCC       1
#define INTERNAL   2

#define TEN_BITS 0
#define EIGHT_BITS  1

#define IDLE         0
#define BUSY         1
#define SINGLE_CHANNEL_ASYNC 0
#define CHAIN_ASYNC          1
void __vector_16 (void)__attribute__((signal));












#endif
