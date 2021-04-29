#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Register.h"



void DIO_VidSetPinDirection(u8 port,u8 pin_Num,u8 state)
{
	if(1==state)
	{
		
		switch(port)
		{
			
			case 0: SET_BIT(DDRA,pin_Num); break;
			case 1: SET_BIT(DDRB,pin_Num); break;
			case 2: SET_BIT(DDRC,pin_Num); break;
			case 3: SET_BIT(DDRD,pin_Num); break;
			
		}
	}
	
	else if(0==state)
	{
		
		switch(port)
		{
			
			case 0: CLR_BIT(DDRA,pin_Num); break;
			case 1: CLR_BIT(DDRB,pin_Num); break;
			case 2: CLR_BIT(DDRC,pin_Num); break;
			case 3: CLR_BIT(DDRD,pin_Num); break;
			
		}
	}
	else
	{
		
	}
	
	

}

void DIO_VidSetPortDirection(u8 port,u8 Direction)
{
	switch(port)
	{
		case 0: DDRA=Direction; break;
		case 1: DDRB=Direction; break;
		case 2: DDRC=Direction; break;
		case 3: DDRD=Direction; break;
		default:                break;
	}
}


void DIO_VidSetPinValue (u8 port,u8 pin_Num,u8 value)
{
	if(1==value)
	{
		
		switch(port)
		{
			
			case 0: SET_BIT(PORTA,pin_Num); break;
			case 1: SET_BIT(PORTB,pin_Num); break;
			case 2: SET_BIT(PORTC,pin_Num); break;
			case 3: SET_BIT(PORTD,pin_Num); break;
			
		}
	}
	else if(0==value)
	{
		
		switch(port)
		{
			
			case 0: CLR_BIT(PORTA,pin_Num); break;
			case 1: CLR_BIT(PORTB,pin_Num); break;
			case 2: CLR_BIT(PORTC,pin_Num); break;
			case 3: CLR_BIT(PORTD,pin_Num); break;
			
		}
	}
	else
	{
		
	
	}
}


void DIO_VidSetPortValue(u8 port,u8 Value)
{
	switch(port)
	{
		case 0: PORTA=Value; break;
		case 1: PORTB=Value; break;
		case 2: PORTC=Value; break;
		case 3: PORTD=Value; break;
		default:             break;
	}
	
}


u8 DIO_u8GetPinValue(u8 port,u8 pin_Num)
{
	u8 u8Result;
	
	switch (port)
	 {
		case 0: u8Result= GET_BIT(PINA,pin_Num); break;
		case 1: u8Result= GET_BIT(PINB,pin_Num); break;
		case 2: u8Result= GET_BIT(PINC,pin_Num); break;
		case 3: u8Result= GET_BIT(PIND,pin_Num); break;
		default:                                 break;
	 }
	 return u8Result;
}


void DIO_ToggelPin(u8 port,u8 pin_Num)
{
	switch(port)
	{
		case 0: TOG_BIT(PORTA,pin_Num);   break;
		case 1: TOG_BIT(PORTB,pin_Num);   break;
		case 2: TOG_BIT(PORTC,pin_Num);   break;
		case 3: TOG_BIT(PORTD,pin_Num);  break;
		default:                         break;
	}
}

