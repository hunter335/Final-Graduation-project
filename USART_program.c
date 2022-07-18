#include "STD_TYPES.h"
#include "BIT_MATH.h"




#include "USART_registers.h"
#include "USART_interface.h"
#include "USART_private.h"

#include "USART_config.h"
u8 *UART_u8ReceiveData;
static void (*UART_Global_pu8NotificationRecievedFunc) (void) = NULL ;

void M_USART_voidInit(void) 
{
	/*full duplex*/
	SET_BIT(UCSRB ,UCSRB_RXEN);
	SET_BIT(UCSRB ,UCSRB_TXEN);
	/*select the baudrate*/
	UBRRL=51;
	u8  Local_UCSRC = 0;
	/*setting for the ucsrc values*/
	/*to enable writing to the UCSRC*/
	SET_BIT(Local_UCSRC,UCSRC_URSEL);
	/*SELECTING THE MODE*/
	CLR_BIT(Local_UCSRC,UCSRC_UMSEL);
	/*SELECTING THE parity*/
	CLR_BIT(Local_UCSRC,UCSRC_UPM1);
	CLR_BIT(Local_UCSRC,UCSRC_UPM0);
	/*SELECTING # of stop bytes*/
	CLR_BIT(Local_UCSRC,UCSRC_USBS);
	/*SELECTING the ch size*/
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_UCSRC,UCSRC_UCSZ1);
	SET_BIT(Local_UCSRC,UCSRC_UCSZ0);
	/*SELECTING THE clock polarity*/
	SET_BIT(Local_UCSRC,UCSRC_UCPOL);
	
	UCSRC = Local_UCSRC ;

	
	
}

void M_USART_voidSendByte(u8 copy_u8_byte)
{
	/*checking the buffer*/
	while (GET_BIT(UCSRA ,UCSRA_UDRE)!= 1) ;
	UDR = copy_u8_byte ;
	
	
}


u8 M_USART_u8_RecieveByte()
{
	u32 Counter = 0;

	/*checking THE COMPLETION OF RECEPTION*/
	while ((GET_BIT(UCSRA,UCSRA_RXC) != 1) && (Counter != 100000))
	{
		Counter++;

	}
	if (Counter==100000)
	{
		return 0 ;

	}
	else
	{
		return UDR ;
	}

	
	

}

void M_USART_u8_Send_Number (u8 copy_u8_Number) {
	s8 * localPtr_str[16] = {0};
	itoa(copy_u8_Number, (char *)localPtr_str, 10);
	M_USART_void_Send_String((u8 *)localPtr_str);
}
void M_USART_void_Send_String(u8 *ptr_u8_S_String)
{
    while(*ptr_u8_S_String != '\0')
    {M_USART_voidSendByte(*ptr_u8_S_String);
    ptr_u8_S_String++;}

}
void *M_USART_void_Recieve_String(u8 *ptr_u8_R_String,u8 End_Of_String)
{

	 u8   counter ;

	//receive the characters until letter is insert
	for (  counter=0  ; ; counter++)
	{

	 //and store the received characters into the array string[] one-by-one


		ptr_u8_R_String[counter] =M_USART_u8_RecieveByte();
		if (ptr_u8_R_String[counter] == End_Of_String )
		{
			break;
		}


	}
	//insert NULL to terminate the string
	ptr_u8_R_String[counter] = '\0';
	//return the received string

	}



void M_USART_void_RecieveByteAsync(u8 *copy_u8Data ,void (*copy_pu8CallBack) (void) )
{
	SET_BIT(UCSRB,UCSRB_RXCIE);
	UART_Global_pu8NotificationRecievedFunc=copy_pu8CallBack;
	UART_u8ReceiveData = copy_u8Data ;

}
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{

	*UART_u8ReceiveData = UDR ;
	UART_Global_pu8NotificationRecievedFunc();






	CLR_BIT(UCSRB,UCSRB_RXCIE);
}



