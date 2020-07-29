/*
 * Head_smart.h
 *
 * Created: 24-Jul-20 10:59:05 PM
 *  Author: Salah Attia, Muhammed Emad, Ahmed Elsewedey, Abdelrahman Osama 
 */ 


#ifndef HEAD_SMART_H_
#define HEAD_SMART_H_

#define F_CPU 8000000UL //set speed at 8MHz
#include <avr/io.h> //Main avr library
#include <util/delay.h> //delay library
#include <avr/interrupt.h>  //Interrupt Library
#include <avr/pgmspace.h>
#include "library/DHT11/DHT11.h"
#include "library/lcd/lcd_hd44780_avr.h"

uint8_t Pules=0, tempreature_flag = 0,Integer_Humidty,Decimal_Humidty,Integer_Temp,Decimal_Temp,Check_Sum;
int count_food = 0, count_water = 0, count_clean = 0;



#define Clean_M PC3

void LCD_Print_Cage_Status ();
void LCD_Print_Welcome_msg ();
void DHT11_Check_temp();

void TIMER1_check_cleaning();
void TIMER1_check_watering();
void TIMER1_check_feeding();



void LCD_Print_Cage_Status (){
LCDWriteStringXY(0,First_Line,"Tempe:");
LCDWriteInt(Integer_Temp,2);

LCDWriteStringXY(0,Second_Line,"Humidity:");
LCDWriteInt(Integer_Humidty,2);
}


void LCD_Print_Welcome_msg (){
	
		LCDWriteStringXY(5,First_Line,"Welcome")
		_delay_ms(500);
		LCDWriteStringXY(4,Second_Line,"Smart Cage")
		_delay_ms(1000);
		LCDClear();
		
}

void DHT11_Check_temp(){
	if(PIND & (1<<PD1))
	{
		if(!tempreature_flag )
		{
			PORTC &= ~(1<< PC6);
			_delay_ms(500);
			PORTC |= (1 << PC6) ; //Heating
			PORTC |= (1<< PC4); //Curtain on
			_delay_ms(1000);
			PORTC &= ~(1<< PC4);// Curtain off
			tempreature_flag = 1;//activate temperature flag to execute only one time
		}//End temperature flag if
	}//End if
	else if(PIND & (1<<PD0))
	{
			if(!tempreature_flag)
			{
				_delay_ms(500);
				PORTC &= ~(1<< PC7);
				PORTC |= (1 << PC7); //Tarawa
				PORTC |= (1<< PC4); //Curtain on
				_delay_ms(1000);
				PORTC &= ~(1<< PC4);// Curtain off
				tempreature_flag = 1;
			}//End temperature flag if
	}//End else if 
	else if(Integer_Temp < 18)
	{
		if(!tempreature_flag )
		{
			PORTC |= (1 << PC6) ; //Heating
			PORTC |= (1<< PC4); //Curtain on
			_delay_ms(1000);
			PORTC &= ~(1<< PC4);// Curtain off
			tempreature_flag = 1;//activate temperature flag to execute only one time
		}//End temperature flag if
	}//End if
	else if(Integer_Temp > 25)
	{
		if(!tempreature_flag)
		{
			PORTC |= (1 << PC7); //Tarawa
			PORTC |= (1<< PC4); //Curtain on
			_delay_ms(1000);
			PORTC &= ~(1<< PC4);// Curtain off
			tempreature_flag = 1;
		}//End temperature flag if
	
	}//End Else if
	else
	{
		PORTC &= ~(1 << PC6);
		PORTC &= ~(1 << PC7);
		tempreature_flag = 0;
	}
}

void TIMER1_check_cleaning()
{
													/*CLEANING*/
	if (count_clean > 1000)
	{
		PORTC |= (1 << Clean_M);
		if (count_clean > 1200)
		{
			PORTC &= ~(1 << Clean_M);
			count_clean = 0;
		} //END if
	} //END outer if
} //END function

void TIMER1_check_watering()
{
/*WATERING___________________________________________________________________________________________________*/
	if (count_water > 2000)
	{
		if (!(PIND & (1 << PD6)))
		{ 
			PORTC |= (1 << PC2);
			_delay_ms(2000);
			PORTC &= ~(1 << PC2);
		} //End if
			 
		else
		{
			count_water = 0;
		}	 
		
		while(!(PIND & (1 << PD6)))
		{
			PORTC |= (1 << PC1); 
		 }   //End While
			 
		PORTC &= ~(1 << PC1);
		count_water = 0;
			 
	} //End IF
	
}//END function
void TIMER1_check_feeding()
{
																	 /*FEEDING*/	 
	if (count_food > 1500)
	{
		while(!(PIND & (1 << PD7))) //while (the PD7 is LOW)
		{
			PORTC |= (1 << PC0);   //Start Feeding
		}//END while
			 
		PORTC &= ~(1 << PC0);      //Stop feeding
		count_food = 0;
	}//END if
}//END function

#endif /* INCFILE1_H_ */