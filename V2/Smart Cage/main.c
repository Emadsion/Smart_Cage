/*
 * GccApplication5.c
 *
 * Created: 25-Mar-21 3:47:33 PM
 * Author : Muhammad Emad & Salaheldin Attia & 3 others
 */ 

#define F_CPU 16000000UL //set speed at 16MHz
/*Include Library*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*Include ASCG*/
#include "ASCG_interface.h"
                    
int main(void)
{
	LCD_Initialization();
	LCD_Print_Welcome_msg();
    while (1) 
    {	
		CheckFood();
		CheckWater();
		CheckCleaning();
		CheckTemp();
    }
}
