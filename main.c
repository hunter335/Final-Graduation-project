/*
 * main.
 *
 *  Created on: Sep 11, 2021
 *      Author: dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_int.h"
#include "USART_interface.h"
#include "TMR1_interface.h"

#include "GIE_interface..h"
#include <util/delay.h>

#include "TMR0_interface.h"
#include "SCH_interface.h"

/* Sensors Reslults Macros*/
#define TEMPRETURE_READING 0
#define GAS_READING        1
#define LIGHT_READING      2
/* Output Status Macros*/
#define DOOR_STATUS        0
#define FAN_STATUS       1
#define LIGHT_STATUS  	   2

void mma1 (void);
void Uart_Recieving_Handler (void);
void Spi_Recieving_Handler (void);

void ISR (void);
//u16 adcvalue = 0;
chain_t sensors; // chanin of analog sensors (LM35 "Tempreture Sensor" & MQ 5 "Gas Sensor" & LDR "Light Sensor"
u8  SensorsChannels [3] = {0,1,2};
u16 SensorsResults [3] ;
u8 Uart_Recieved_Byte = 0 ;
u8 Spi_Recieved_Byte = 0 ;
u8 AutoAdjustLight = 0;
u8 AutoAdjustFan = 0;
u8 status[3];
u8 counter ;
void Setup(void);
int main (void)
{


     Setup();









	while (1)
	{



		ADC_u8ReadChainI(&sensors);
		M_USART_void_RecieveByteAsync(&Uart_Recieved_Byte,&Uart_Recieving_Handler);
		MSPI_voidTranseiverDataAsynch(&Spi_Recieved_Byte,&Spi_Recieving_Handler);






		//Uart_Recieved_Byte = M_USART_u8_RecieveByte();


	}






}
void Setup(void)
{
	/*ADC Chain paramters*/
	sensors.Channels = &SensorsChannels;
	sensors.size = 3 ;
	sensors.result = &SensorsResults ;
	sensors.NotiFunc = &ISR;

	MDIO_voidSetPortDirection(PORTC,OUTPUT); // Output Port PORTC (PIN0 -> LED .. PIN1 -> FAN ..  PIN2 -> BUZZER .. PIN3 DOOR )
	MDIO_voidSetPinValue(PORTC,PIN3,HIGH);


	MDIO_voidSetPinDirection(PORTA,PIN0,INPUT); // Tempreture Sensor Pin PortA Pin0
	MDIO_voidSetPinDirection(PORTA,PIN1,INPUT); // Gas Sensor Pin PortA Pin1
	MDIO_voidSetPinDirection(PORTA,PIN2,INPUT); // LDR Sensor Pin PortA Pin2


	/*SPI PINS INTI*/
	MDIO_voidSetPinDirection(PORTB,PIN5,INPUT); // MOSI
	MDIO_voidSetPinDirection(PORTB,PIN7,INPUT);  // CLock
	MDIO_voidSetPinDirection(PORTB,PIN6,OUTPUT); // MISO


	MDIO_voidSetPinDirection(PORTB,PIN4,INPUT); //SS
	MDIO_voidSetPinValue(PORTB,PIN4,LOW);

	/*Prephirals Intitiation*/
	ADC_voidInit();
	Spi_voidSlaveInit();
	M_USART_voidInit();
//	M_TMR1_void_init();
	GIE_voidEnable();

	/* servo */

	//M_TMR1_void_SetTopValue(20000); // servo period
	//MDIO_voidSetPinDirection(PORTD,PIN5,OUTPUT); // servo signal pin portd pin 5





}


