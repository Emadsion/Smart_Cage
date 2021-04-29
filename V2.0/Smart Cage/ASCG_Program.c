/**************************************************************/
/***********     Author    :                         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_Prog             **********/
/**************************************************************/

#define F_CPU 16000000UL //set speed at 16MHz

/*Include Library*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/*Include HAL*/
#include "library/HAL/LCD/lcd_hd44780_avr.h"
#include "library/HAL/DHT11/DHT11_Interface.h"
/*Include MCAL*/
#include "library/MCAL/DIO/DIO_Interface.h"
#include "library/MCAL/EXIT/EXIT_Interface.h"
#include "library/MCAL/TIMER0/TIMER_Interface.h"
#include "library/MCAL/TIMER1/TIMER1_Interface.h"
#include "library/MCAL/WDT/WDT_Interface.h"

#include "ASCG_interface.h"
#include "ASCG_Config.h"
#include <util/delay.h>

u32 FoodCounter=0;
u32 WaterCounter=0;
u32 CleanCounter=0;
u16 TempCounter=0;
 

void Set_IP()
{
	//INPUTS
	
	DIO_VidSetPinDirection(INT0Button_PORT,INT0Button_PIN,INPUT);//INT0	Feeder
	DIO_VidSetPinDirection(INT1Button_PORT,INT1Button_PIN,INPUT);//INT1	Water
	DIO_VidSetPinDirection(INT2Button_PORT,INT2Button_PIN,INPUT);//INT2	Cleaning
	DIO_VidSetPinDirection(TempButton_PORT,TempButton_Pin,INPUT);//Push button	Temp
	DIO_VidSetPinDirection(WaterSensor1_PORT,WaterSensor1_PIN,INPUT); //Water Sensor 1
	DIO_VidSetPinDirection(WaterSensor2_PORT,WaterSensor2_PIN,INPUT); //Water Sensor 2
	DIO_VidSetPinDirection(LimitSwitch_PORT,LimitSwitch_PIN,INPUT); //Feeder Limit Switch
	
}
void Set_OP()
{
	//OUTPUTS
	
	DIO_VidSetPinDirection(IR_PORT, IR_PIN, OUTPUT);		//IR
	DIO_VidSetPinDirection(Fan1_PORT, Fan1_PIN, OUTPUT);	//FAN1
	DIO_VidSetPinDirection(Fan2_PORT, Fan2_PIN, OUTPUT);	//FAN2
	DIO_VidSetPinDirection(Belt_PORT, Belt_PIN, OUTPUT);	//Belt1
	DIO_VidSetPinDirection(Belt2_PORT, Belt2_PIN, OUTPUT);	//Belt2
	DIO_VidSetPinDirection(Peltir1_PORT, Peltir1_PIN, OUTPUT); //Peltir1
	DIO_VidSetPinDirection(Peltir2_PORT, Peltir2_PIN, OUTPUT); //Pelrit2
	DIO_VidSetPinDirection(Servo_PORT, Servo_PIN, OUTPUT); //Servo
	DIO_VidSetPinDirection(Lamp_PORT, Lamp_PIN, OUTPUT); //Lamp
	DIO_VidSetPinDirection(Valve_PORT, Valve_PIN, OUTPUT); //Valve
	DIO_VidSetPinDirection(CurtainUp_PORT, CurtainUp_PIN, OUTPUT); //Curtain Up
	DIO_VidSetPinDirection(CurtainDn_PORT, CurtainDn_PIN, OUTPUT); //Curtain Dn
	
}
void Set_Peripherals()
{
	//Driver Initialization
	TIMER0_VidInit();
	TIMER1_VoidInit();
	TIMER1_VoidSetCallBack(&CountUP);
	EXIT0_VidInit();
	EXIT1_VidInit();
	EXIT2_VidInit();
	EXIT0_VoidSetCallBack(&Feeder);
	EXIT1_VoidSetCallBack(&Water);
	EXIT2_VoidSetCallBack(&Clean);
}

void LCD_Initialization()
{
	LCDInit(LS_NONE);
	LCDClear();
}
void LCD_Print_Cage_Status()
{
	LCDClear();
	LCDWriteStringXY(0,First_Line,"Tempe:");
	LCDWriteInt(Integer_Temp,2);

	LCDWriteStringXY(0,Second_Line,"Humidity:");
	LCDWriteInt(Integer_Humidty,2);
}


