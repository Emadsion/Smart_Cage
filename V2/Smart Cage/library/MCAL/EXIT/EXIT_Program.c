/*********************************************************/
/* Author      : Muhammad Emad                            */
/* Date        : 10 NOV 2020                             */
/* Version     : V01                                     */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXIT_Interface.h"
#include "EXIT_Register.h"
#include "EXIT_Config.h"


void EXIT0_VidInit(void)
{
	//Global Interrupt
	SET_BIT(SREG,GIE);
	#if ISC_INT0 == RISING
		SET_BIT(MCUCR,ISC00); 
		SET_BIT(MCUCR,ISC01); 
	#elif ISC_INT0 == FALLING
		CLR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01); 
	#elif  ISC_INT0 == OCH
		
	#elif  ISC_INT0 == LOWLEVEL

	#endif
	
	// INT0 Enable (PIE)
	SET_BIT(GICR,INT0); 

}
void EXIT1_VidInit(void)
{
	//Global Interrupt
	SET_BIT(SREG,GIE);
	#if ISC_INT1 == RISING
		SET_BIT(MCUCR,ISC11); 
		SET_BIT(MCUCR,ISC10); 
	#elif ISC_INT1 == FALLING
		SET_BIT(MCUCR,ISC11);
		CLR_BIT(MCUCR,ISC10); 
	#elif  ISC_INT1 == OCH
		
	#elif  ISC_INT1 == LOWLEVEL

	#endif
	
	//Setting INT1 Enable (PIE)
	SET_BIT(GICR,INT1); 

}

void EXIT2_VidInit(void)
{
	//Global Interrupt
	SET_BIT(SREG,GIE);
	#if ISC_INT2 == RISING
		SET_BIT(MCUCSR,ISC2); 
	#elif ISC_INT2 == FALLING
		CLR_BIT(MCUCSR,ISC2);
	#endif

	//Setting INT2 Enable (PIE)
	CLR_BIT(GICR,INT2); 
	SET_BIT(GICR,INT2); 
}


//Global Interrupt 
void GIE_VidEnable(void)
{
	SET_BIT(SREG,GIE);
}

void GIE_VidDisable(void)
{
	 CLR_BIT(SREG,GIE);
}


void EXIT0_VoidSetCallBack(void (*Ptr0)(void))
{
	EXIT0_PVidCallBack = Ptr0;
}

void EXIT1_VoidSetCallBack(void (*Ptr1)(void))
{
	EXIT1_PVidCallBack = Ptr1;
}
void EXIT2_VoidSetCallBack(void (*Ptr2)(void))
{
	EXIT2_PVidCallBack = Ptr2;
}


//INT0 VECTOR 
//All vector number in table are subtracted by 1
void __vector_1(void)
{
	if(EXIT0_PVidCallBack != NULL)
		EXIT0_PVidCallBack();
	//what we want the interrupt to do 
}
//INT1 VECTOR
void __vector_2(void)
{
	if(EXIT1_PVidCallBack != NULL)
		EXIT1_PVidCallBack();
	
}

void __vector_3(void)
{
	if(EXIT2_PVidCallBack != NULL)
		EXIT2_PVidCallBack();
	CLR_BIT(GIFR,INTF2);
}
