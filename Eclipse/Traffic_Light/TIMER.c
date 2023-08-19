/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: TIMER.c
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
#include "GPIO.h"
#include "TIMER.h"

/**-------------------------Global Variables Section----------------**/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrA)(void) = NULL_PTR;
static volatile void (*g_callBackPtrB)(void) = NULL_PTR;
uint8 g_EnterCounter = 0;

/**-------------------------Extern Section----------------**/
extern uint8 e_Yellow_Flag;
extern uint8 e_Button_Pushed;
/**-------------------------Interrupts Section----------------------**/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtrA != NULL_PTR)
	{
		if(g_callBackPtrB != NULL_PTR)
		{
			if(e_Button_Pushed == 1) /* If the Push Button was pressed INT0 */
			{
				g_EnterCounter = 6;
				e_Button_Pushed= 0;
			}

			if(e_Yellow_Flag == 1) /* To start blinking the yellow LED */
			{
				/* Call the Call Back function in the application after the edge is detected */
				(*g_callBackPtrB)(); /* another method to call the function using pointer to function g_callBackPtr(); */
			}

			if(g_EnterCounter == 0 || g_EnterCounter == 6)
			{
				/* Call the Call Back function in the application after the edge is detected */
				(*g_callBackPtrA)(); /* another method to call the function using pointer to function g_callBackPtr(); */
				g_EnterCounter = 1; /* Start over again */
			}
		}
	}
	g_EnterCounter++;
}

ISR(TIMER1_COMPB_vect)
{

}

/**-------------------------Function Definition Section-------------**/

/*
 * Initializing TIMER0
 */
void Timer1_Init(TIMER1_ConfigType *Config_Ptr)
{
		/* Compare Output Mode for channel A */
		TCCR1A = (TCCR1A & 0x3F) | (Config_Ptr->CompareModeA<<6);

		/* Compare Output Mode for channel B */
		TCCR1A = (TCCR1A & 0xCF) | (Config_Ptr->CompareModeB<<4);

		/* Force Output Compare for Channel A */
		TCCR1A = (TCCR1A & 0xF7) | (Config_Ptr->ForceCompareA<<3);

		/* Force Output Compare for Channel B */
		TCCR1A = (TCCR1A & 0xFB) | (Config_Ptr->ForceCompareB<<2);

		/* Setting the waveform */
		TCCR1A = (TCCR1A & 0xFC) | ((Config_Ptr->WaveForm<<6)>>6); /* Getting the first 2 bits only */
		TCCR1B = (TCCR1B & 0xE7) | ((Config_Ptr->WaveForm>>2)<<3); /* Getting bit 2 and 3 only*/

		/* Noise Canceler */
		TCCR1B = (TCCR1B & 0x7F) | ((Config_Ptr->NoiseControl)<<7);

		/* Edge Select */
		TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->EdgeControl)<<ICES1);

		/* Clock Selection */
		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->F_TIMER1_CLOCK);

		/* Enable compare A interrupt */
		TIMSK = (TIMSK & 0xEF) | ((Config_Ptr->interruptA)<<OCIE1A);

		/* Enable compare B interrupt */
		TIMSK = (TIMSK & 0xF7) | ((Config_Ptr->interruptB)<<OCIE1B);

		/* Enable OverFlow interrupt */
		TIMSK = (TIMSK & 0xFB) | ((Config_Ptr->interruptOvf)<<TOIE1);

		/* Initial Value for Timer1 */
		TCNT1 = Config_Ptr->TCNT1_Value;

		/* Initializing the compare value register */
		OCR1A = Config_Ptr->OCR1A_Value;
		OCR1B = Config_Ptr->OCR1B_Value;
}

/*---------------------------------------------------------------------*/

/*
 * Initializing Timer0_PWM
 */
void Timer0_PWM_Init(TIMER0_ConfigType *Config_Ptr)
{
	TCNT0 = 0; /* Set Timer Initial Value to 0 */

	/* Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC */
	GPIO_setupPinDirection(PWM0_PORT_ID, PWM0_PIN_ID, PIN_OUTPUT);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = Dependent on the user
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01);
	TCCR0 |= Config_Ptr->prescaler;
}

/*----------------------------------------------------------------------------*/

/*
 * Setting Timer0_PWM
 */
void Timer0_PWM_Activate(uint8 *SetDuty_Ptr)
{
	TCNT0 = 0; /* Set Timer Initial Value to 0 */
	OCR0  = *SetDuty_Ptr; /* Set Compare Value */
}

/*----------------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void Timer1_setCallBackOneA(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrA = a_ptr;
}
/*----------------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void Timer1_setCallBackOneB(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrB = a_ptr;
}
/**---------------------------------END-----------------------------**/
