#ifndef USART_interface_H_
#define USART_interface_H_
void M_USART_voidInit(void);
void M_USART_voidSendByte(u8 copy_u8_byte);
u8   M_USART_u8_RecieveByte();
void M_USART_void_Send_String(u8 *ptr_u8_S_String);
void *M_USART_void_Recieve_String(u8 *ptr_u8_R_String,u8 Length_Of_string);
void M_USART_u8_Send_Number (u8 copy_u8_Number);
void M_USART_void_RecieveByteAsync(u8 *copy_u8Data ,void (*copy_pu8CallBack) (void) );






#endif
