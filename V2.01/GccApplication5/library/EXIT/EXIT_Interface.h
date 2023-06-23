
#ifndef 	EXIT_INTERFACE_H
#define 	EXIT_INTERFACE_H



//Initialize INT0
void EXIT0_VidInit(void);
//Initialize INT1
void EXIT1_VidInit(void);
//Initialize INT2
void EXIT2_VidInit(void);

//Enable Global Interrupt
void GIE_VidEnable(void);

//Disable Global Interrupt
void GIE_VidDisable(void);

void EXIT0_VoidSetCallBack(void (*Ptr0)(void));
void EXIT1_VoidSetCallBack(void (*Ptr1)(void));
void EXIT2_VoidSetCallBack(void (*Ptr2)(void));



#endif