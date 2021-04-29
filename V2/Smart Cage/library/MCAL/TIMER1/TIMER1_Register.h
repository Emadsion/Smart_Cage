#ifndef TIMER1_REGISTER_H_
#define TIMER1_REGISTER_H_


#define TCCR1		*((volatile u16 *) 0x4E)
#define TCNT1		*((volatile u16 *) 0x4C)
#define OCR1A		*((volatile u16 *) 0x4A)
#define OCR1B		*((volatile u16 *) 0x48)
#define ICR1			*((volatile u16 *) 0x46)
#define TIMSK			*((volatile u8 *) 0x59)
#define TIFR			*((volatile u8 *) 0x48)
#define SREG			*((volatile u8 *) 0x5F)

#define GIE				7
#define COM1B0		12
#define COM1B1		13
#define COM1A0		14
#define COM1A1		15
#define WGM12		3
#define WGM13		4
#define WGM10		8
#define WGM11		9

#define CS10			0
#define CS11			1
#define CS12			2

#define TOIE1			2
#define OCIE1B		3
#define OCIE1A		4
#define TICIE1		5


static void (* TIMER1_PVidCallBack)(void) = NULL;

void __vector_7(void) __attribute__((signal));





#endif