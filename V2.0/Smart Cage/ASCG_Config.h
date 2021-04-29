/**************************************************************/
/***********     Author    :                         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_Config           **********/
/**************************************************************/
#ifndef ASCG_CONFIG_H_
#define ASCG_CONFIG_H_



//PORTA
#define IR_PORT				PORTA
#define IR_PIN				7

//PORTB
#define LimitSwitch_PORT	PORTB
#define LimitSwitch_PIN		0
#define Fan2_PORT			PORTB
#define Fan2_PIN			1
#define LimitSwitch_PIN		0
#define INT2Button_PORT		PORTB
#define INT2Button_PIN		2
#define Servo_PORT			PORTB
#define Servo_PIN			3
//PB4?
#define TempButton_PORT		PORTB
#define TempButton_Pin		5
#define WaterSensor1_PORT	PORTB
#define WaterSensor1_PIN	6
#define WaterSensor2_PORT	PORTB
#define WaterSensor2_PIN	7


//PORTC
//C0?
#define Lamp_PORT			PORTC
#define Lamp_PIN			1
#define Peltir2_PORT		PORTC
#define Peltir2_PIN			2

#define Peltir1_PORT		PORTC
#define Peltir1_PIN			3
#define Valve_PORT			PORTC
#define Valve_PIN			4



//PORTD
#define Belt_PORT			PORTD
#define Belt_PIN			0
#define Belt2_PORT			PORTD
#define Belt2_PIN			1
#define INT0Button_PORT		PORTD
#define INT0Button_PIN		2
#define INT1Button_PORT		PORTD
#define INT1Button_PIN		3
#define CurtainUp_PORT		PORTD
#define CurtainUp_PIN		5
#define CurtainDn_PORT		PORTD
#define CurtainDn_PIN		6
#define Fan1_PORT			PORTD
#define Fan1_PIN			7


#define VeryLow			2
#define Moderate		3

#endif
