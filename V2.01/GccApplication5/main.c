/*
 * GccApplication5.c
 *
 * Created: 25-Mar-21 3:47:33 PM
 * Author : Team 5 software department
 */ 

#define F_CPU 16000000UL //set speed at 16MHz


#include <util/delay.h> 
#include <avr/pgmspace.h>



/*Include Libraries*/
#include "BIT_MATH.h"
#include "STD_TYPES.h"
##include "ASCG_Interface.h"
#include "ASCG_Config.h"

/*Include MCAL*/
#include "library/DIO/DIO_Interface.h"
#include "library/EXIT/EXIT_Interface.h"
#include "library/TIMER0/Timer_Interface.h"
#include "library/TIMER1/Timer1_Interface.h"
/*Include HAL*/
#include "library/LCD/lcd_hd44780_avr.h"
#include "library/DHT11/DHT11_Interface.h"






static u32 GenralCounter=0;
static u32 FoodCounter=0;
static u32 WaterCounter=0;
static u32 CleanCounter=0;
static u16 TempCounter=0;
static u8 CleanDuration=0;




void LCD_Print_Cage_Status ()
{
	LCDClear();
	LCDWriteStringXY(0,First_Line,"Tempe:");
	LCDWriteInt(5,2);

	LCDWriteStringXY(0,Second_Line,"Humidity:");
	LCDWriteInt(89,2);
}


void LCD_Print_Welcome_msg (){
	
	LCDWriteStringXY(5,First_Line,"Welcome")
	_delay_ms(500);
	LCDWriteStringXY(4,Second_Line,"SmartCage")
	_delay_ms(1000);
	LCDClear();
	
}


                                  
int main(void)
{
	
	//INPUTS
	DIO_VidSetPinDirection(INT0Button_PORT,INT0Button_PIN,INPUT);//INT0	Feeder
	DIO_VidSetPinDirection(INT1Button_PORT,INT1Button_PIN,INPUT);//INT1	Water
	DIO_VidSetPinDirection(INT2Button_PORT,INT2Button_PIN,INPUT);//INT2	Cleaning
	DIO_VidSetPinDirection(TempButton_PORT,TempButton_Pin,INPUT);//Push button	Temp
	DIO_VidSetPinDirection(WaterSensor1_PORT,WaterSensor1_PIN,INPUT); //Water Sensor 1
	DIO_VidSetPinDirection(WaterSensor2_PORT,WaterSensor2_PIN,INPUT); //Water Sensor 2
	DIO_VidSetPinDirection(LimitSwitch_PORT,LimitSwitch_PIN,INPUT); //Feeder Limit Switch
	
	//OUTPUTS
	
	DIO_VidSetPinDirection(IR_PORT, IR_PIN, OUTPUT);		//IR
	DIO_VidSetPinDirection(Fan1_PORT, Fan1_PIN, OUTPUT);	//FAN1
	DIO_VidSetPinDirection(Belt_PORT, Belt_PIN, OUTPUT);	//Belt1
	DIO_VidSetPinDirection(Belt2_PORT, Belt2_PIN, OUTPUT);	//Belt2
	DIO_VidSetPinDirection(Peltir1_PORT, Peltir1_PIN, OUTPUT); //Peltir1
	DIO_VidSetPinDirection(Peltir2_PORT, Peltir2_PIN, OUTPUT); //Pelrit2
	DIO_VidSetPinDirection(Servo_PORT, Servo_PIN, OUTPUT); //Servo
	DIO_VidSetPinDirection(Lamp_PORT, Lamp_PIN, OUTPUT); //Lamp
	DIO_VidSetPinDirection(Valve_PORT, Valve_PIN, OUTPUT); //Vavle
	DIO_VidSetPinDirection(CurtainUp_PORT, CurtainUp_PIN, OUTPUT); //Curtain Up
	DIO_VidSetPinDirection(CurtainDn_PORT, CurtainDn_PIN, OUTPUT); //Curtain Dn
	DIO_VidSetPinDirection(FeedServo_PORT,FeedServo_PIN,OUTPUT);   //FeedingServo
	
	
	//Driver Initialization
	TIMER0_VidInit();
	TIMER1_VoidInit();
	TIMER1_VoidSetCallBack(&CountUP);
	EXIT0_VidInit();
	EXIT1_VidInit();
	EXIT2_VidInit();
	EXIT0_VoidSetCallBack(&Feeder);
	DIO_VidSetPinValue(FeedServo_PORT,FeedServo_PIN,HIGH);
	EXIT1_VoidSetCallBack(&Water);
	EXIT2_VoidSetCallBack(&Clean);
	
	
	LCDInit(LS_NONE);
	LCDClear();
	LCD_Print_Welcome_msg ();
	
	
	
    while (1) 
    {
		
		CheckFood();
		CheckWater();
		CheckCleaning();
		CheckTemp();			
    }
}

