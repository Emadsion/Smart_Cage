#ifndef 	EXIT_REGISTER_H
#define 	EXIT_REGISTER_H



#define MCUCR			*((volatile u8 *) 0x55)
#define MCUCSR			*((volatile u8 *) 0x54)
#define GICR				*((volatile u8 *) 0x5B)
#define GIFR				*((volatile u8 *) 0x5A)
#define SREG				*((volatile u8 *) 0x5F)



#define INT0		6
#define INT1		7
#define INT2		5
#define INTF2		5

#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3
#define ISC2		6
#define GIE 		7



static void (* EXIT0_PVidCallBack)(void) = NULL;
static void (* EXIT1_PVidCallBack)(void) = NULL;
static void (* EXIT2_PVidCallBack)(void) = NULL;
//this function is not called in the software but  in hardware so we need to tell the compiler not to delete it 
void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));



#endif