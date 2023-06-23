/**************************************************************/
/***********     Author    : T5 software department  **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_interface        **********/
/**************************************************************/
#ifndef ASCG_INTERFACE_H_
#define ASCG_INTERFACE_H_


extern void LCD_Print_Cage_Status ();
extern void LCD_Print_Welcome_msg ();
extern void CountUP(void);
extern void CheckFood(void);
extern void CheckWater(void);
extern void CheckCleaning(void);
extern void CheckTemp(void);
extern void Feeder(void);
extern void Water(void);
extern void Clean(void);
extern void Temp(u8 TempCondition);
extern void ASCG_vidPrintWeatherStatus(void);


#endif