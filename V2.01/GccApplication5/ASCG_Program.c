/**************************************************************/
/***********     Author    : T5 software department  **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_Prog             **********/
/**************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Lcd_interface.h"


#include "ASCG_interface.h"
#include "ASCG_Private.h"

#include "avr/delay.h"
#include "ASCG_Config.h"

void ASCG_vidPrintWeatherStatus(void)
{
	/*Display Weather */
	LCD_vidWriteCommand(LCD_Clr_Display);
	/*Row 0, Col 0*/
	LCD_vidGoTo(0, 0);
	LCD_vidWriteString("Tempe:");
	LCD_VidWriteNum(Integer_Temp);
	/*Row 1, Col 0*/
	LCD_vidGoTo(1, 0);
	LCD_vidWriteString("Humidity:");
	LCD_VidWriteNum(Integer_Humidty);
}



