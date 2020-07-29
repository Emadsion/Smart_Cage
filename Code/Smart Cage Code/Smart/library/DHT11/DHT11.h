#ifndef _DHT11_H
#define _DHT11_H

extern uint8_t Pules, Integer_Humidty,Decimal_Humidty,Integer_Temp,Decimal_Temp,Check_Sum;


void Request();	
void Response();
uint8_t Receive_data();
void DHT111_Get_Values();

#define DHT11_PIN 5


#endif