#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H




void TIMER0_VidInit(void);
void TIMER0_VoidDutyCycle(u8 Duty);
void TIMER0_VoidSetCallBack(void (*Ptr0)(void));


#endif
