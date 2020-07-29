#define F_CPU 8000000UL //set speed at 8MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "DHT11.h"





//Used Functions_________________________________________________________________________________________________________________

												/* Microcontroller send start pulse/request */

void Request()				
{
	DDRD |= (1<<DHT11_PIN);
	PORTD |= (1<<DHT11_PIN); //for some reason this solved the problem (probably to insure that the sensor is working probably)
	_delay_ms(10);
	PORTD &= ~(1<<DHT11_PIN); 
	_delay_ms(20); // Waiting time 
	PORTD |= (1<<DHT11_PIN); 
}

														/* receive response from DHT11 */

void Response()				
{
	DDRD &= ~(1<<DHT11_PIN);
	//Wait till hight pulse pass(just Insurance that the sensor is not passing any thing from the last attempts )
	while(PIND & (1<<DHT11_PIN)); 
	/*Sensor send low pulse then high pulse which insures
	that it received the request from Micro controller*/
	while((PIND & (1<<DHT11_PIN))==0); 
	while(PIND & (1<<DHT11_PIN)); 
}


void DHT111_Get_Values(){
	
		Request();		/* send start pulse */
		Response();		/* receive response */
		Integer_Humidty=Receive_data();	/* store first eight bit as Integer humidity*/
		Decimal_Humidty=Receive_data();	/* store next eight bit as Decimal humidity */
		Integer_Temp=Receive_data();	/* store next eight bit in Integer Temperature*/
		Decimal_Temp=Receive_data();	/* store next eight bit in Decimal Temperature */
		Check_Sum=Receive_data();/* store next eight bit in CheckSum */
		_delay_ms(10); // for stability and error delays
}






																/* receiving data */
uint8_t Receive_data()			
{
	for (int i=0; i<8; i++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		Pules = (Pules<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		Pules = (Pules<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return Pules;
}


