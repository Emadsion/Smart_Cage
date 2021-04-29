/**************************************************************/
/***********     Author    :                         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_interface        **********/
/**************************************************************/
#ifndef ASCG_INTERFACE_H_
#define ASCG_INTERFACE_H_


void LCD_Initialization();
void LCD_Print_Cage_Status ();
void LCD_Print_Welcome_msg ();
void CountUP();
void CheckFood();
void CheckWater();
void CheckCleaning();
void CheckTemp();
void Feeder();
void Water();
void Clean();
void Temp(u8 Condition);
void Set_IP();
void Set_OP();
void Set_Peripherals();







#endif