/*
 *
 * Ticking one second for all Smart cage process to reach the timing for each process
 *
 */
void CountUP(void)
{
	FoodCounter++;
	WaterCounter++;
	CleanCounter++;
	TempCounter++;
	GenralCounter++;
}


/*
 * Every 3 hours water is served for our animal by activating watering mechanism
 * then resting Food counter to begin another 6 hours
 *
 */
void CheckFood(void)
{
	if(FoodCounter >= Six_Hours)
	{
		Feeder();
		FoodCounter=0;
	}
}

/*
 * Every 3 hours water is served for our animal by activating watering mechanism
 * Then resting Water counter to begin another 3 hours
 *
 */

void CheckWater(void)
{
	if(WaterCounter >= Three_Hours)
	{
		Water();
		WaterCounter = 0;
	}
	
}
/*
 * Every 12 hours Cleaning the cage operations starts by activating our cleaning mechanism
 * Then resting Clean counter to begin another 12 hours
 *
 */
void CheckCleaning(void)
{
	if(CleanCounter >= Twelve_Hours)
	{
		CleanDuration = GenralCounter;
		Clean();
		CleanCounter=0;
	}
	if(CleanDuration > 0)
		clean();
}



/*
 * Updating the tempreature sensor every 30 minutes 
 * Setting (cooler / Heater) to operates according to the temprture condition
 *
 */
void CheckTemp(void)
{
	
	if (TempCounter == Thirty_min)
	{
		DHT11_GetValues();
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
	ASCG_vidPrintWeatherStatus();
	TempCounter = 0;
}

/*
 * Activating servo motor at 90 angle to open up for food to come down from food box  
 * when the plate is full (Limit siwtch in on) the servo will close the food box
 *
 */
void Feeder(void)
{	
	
	while(!DIO_u8GetPinValue(PORTA,LimitSwitch));
	{
		 TIMER0_VoidDutyCycle(Angle_90); //-90 angle
	}
	TIMER0_VoidDutyCycle(Angle_0);//0 angle
	FoodCounter=0;
}

/*
 * Activating watering operation by checking on the L_sensor and U_sensor   
 * The watering will stop when it reaches U_sensor
 *
 */
void Water(void)
{
	if(DIO_u8GetPinValue(WaterSensor1_PORT,WaterSensor1_PIN) && DIO_u8GetPinValue(WaterSensor2_PORT,WaterSensor2_PIN))
	{
		DIO_VidSetPinValue(Valve_PORT,Valve_PIN,HIGH);
		while(!(DIO_u8GetPinValue(WaterSensor2_PORT,WaterSensor2_PIN)));
		DIO_VidSetPinValue(Valve_PORT,Valve_PIN,LOW);
	}
}

/*
 *    
 * Activating Cleaning operation 
 *
 */
void Clean(void)
{
	DIO_VidSetPinValue(Belt_PORT,Belt_PIN,HIGH);
	
	if(GenralCounter - CleanDuration >= 10) // 10 seconds is the time needed to clean the cage
	{
		DIO_VidSetPinValue(Belt_PORT,Belt_PIN,LOW);
		CleanDuration = 0;
	}
}


/*Setting Cage condition for every state of the weather*/
void Temp(u8 TempCondition)
{
	switch(TempCondition)
	{
		case HIGH:
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,LOW);
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,LOW);
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,LOW);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,High);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,HIGH);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,HIGH);
		break;
		case LOW:
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,LOW);
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,HIGH);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,HIGH);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,LOW);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,LOW);
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,HIGH);
		break;
		case VeryLow:
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,HIGH);
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,HIGH);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,HIGH);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,LOW);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,HIGH);
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,LOW);
		break;
		case Moderate:
		DIO_VidSetPinValue(Lamp_PORT,Lamp_PIN,LOW);
		DIO_VidSetPinValue(Peltir2_PORT,Peltir2_PIN,LOW);
		DIO_VidSetPinValue(Fan1_PORT,Fan1_PIN,LOW);
		DIO_VidSetPinValue(Peltir1_PORT,Peltir1_PIN,LOW);
		DIO_VidSetPinValue(Fan2_PORT,Fan2_PIN,LOW);
		DIO_VidSetPinValue(CurtainDn_PORT,CurtainDn_PIN,LOW);
		DIO_VidSetPinValue(CurtainUp_PORT,CurtainUp_PIN,HIGH);
		break;
	}
}

