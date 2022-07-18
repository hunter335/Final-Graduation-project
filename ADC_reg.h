/**************************************************************/
/**************************************************************/
/************  Author : Mustafa Elsyad   **********************/
/************  Layer  : MCAL             **********************/
/************  SWC    : ADC              **********************/
/**************************************************************/
/**************************************************************/



#ifndef ADC_REG_H_
#define ADC_REG_H_

/*ADC registers */
#define ADC_ADMUX             *((volatile u8*)0x27)
#define ADC_ADCL              *((volatile u16*)0x24)
#define ADC_ADCH              *((volatile u8*)0x25)
#define ADC_SFIOR             *((volatile u8*)0x50)
#define ADC_ADCSRA            *((volatile u8*)0x26)
                              
                              
/*ADC Multiplexer Selection Register Bits */
                              
#define ADC_ADMUX_REFS1       7
#define ADC_ADMUX_REFS0       6   
#define ADC_ADMUX_ADLAR       5   
#define ADC_ADMUX_MUX4        4
#define ADC_ADMUX_MUX3        3
#define ADC_ADMUX_MUX2        2
#define ADC_ADMUX_MUX1        1
#define ADC_ADMUX_MUX0        0
                              
/*ADC control and status register Bits  */
                              
#define ADC_ADCSRA_ADEN       7 
#define ADC_ADCSRA_ADSC       6 
#define ADC_ADCSRA_ADATE      5
#define ADC_ADCSRA_ADIF       4 
#define ADC_ADCSRA_ADIE       3 
#define ADC_ADCSRA_ADPS2      2
#define ADC_ADCSRA_ADPS1      1 
#define ADC_ADCSRA_ADPS0      0
                              
/* ADC Special FunctionIO Register Bits  */
                              
#define ADC_SFIOR_ADTS2       7
#define ADC_SFIOR_ADTS1       6
#define ADC_SFIOR_ADTS0       5
#define ADC_SFIOR_ACME        3
#define ADC_SFIOR_PUD         2
#define ADC_SFIOR_PSR2        1
#define ADC_SFIOR_PSR10       0











     





 

#endif
