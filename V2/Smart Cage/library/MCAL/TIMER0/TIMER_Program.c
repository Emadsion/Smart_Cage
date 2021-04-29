#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_Register.h"
#include "TIMER_Config.h"


/*
Equation of timer:
					T(OV)=256*Prescaler/frequency
					Counter = Required time / T(ov)
					Preload = 256 - (256 * counter float)


 */

void TIMER0_VidInit(void)
{

	//Global Interrupt
		//SET_BIT(SREG,GIE);
	//TIMER0 MODE NORMAL/ OV MODE
	#if TIMER0_MODE == NORMAL
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		/*We want to do an action every  1 sec
		//Preload Value (Important to set it first before setting the prescaler as once the prescaler is set the timer will begin instantly)
		*/TCNT0 = 133;
		
		//Enable OV Interrupt
		SET_BIT(TIMSK,TOIE0);
		CLR_BIT(TIMSK,OCIE0);
		
		//PRESCALER 1024
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);


	#elif TIMER0_MODE == CTC
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		OCR0 = 128
		//Enable CTC Interrupt
		CLR_BIT(TIMSK,TOIE0);
		SET_BIT(TIMSK,OCIE0);
		//PRESCALER 1024
		SET_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		SET_BIT(SREG,GIE);

	#elif TIMER0_MODE == FastPWM
		SET_BIT(TCCR0,3);
		SET_BIT(TCCR0,6);

		/*//Disable any timer Interrupt
		CLR_BIT(TIMSK,TOIE0);
		CLR_BIT(TIMSK,OCIE0);
*/
		//Non Inverted Mode
		CLR_BIT(TCCR0,4);
		SET_BIT(TCCR0,5);

		//PRESCALER 1024
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);


	#endif
}

void TIMER0_VoidDutyCycle(u8 Duty)
{
	OCR0 = Duty;
}

void TIMER0_VoidSetCallBack(void (*Ptr0)(void))
{
	TIMER0_PVidCallBack = Ptr0;
}




void __vector_11(void)
{
	if(TIMER0_PVidCallBack != NULL)
	{
		static u8 counter = 0;
		counter ++;
		if(counter == 31) //counter for 1 second
		{
			//DIO_VidSetPinDirection(PORTA,0,OUTPUT);
			//DIO_ToggelPin(PORTA,0);
			TIMER0_PVidCallBack();
			counter = 0;
			TCNT0 = 133;
		}
	}
}
