/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: interrupts.c
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
#include "interrupt.h"
/**-------------------------Global Variables Section----------------**/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

/**-------------------------Interrupts Section----------------------**/

ISR(INT0_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*-------------------------------------------------------------------*/

ISR(INT1_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*-------------------------------------------------------------------*/

ISR(INT2_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/**-------------------------Function Definition Section-------------**/

/* Initializing interrupt zero */
void INT0_Init(INT_ConfigType *Config_Ptr)
{
	/* Initializing the pin direction as input pin */
	GPIO_setupPinDirection(INT0_PORT_ID, INT0_PIN_ID, PIN_INPUT);

	/* Interrupt Sense Control */
	MCUCR = (MCUCR & 0xFC) | ((Config_Ptr->controlZero));

	/* Enable the interrupt */
	GICR = (GICR & 0xBF) | ((Config_Ptr->interruptZeroEN)<<INT0);
}
/*-------------------------------------------------------------------*/

/* Initializing interrupt one */
void INT1_Init(INT_ConfigType *Config_Ptr)
{
	/* Initializing the pin direction as input pin */
	GPIO_setupPinDirection(INT1_PORT_ID, INT1_PIN_ID, PIN_INPUT);

	/* Interrupt Sense Control */
	MCUCR = (MCUCR & 0xF3) | ((Config_Ptr->controlOne)<<2);

	/* Enable the interrupt */
	GICR = (GICR & 0x7F) | ((Config_Ptr->interruptOneEN)<<INT1);
}
/*-------------------------------------------------------------------*/

/* Initializing interrupt two */
void INT2_Init(INT_ConfigType *Config_Ptr)
{
	/* Initializing the pin direction as input pin */
	GPIO_setupPinDirection(INT2_PORT_ID, INT2_PIN_ID, PIN_INPUT);

	/* Interrupt Sense Control */
	MCUCSR = (MCUCSR & 0xBF) | ((Config_Ptr->controlTwo)<<ISC2);

	/* Enable the interrupt */
	GICR = (GICR & 0xDF) | ((Config_Ptr->interruptTwoEN)<<INT2);

}
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void INT0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = a_ptr;
}
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void INT1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = a_ptr;
}
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void INT2_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}

/**---------------------------------END-----------------------------**/
