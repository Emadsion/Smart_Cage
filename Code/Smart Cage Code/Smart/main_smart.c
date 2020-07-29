/*
 * Smart.c
 *
 * Created: 17-Jul-20 4:23:52 PM
 *  Author: Salah Attia, Muhammed Emad, Ahmed Elsewedey, Abdelrahman Osama 
 */ 

#include "head_smart.h"



int main()
{
/*Pins Configuration____________________________________________________________________________ */
  
		DDRC = 0xFF;  //set all PinC as Outputs
		DDRD = 0x00;  //set all PinD as Inputs
		DDRB &= ~(1 << PB2);
	
	
		
/* LCD Initialization And Welcome Screen___________________________________________________________*/
		LCDInit(LS_NONE);  //Initialize the LCD in 4-Pins, and No Cursor Mode
		LCD_Print_Welcome_msg ();
		
		

/* Interrupt Configuration___________________________________________________________________________ */
		
		/*3-Clear Flags*/
		GIFR &= ~(1 << INTF0 ) & ~(1 << INTF1 )  & ~(1 << INTF2 );
		/*1-Enable Interrupts*/
		GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);  //Enable Interrupt 0,1, and 2
		/*2-Signal Mode Configuration*/
		MCUCR |= (1 << ISC10) | (1 << ISC11)|(1 << ISC00) | (1 << ISC01); //Activating Int 0, and 1 at Rising Edge
		MCUCSR |= (1 << ISC2);    //Activating Int 2 at Rising Edge
		/*4-Global Interrupt Enable*/
		#define SREG *(volatile unsigned char *)(0x5F)
		#define GIE_Bit_Numb_In_SREG 7
	    SREG |= (1 << GIE_Bit_Numb_In_SREG );		
		_delay_ms(10);
				
/*Timer Initialization and Configuration_______________________________________________________________*/		
		/*Start Timer1 in CTC Mode Chanel B*/
		TCCR1A= 0b00000000;         //Timer/Counter1 Control Register-Channel A  (Disable all the Channel)
		TCCR1B |= (1 << WGM12)|(1 << CS11);     //Timer/Counter1 Control Register-Channel B  (Enable in Clear On Compare Mode, and with a 8-bit prescaler)
		/*set value to compare match at*/
		OCR1A = 10000;             //When TCNT1 Matches this value, an OC interrupt will happen every 1ms, and TCNT1 will be cleared
		/*Enable The used Interrupt*/
		TIMSK |= (1 << OCIE1A) ;   //Timer/Counter Interrupt Mask Register, Enable -Channel B, On Compare Interrupt-
		
			
	
	

	while(1)
	{
	
	    DHT111_Get_Values();  //keep getting Data From The DHT11 Sensor
		LCD_Print_Cage_Status ();  //Keep Printing Data On the LCD
		DHT11_Check_temp();       //Keep Checking temp, and Controlling Cooling system
		
		TIMER1_check_cleaning();
		TIMER1_check_watering();
		TIMER1_check_feeding();
		
	}
	return 0;
}


  
  ISR(INT2_vect) //Cleaning 
  {
	  PORTC |= (1<<PC3);
	  _delay_ms(2000);
	  count_food = count_food + 200;
	  count_water = count_water + 200;
	   PORTC &= ~(1 << PC3);
	  
  }
  
  ISR(INT0_vect) // feeder
  {
	  
	 while (!(PIND & (1<<PD7)))
	  {
		  PORTC ^= (1 << PC0);
		  _delay_ms(2000);
		  count_water = count_water + 200;
		  count_clean = count_clean + 200;
		  PORTC ^= (1 << PC0);
		  
	  }
	  
  }
  ISR(INT1_vect) // Water valves
  {
	  
	  PORTC |= (1 << PC2);
	  _delay_ms(3000);
	  count_food = count_food + 200;
	  count_clean = count_clean + 200;
	  PORTC &= ~(1 << PC2);
	  while (!(PIND & (1<<PD6)))
	  {
		  PORTC |= (1 << PC1);
	  }
	  
	  PORTC &= ~(1 << PC1);
	  
  }
  
  
  ISR(TIMER1_COMPA_vect)
  {
	  count_water++;
	  count_clean++;
	  count_food++;

  }  //END Interrupt
  







