/*
 * config.h
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_


/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA A		//Port AVR's PA0-PA3 are connected to LCD's DB4-DB7
#define LCD_DATA_POS 3 


#define LCD_RS A		//Register Select signal (RS)-> PA4
#define LCD_RS_POS	PA1

#define LCD_RW A		//Read/Write signal (R/W) ->PA5
#define LCD_RW_POS	PA0

#define LCD_E A			//Enable/strobe signal (E)-> PA6
#define LCD_E_POS	PA2	//Position of enable in above port



/***********************************************

LCD Type Selection


************************************************/
#define LCD_TYPE_162	//For 16 Chars by 2 lines


//************************************************


#endif /* CONFIG_H_ */