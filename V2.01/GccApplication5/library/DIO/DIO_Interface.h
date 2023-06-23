
#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

//PORT
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

//PIN_NUM
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

//PIN_DIRECTION
#define INPUT  0
#define OUTPUT 1

//PIN VALUE
#define LOW  0
#define HIGH 1




// IO .....

void DIO_VidSetPinDirection(u8 port,u8 pin_Num,u8 state);


void DIO_VidSetPortDirection(u8 port,u8 Direction);


void DIO_VidSetPinValue (u8 port,u8 pin_Num,u8 value);


void DIO_VidSetPortValue(u8 port,u8 Value);


u8 DIO_u8GetPinValue(u8 port,u8 pin_Num);


void DIO_ToggelPin(u8 port,u8 pin_Num);


#endif
