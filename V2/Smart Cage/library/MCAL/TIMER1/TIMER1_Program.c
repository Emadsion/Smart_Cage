#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1_Register.h"
#include "TIMER1_Config.h"


void TIMER1_VoidInit(void)
{
	//Golbal Intrrupt
	SET_BIT(SREG,GIE);
	#if TIMER1 == Normal	
		CLR_BIT(TCCR1,COM1B0);
		CLR_BIT(TCCR1,COM1B1);
		CLR_BIT(TCCR1,COM1A0);
		CLR_BIT(TCCR1,COM1A1);
		#if WaveForm == CTC
			CLR_BIT(TCCR1,WGM10);
			CLR_BIT(TCCR1,WGM11);
			SET_BIT(TCCR1,WGM12);
			CLR_BIT(TCCR1,WGM13);
			//TOP
			OCR1A = 62500;
			//Enable Interrupt
			CLR_BIT(TIMSK,TOIE1);
			CLR_BIT(TIMSK,OCIE1B);
			SET_BIT(TIMSK,OCIE1A);
			CLR_BIT(TIMSK,TICIE1);
			
		#endif
			//Set Prescaler to 256
			CLR_BIT(TCCR1,CS10);
			CLR_BIT(TCCR1,CS11);
			SET_BIT(TCCR1,CS12);
		
	#endif
}


void TIMER1_VoidSetCallBack(void (*Ptr1)(void))
{
	TIMER1_PVidCallBack = Ptr1;
}




void __vector_7(void)
{
	if(TIMER1_PVidCallBack != NULL)
	{

		static u8 counter = 0;
		counter ++;
		if(counter == 1) //counter for 3 second
		{
			//DIO_VidSetPinDirection(PORTA,0,OUTPUT);
			//DIO_ToggelPin(PORTA,0);
			TIMER1_PVidCallBack();
			counter = 0;
			
		}
	}
}
