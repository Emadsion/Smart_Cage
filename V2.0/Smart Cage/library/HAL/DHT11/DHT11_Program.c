/**************************************************************/
/***********     Author    :                         **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  30-11-2020             **********/
/***********     File      :  DHT11_Prog             **********/
/**************************************************************/
#define F_CPU 16000000UL
#include "../../../STD_TYPES.h"
#include "../../../BIT_MATH.h"

#include "../../MCAL/DIO/DIO_Interface.h"


#include "DHT11_interface.h"
#include "DHT11_Config.h"
#include "DHT11_Private.h"




#include "util/delay.h"



//Used Functions_________________________________________________________________________________________________________________
/* Microcontroller send start pulse/request */
u8* pu8InitAndReceiveData(void)
{
/* 0-Declare Some variables*/
	static u8 ReceivedData[5]={0};



/* 1-Start THE DHT11 From Low-power-consumption Mode to Running Mode*/
	/*Make the Pin OUTPUT to send start signal*/
	DIO_VidSetPinDirection(DHT11_PORT,DHT11_PIN,OUTPUT); 
	/*send high to make the DHT11 Ready to receive LOW (Start Signal starts with LOW)*/
    DIO_VidSetPinValue (DHT11_PORT,DHT11_PIN,HIGH);
	_delay_ms(10);
	/*Send Start Signal*/
	DIO_VidSetPinValue (DHT11_PORT,DHT11_PIN,LOW);
	_delay_ms(20); // Waiting time
	DIO_VidSetPinValue (DHT11_PORT,DHT11_PIN,HIGH); //after about 20-40 us the DHT11 Should response
	//_delay_us(35); //wait until the DHT11 detects the start signal and starts to responce
	//DIO_SetPinValue(DHT11_PORT, DHT11_PIN, LOW);


/* 2-receive response from DHT11 to make sure that it is converted into Running-mode */
	/*Make the Pin INPUT to receive response signal*/
	DIO_VidSetPinDirection(DHT11_PORT,DHT11_PIN,INPUT);

	while(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN)==1); //make sure DHT11 send LOW
	while(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN)==0); //DHT11 will send low for about 80us
	while(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN)==1); //then  will send high for about 80us


/* 3-receive 40bit Data From the DHT11*/
	for (u8 Loc_u8ByteCount=0; Loc_u8ByteCount<5; Loc_u8ByteCount++)
	{

		for (s8 Loc_s8ReceivedBitCount=7; Loc_s8ReceivedBitCount>=0; Loc_s8ReceivedBitCount--)
		{

			/*Each bit Starts with 50us LOW*/
			while(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN)==0);



			/*if Zero bit: it will be high for 26-28us, else if One Bit: it will be high for 40us*/
			_delay_us(30);

			if(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN)==1)
			{
				SET_BIT(ReceivedData[Loc_u8ByteCount],Loc_s8ReceivedBitCount);  /* then its logic HIGH */
				/*wait until low again for next bit */

				while(DIO_u8GetPinValue(DHT11_PORT,DHT11_PIN));//IT GET STUCK HERE



			}
			else
			{
				CLR_BIT(ReceivedData[Loc_u8ByteCount],Loc_s8ReceivedBitCount);
			}


		} //END Inner for

	} //END Outer For

/* 4-Back To default for the next readings*/
	/*Make the Pin OUTPUT*/
	DIO_VidSetPinDirection(DHT11_PORT,DHT11_PIN,OUTPUT);
	/*send high until the next Reading operation*/
    DIO_VidSetPinValue (DHT11_PORT,DHT11_PIN,HIGH);



return ReceivedData;

} //END Func

void DHT11_GetValues(void)
{
	u8 * pu8PointerToReceivedArray=0;

	pu8PointerToReceivedArray = pu8InitAndReceiveData();

		Integer_Humidty=pu8PointerToReceivedArray[0] ;	/* store first eight bit as Integer humidity*/
		Decimal_Humidty=pu8PointerToReceivedArray[1] ;	/* store next eight bit as Decimal humidity */
		Integer_Temp=pu8PointerToReceivedArray[2] ;	/* store next eight bit in Integer Temperature*/
		Decimal_Temp=pu8PointerToReceivedArray[3] ;	/* store next eight bit in Decimal Temperature */
		Check_Sum=pu8PointerToReceivedArray[4] ;/* store next eight bit in CheckSum */

}






