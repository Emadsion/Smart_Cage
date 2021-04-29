#ifndef TIMER_REGISTER_H
#define TIMER_REGISTER_H

#define TCCR0		*((volatile u8 *) 0x53)
#define TCNT0		*((volatile u8 *) 0x52)
#define OCR0		*((volatile u8 *) 0x5C)
#define TIMSK		*((volatile u8 *) 0x59)
#define TIFR		*((volatile u8 *) 0x58)

#define SREG		*((volatile u8 *) 0x5F) //don't forget it

#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define WGM00	6
#define COM00	4
#define	COM01	5
#define TOIE0	0
#define OCIE0	1
#define GIE 	7 //don't forget it

static void (* TIMER0_PVidCallBack)(void) = NULL;

void __vector_11(void) __attribute__((signal));












#endif
