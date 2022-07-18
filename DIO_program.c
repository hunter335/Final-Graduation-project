#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"

void MDIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection)
{
	switch(copy_u8PortId)
	{
		case PORTA: if(copy_u8PortDirection == OUTPUT)
		            {
		                DDRA_REG = 0xFF;	
		            }
					else if(copy_u8PortDirection == INPUT)
					{
						DDRA_REG = 0x00;
					}
					else
					{
						//error
					}
					break;
		case PORTB: if(copy_u8PortDirection == OUTPUT)
		            {
		                DDRB_REG = 0xFF;	
		            }
					else if(copy_u8PortDirection == INPUT)
					{
						DDRB_REG = 0x00;
					}
					else
					{
						//error
					}
					break;
		case PORTC: if(copy_u8PortDirection == OUTPUT)
		            {
		                DDRC_REG = 0xFF;	
		            }
					else if(copy_u8PortDirection == INPUT)
					{
						DDRC_REG = 0x00;
					}
					else
					{
						//error
					}
					break;
		case PORTD: if(copy_u8PortDirection == OUTPUT)
		            {
		                DDRD_REG = 0xFF;	
		            }
					else if(copy_u8PortDirection == INPUT)
					{
						DDRD_REG = 0x00;
					}
					else
					{
						//error
					}
					break;
		default: /* invalid port id */ break;
	}
}

void MDIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue)
{
		switch(copy_u8PortId)
	{
		case PORTA: if(copy_u8PortValue == HIGH)
		            {
		                PORTA_REG = 0xFF;	
		            }
					else if(copy_u8PortValue == LOW)
					{
						PORTA_REG = 0x00;
					}
					else
					{
						PORTA_REG = copy_u8PortValue;
					}
					break;
		case PORTB: if(copy_u8PortValue == HIGH)
		            {
		                PORTB_REG = 0xFF;	
		            }
					else if(copy_u8PortValue == LOW)
					{
						PORTB_REG = 0x00;
					}
					else
					{
						PORTB_REG = copy_u8PortValue;
					}
					break;
		case PORTC: if(copy_u8PortValue == HIGH)
		            {
		                PORTC_REG = 0xFF;	
		            }
					else if(copy_u8PortValue == LOW)
					{
						PORTC_REG = 0x00;
					}
					else
					{
						PORTC_REG = copy_u8PortValue;
					}
					break;
		case PORTD: if(copy_u8PortValue == HIGH)
		            {
		                PORTD_REG = 0xFF;	
		            }
					else if(copy_u8PortValue == LOW)
					{
						PORTD_REG = 0x00;
					}
					else
					{
						PORTD_REG = copy_u8PortValue;
					}
					break;
		default: /* invalid port id */ break;
	}
}


void MDIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
	switch(copy_u8PortId)
	{
		case PORTA: if(copy_u8PinDirection == OUTPUT)
		            {
		                SET_BIT(DDRA_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinDirection == INPUT)
					{
						CLR_BIT(DDRA_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTB: if(copy_u8PinDirection == OUTPUT)
		            {
		                SET_BIT(DDRB_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinDirection == INPUT)
					{
						CLR_BIT(DDRB_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTC: if(copy_u8PinDirection == OUTPUT)
		            {
		                SET_BIT(DDRC_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinDirection == INPUT)
					{
						CLR_BIT(DDRC_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTD: if(copy_u8PinDirection == OUTPUT)
		            {
		                SET_BIT(DDRD_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinDirection == INPUT)
					{
						CLR_BIT(DDRD_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		default: /* invalid port id  */ break;
	}
}

void MDIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue)
{
	switch(copy_u8PortId)
	{
		case PORTA: if(copy_u8PinValue == HIGH)
		            {
		                SET_BIT(PORTA_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinValue == LOW)
					{
						CLR_BIT(PORTA_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTB: if(copy_u8PinValue == HIGH)
		            {
		                SET_BIT(PORTB_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinValue == LOW)
					{
						CLR_BIT(PORTB_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTC: if(copy_u8PinValue == HIGH)
		            {
		                SET_BIT(PORTC_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinValue == LOW)
					{
						CLR_BIT(PORTC_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		case PORTD: if(copy_u8PinValue == HIGH)
		            {
		                SET_BIT(PORTD_REG, copy_u8PinId);	
		            }
					else if(copy_u8PinValue == LOW)
					{
						CLR_BIT(PORTD_REG, copy_u8PinId);
					}
					else
					{
						//error
					}
					break;
		default: /* invalid port id  */ break;
	}
}


void MDIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	switch(copy_u8PortId)
	{
		case PORTA: TOG_BIT(PORTA_REG, copy_u8PinId);break;
		case PORTB: TOG_BIT(PORTB_REG, copy_u8PinId);break;
		case PORTC: TOG_BIT(PORTC_REG, copy_u8PinId);break;
		case PORTD: TOG_BIT(PORTD_REG, copy_u8PinId);break;
		default: /* invalid port id */ break;
	}
}

u8   MDIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	u8 Local_u8PinState;
	switch(copy_u8PortId)
	{
		case PORTA: Local_u8PinState = GET_BIT(PINA_REG, copy_u8PinId);break;
		case PORTB: Local_u8PinState = GET_BIT(PINB_REG, copy_u8PinId);break;
		case PORTC: Local_u8PinState = GET_BIT(PINC_REG, copy_u8PinId);break;
		case PORTD: Local_u8PinState = GET_BIT(PIND_REG, copy_u8PinId);break;
		default:  /* invalid port id */ break;
	}
	
	return Local_u8PinState;
}