void LCD_Print_Welcome_msg()
{
	
	LCDWriteStringXY(5,First_Line,"Welcome")
	_delay_ms(500);
	LCDWriteStringXY(4,Second_Line,"SmartCage")
	_delay_ms(2000);
	LCDClear();
	
}


void CountUP()
{
	FoodCounter++;
	WaterCounter++;
	CleanCounter++;
	TempCounter++;
}

void CheckFood()
{
	if(FoodCounter == 10)
	{
		Feeder();
		FoodCounter=0;
	}
	
}

void CheckWater()
{
	if(WaterCounter == 20)
	{
		Water();
		WaterCounter = 0;
	}
	
}
void CheckCleaning()
{
	if(CleanCounter == 30)
	{
		Clean();
		CleanCounter=0;
	}
	
}

void CheckTemp()
{
	if (TempCounter == 300)
	{
		WD_TimerEnable();
		DHT11_GetValues();
		WD_TimerDisable();
		if(Integer_Temp > 25)
		{
			Temp(HIGH);
		}
		else if(Integer_Temp < 20 && Integer_Temp > 15)
		{
			Temp(LOW);
		}
		else if(Integer_Temp < 15)
		{
			Temp(VeryLow);
		}
		else
		{
			Temp(Moderate);
		}
	}
}

void Feeder()
{
	LCDClear();
	LCDWriteStringXY(0,First_Line,"Feeder is starting now");
	while(!DIO_u8GetPinValue(LimitSwitch_PORT,LimitSwitch_PIN));
	{
		 TIMER0_VoidDutyCycle(30); //-90 angle
	}
	 TIMER0_VoidDutyCycle(46);//0 angle
	 FoodCounter=0;
	 LCDClear();
	 _delay_ms(100);
	 LCD_Print_Cage_Status();
}
void Water()
{
	if(DIO_u8GetPinValue(WaterSensor1_PORT,WaterSensor1_PIN) && DIO_u8GetPinValue(WaterSensor2_PORT,WaterSensor2_PIN))
	{
		LCDClear();
		LCDWriteStringXY(0,First_Line,"Watring is starting now");
		DIO_VidSetPinValue(Valve_PORT,Valve_PIN,HIGH);
		while(!(DIO_u8GetPinValue(WaterSensor2_PORT,WaterSensor2_PIN)));
		DIO_VidSetPinValue(Valve_PORT,Valve_PIN,LOW);
	}
	WaterCounter = 0;
	 LCDClear();
	_delay_ms(100);
	LCD_Print_Cage_Status();
}
void Clean()
{
	LCDClear();
	LCDWriteStringXY(0,First_Line,"Cleaning is starting now");
	DIO_VidSetPinValue(Belt_PORT,Belt_PIN,HIGH);
	_delay_ms(200);
	while(!DIO_u8GetPinValue(IR_PORT,IR_PIN))
	DIO_VidSetPinValue(Belt_PORT,Belt_PIN,LOW);
	_delay_ms(100);
	DIO_VidSetPinValue(Belt2_PORT,Belt2_PIN,HIGH);
	_delay_ms(200);
	while(!DIO_u8GetPinValue(IR_PORT,IR_PIN));
	DIO_VidSetPinValue(Belt2_PORT,Belt2_PIN,LOW);
	
	CleanCounter = 0;
	LCDClear();
	_delay_ms(100);
	LCD_Print_Cage_Status();
}

void Temp(u8 Condition)
{
	switch(Condition)
	{
		case HIGH:
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,HIGH);
		_delay_ms(3000);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,HIGH);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,HIGH);
		break;
		case LOW:
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,HIGH);
		_delay_ms(3000);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,LOW);
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,HIGH);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,HIGH);
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,LOW);
		break;
		case VeryLow:
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,HIGH);
		break;
		case Moderate:
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,HIGH);
		_delay_ms(3000);
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,LOW);
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,LOW);
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,LOW);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,LOW);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,LOW);
		break;
		_delay_ms(100);
	}
	
}





