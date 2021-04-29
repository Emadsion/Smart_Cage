#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "WDT_Register.h"

void WD_TimerEnable()
{
	//Enable WDT
	SET_BIT(WDTCR,WDE);
	//Set Prescaler to 1 second
	CLR_BIT(WDTCR,WDP0);
	SET_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP2);
}

void WD_TimerDisable()
{
		/*to disable an enabled WDT we must follow certian procdure
		1- Write logic one to both WDTOE and WDE at the same time
		2- Withing 4 clock cycle disable WDE (4 clock cycle is a MUST)
		*/ 
		WDTCR = (1<<WDTOE) | (1<<WDE);
		//Do not use the CLR_BIT operation as it may take more than 4 clock cycle
		WDTCR = 0x00;
}