void ISR (void)
{
//	SensorsResults[TEMPRETURE_READING] = GET_TEMP(SensorsResults[TEMPRETURE_READING]);
//	SensorsResults[GAS_READING]        = MAP(0,1024,0,100,SensorsResults[GAS_READING]);
//	SensorsResults[LIGHT_READING]      = MAP(0,1024,0,100,SensorsResults[LIGHT_READING]);


	/*Handling The Gas Leakage*/

	if (MAP(0,1024,0,100,SensorsResults[GAS_READING]) >= 5 )
	{
		MDIO_voidSetPinValue(PORTC,PIN2,HIGH); // buzzer bin portc pin 2

	}
	else if (MAP(0,1024,0,100,SensorsResults[GAS_READING])<5)
	{
		MDIO_voidSetPinValue(PORTC,PIN2,LOW);

	}

	/*Handling High Tempreture*/

	if (AutoAdjustFan==1)
	{
		if (GET_TEMP(SensorsResults[TEMPRETURE_READING])>=25)
		{
			MDIO_voidSetPinValue(PORTC,PIN1,HIGH);  // fan pin portc pin1
			status[FAN_STATUS]=1;

		}
		else if (GET_TEMP(SensorsResults[TEMPRETURE_READING])<25)
		{
			MDIO_voidSetPinValue(PORTC,PIN1,LOW);
			status[FAN_STATUS]=0;

		}
	}


	if (AutoAdjustLight==1)
	{
		if (MAP(0,1024,0,100,SensorsResults[LIGHT_READING])>=35)
		{
			MDIO_voidSetPinValue(PORTC,PIN0,LOW);  // led pin is  portc pin0
			status[LIGHT_STATUS]=0;
		}
		else if (MAP(0,1024,0,100,SensorsResults[LIGHT_READING])<35)
		{
			MDIO_voidSetPinValue(PORTC,PIN0,HIGH);
			status[LIGHT_STATUS]=1;

		}
	}









	}

void Uart_Recieving_Handler (void)
{
			if (Uart_Recieved_Byte == 'u')
			{

				M_USART_u8_Send_Number(GET_TEMP(SensorsResults[TEMPRETURE_READING])); // send tempreture value
				M_USART_voidSendByte(' ');
				M_USART_u8_Send_Number(MAP(0,1024,0,100,SensorsResults[GAS_READING]));// send gas leakage value
				M_USART_voidSendByte(' ');
				M_USART_u8_Send_Number(MAP(0,1024,0,100,SensorsResults[LIGHT_READING])); // send Light intensity value
				M_USART_voidSendByte(' ');
				M_USART_u8_Send_Number(status[DOOR_STATUS]); // sending the door status
				M_USART_u8_Send_Number(status[FAN_STATUS]); // sending the fan status
				M_USART_u8_Send_Number(status[LIGHT_STATUS]); // sending the light status

			}
			else if (Uart_Recieved_Byte=='1')
			{
				MDIO_voidSetPinValue(PORTC,PIN3,LOW);
				status[DOOR_STATUS]= 1 ; // door is opened


			}
			else if (Uart_Recieved_Byte == '2')
			{
				MDIO_voidSetPinValue(PORTC,PIN3,HIGH);
				status[DOOR_STATUS]= 0 ; // door is closed

			}
			else if (Uart_Recieved_Byte == '3')
			{
				MDIO_voidSetPinValue(PORTC,PIN0,HIGH);
				status[LIGHT_STATUS]= 1 ; //light is open

			}
			else if (Uart_Recieved_Byte == '4')
			{
				MDIO_voidSetPinValue(PORTC,PIN0,LOW);
				status[LIGHT_STATUS]= 0 ; // light is closed


			}
			else if (Uart_Recieved_Byte == '5')
			{
				MDIO_voidSetPinValue(PORTC,PIN1,HIGH);
				status[FAN_STATUS]= 1 ; // fan is open


			}
			else if (Uart_Recieved_Byte == '6')
			{
				MDIO_voidSetPinValue(PORTC,PIN1,LOW);
				status [FAN_STATUS]= 0 ; // fan is closed

			}
			else if (Uart_Recieved_Byte == '7')
			{
				AutoAdjustLight=1; // auto adjust light

			}
			else if (Uart_Recieved_Byte == '8')
			{

				AutoAdjustLight=0; //self adjust light

			}
			else if (Uart_Recieved_Byte == '9')
			{
				AutoAdjustFan=1; //auto adjust fan

			}
			else if (Uart_Recieved_Byte == 'a')
			{

				AutoAdjustFan=0; //self adjust fan

			}




}


void Spi_Recieving_Handler (void)
{
//	static u8 counter = 0 ;
	if (Spi_Recieved_Byte==1)
	{
//		counter++;
//
//
//		if (counter==2)
//		{
			// Open the Door
			MDIO_voidSetPinValue(PORTC,PIN3,LOW);
			status[DOOR_STATUS]= 1 ; // door is opened
//		}
//		else
//		{
//
//		}


	}
	else
	{

	}
}

