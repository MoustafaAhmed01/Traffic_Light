/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: Traffic_Light.c
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------INCLUDES Section------------------------**/
#include "Libraries.h"
#include "Traffic_Light.h"
#include "TIMER.h"
#include "interrupt.h"
#include "GPIO.h"

/**-------------------------Global Variables Section----------------**/
TL_LED ColorState = Green;

volatile uint8 g_Flag = 0;
volatile uint8 e_Yellow_Flag = 0;
volatile uint8 e_Button_Pushed = 0;
/**-------------------------Function Definition Section-------------**/

/*
 * Description Initializing the traffic light
 */
void TL_Init(void)
{
	/* Setting up pins direction */
	/* Setting car led pins */
	GPIO_setupPinDirection(CAR_PORT_ID, CAR_GREEN_LED_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(CAR_PORT_ID, CAR_YELLOW_LED_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(CAR_PORT_ID, CAR_RED_LED_ID, PIN_OUTPUT);

	/* Setting passenger traffic light pins */
	GPIO_setupPinDirection(PEDESTRIAN_PORT_ID, PEDESTRIAN_GREEN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PEDESTRIAN_PORT_ID, PEDESTRIAN_RED_ID, PIN_OUTPUT);
	/*---------------------------------------------------------------*/
	/*
	 	 * file name: TIMER.h
	 	 *  -> Structure Configuration:
	 	 *
	 	 *  CompareModeA : Normal
	 	 *  CompareModeB : Normal
	 	 *  ForceCompareA : Activated
	 	 *  ForceCompareB : Disabled
	 	 *  EdgeControl : ---
	 	 *  NoiseControl : Disabled
	 	 *  F_TIMER1_CLOCK : F_CPU/1024
	 	 *  WaveForm : CTC mode ,TOP: OCR1A
	 	 *  interruptA : Enabled
	 	 *  interruptB : Disabled
	 	 *  interruptOvf : Disabled
	 	 *  TCNT1_Value : 970
	 	 *  OCR1A_Value : 976
	 	 *  OCR1B_Value : ---
	 */

		TIMER1_ConfigType Timer1_Config={Normal_A,Normal_B,Channel_A_ON,Channel_B_OFF,TIMER1_FALLING_EDGE,NOISE_CANCELER_OFF,F_TIMER11024,CTC_OCR1A,ENABLE_INTERRUPT,DISABLE_INTERRUPT,DISABLE_INTERRUPT,970,976,0};
		Timer1_Init(&Timer1_Config);

		/* Initializing the call back function */
		Timer1_setCallBackOneA(TL_NormalSystemISR);
		Timer1_setCallBackOneB(TL_YellowBlinking);
/*-------------------------------------------------------------------*/

		/*
			 * Initializing Interrupt 0
			 *
			 * interruptZeroEN :	Enabled
			 * interruptOneEN  : 	Disabled
			 * interruptTwoEN  : 	Disabled
			 * controlZero :		Rising
			 * controlOne  :		----
			 * controlTwo  :		----
			 *
		 */
			INT_ConfigType INT_Config = {INT0_ENABLE,INT1_DISABLE,INT2_DISABLE,RISING_EDGE,0,0};
			INT0_Init(&INT_Config);

			INT0_setCallBack(TL_PedestrianISR);
}
/*-------------------------------------------------------------------*/

/*
 * Description:
 * Used by the Pedestrian button
 */
void TL_PedestrianISR(void)
{
	if(ColorState == Yellow_2) /* If the traffic car is Red do nothing */
	{
		/* Nothing to do */
	}
	else if(ColorState == Yellow_1 || ColorState == Green || ColorState == Red) /* This is the next state, which means if the car is right now is green or yellow */
	{
		/* Start from yellow sign */
		ColorState = Yellow_1;
		e_Button_Pushed =1;
		TCNT1 = 970;
	}
}
/*-------------------------------------------------------------------*/
/*
 * Description:
 * Yellow Blinking
 */
void TL_YellowBlinking(void)
{
	if(g_Flag == 0)
	{
		GPIO_writePin(CAR_PORT_ID, CAR_YELLOW_LED_ID, LOGIC_LOW);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, LOGIC_LOW);

		g_Flag = 1;
	}
	else
	{
		GPIO_writePin(CAR_PORT_ID, CAR_YELLOW_LED_ID, LOGIC_HIGH);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, LOGIC_HIGH);
		g_Flag = 0;
	}
}
/*-------------------------------------------------------------------*/

/* Function will be called every interrupt to handle the passenger request */
void TL_NormalSystemISR(void)
{
	/* Setting up the conditions */
	if(ColorState == Green)
	{
		/* Activating the CAR Green Color */
		GPIO_writePin(CAR_PORT_ID, CAR_GREEN_LED_ID, LOGIC_HIGH);
		GPIO_writePin(CAR_PORT_ID, CAR_YELLOW_LED_ID, LOGIC_LOW);
		GPIO_writePin(CAR_PORT_ID, CAR_RED_LED_ID, LOGIC_LOW);

		/* Activating the Pedestrian Red Color */
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_GREEN_ID, LOGIC_LOW);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, LOGIC_LOW);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_RED_ID, LOGIC_HIGH);

		/* Setting the yellow flag to zero */
		e_Yellow_Flag = 0;
		/* Switching to Yellow color on the next step */
		ColorState = Yellow_1;
	}
	else if(ColorState == Yellow_1 || ColorState == Yellow_2)
	{
		/* Activating the CAR yellow Color */
		GPIO_writePin(CAR_PORT_ID, CAR_GREEN_LED_ID, LOGIC_LOW);
		GPIO_writePin(CAR_PORT_ID, CAR_YELLOW_LED_ID, LOGIC_HIGH);
		GPIO_writePin(CAR_PORT_ID, CAR_RED_LED_ID, LOGIC_LOW);

		/* Activating the Pedestrian Red Color */
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_GREEN_ID, LOGIC_LOW);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, LOGIC_HIGH);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_RED_ID, LOGIC_LOW);

		/* Setting the yellow flag to one */
		e_Yellow_Flag = 1;

		/* Switching to Red color on the next step or back to green if it was on red */
		if(ColorState == Yellow_1)
		{
			ColorState = Red;
		}
		else
		{
			ColorState = Green;
		}
	}
	else
	{
		/* Activating the CAR Red Color */
		GPIO_writePin(CAR_PORT_ID, CAR_GREEN_LED_ID, LOGIC_LOW);
		GPIO_writePin(CAR_PORT_ID, CAR_YELLOW_LED_ID, LOGIC_LOW);
		GPIO_writePin(CAR_PORT_ID, CAR_RED_LED_ID, LOGIC_HIGH);

		/* Activating the Pedestrian Red Color */
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_GREEN_ID, LOGIC_HIGH);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_YELLOW_ID, LOGIC_LOW);
		GPIO_writePin(PEDESTRIAN_PORT_ID, PEDESTRIAN_RED_ID, LOGIC_LOW);

		/* Setting the yellow flag to zero */
		e_Yellow_Flag = 0;

		/* Switching to Green color on the next step */
		ColorState = Yellow_2;
	}

	/* Letting the timer to start over again */
	TCNT1 = 0;
}
/*-------------------------------------------------------------------*/


/**---------------------------------END-----------------------------**/
