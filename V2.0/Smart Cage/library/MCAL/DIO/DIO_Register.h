#ifndef _DIO_REGISTER_H_
#define _DIO_REGISTER_H_


//PORTA...
#define DDRA   *((u8*)0x3A)
#define PORTA  *((u8*)0x3B)
#define PINA   *((u8*)0x39)

//PORTB...
#define DDRB   *((u8*)0x37)
#define PORTB  *((u8*)0x38)
#define PINB   *((u8*)0x36)

//PORTC
#define DDRC   *((u8*)0x34)
#define PORTC  *((u8*)0x35)
#define PINC   *((u8*)0x33)

//PORTD
#define DDRD   *((u8*)0x31)
#define PORTD  *((u8*)0x32)
#define PIND   *((u8*)0x30)
#endif
