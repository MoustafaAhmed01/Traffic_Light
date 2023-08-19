 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: interrupts.h
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


/**-------------------------INCLUDES Section------------------------**/
#include "std_types.h"

/**-------------------------Definitions & Config Section------------**/
#define INT0_PORT_ID	PORTD_ID
#define INT0_PIN_ID		PIN2_ID

#define INT1_PORT_ID	PORTD_ID
#define INT1_PIN_ID		PIN3_ID

#define INT2_PORT_ID	PORTB_ID
#define INT2_PIN_ID		PIN2_ID
/**-------------------------Enum Section----------------------------**/
/*
 * Description:
 * INT0 Activate or Disable it
 */
typedef enum
{
	INT0_DISABLE,INT0_ENABLE
}INT0_EN;
/*-------------------------------------------------------------------*/

/*
 * Description:
 * INT1 Activate or Disable it
 */
typedef enum
{
	INT1_DISABLE,INT1_ENABLE
}INT1_EN;
/*-------------------------------------------------------------------*/

/*
 * Description:
 * INT2 Activate or Disable it
 */
typedef enum
{
	INT2_DISABLE,INT2_ENABLE
}INT2_EN;
/*-------------------------------------------------------------------*/

/*
 * Description:
 * Interrupt Sense control
 */
typedef enum
{
	LOW_LEVEL,ANY_CHANGE,FALLING_EDGE,RISING_EDGE
}INT_SenseControl;
/*-------------------------------------------------------------------*/
/*
 * Description:
 * Interrupt 2 Control sense
 */
typedef enum
{
	INT2_FALLING_EDGE,INT2_RISING_EDGE
}INT2_SenseControl;

/**-------------------------Struct Section--------------------------**/
/* Please copy the below comment before configuring interrupts */
/*
 * interruptZeroEN :	Enabled
 * interruptOneEN  : 	Disabled
 * interruptTwoEN  : 	Disabled
 * controlZero :		Rising
 * controlOne  :		----
 * controlTwo  :		----
 *
 */
typedef struct
{
	INT0_EN 			interruptZeroEN;
	INT1_EN 			interruptOneEN;
	INT2_EN				interruptTwoEN;
	INT_SenseControl	controlZero;
	INT_SenseControl	controlOne;
	INT2_SenseControl	controlTwo;

}INT_ConfigType;

/**-------------------------Function Dec. Section-------------------**/

/* Initializing interrupt zero */
void INT0_Init(INT_ConfigType *Config_Ptr);
/*-------------------------------------------------------------------*/

/* Initializing interrupt one */
void INT1_Init(INT_ConfigType *Config_Ptr);
/*-------------------------------------------------------------------*/

/* Initializing interrupt two */
void INT2_Init(INT_ConfigType *Config_Ptr);
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void INT0_setCallBack(void(*a_ptr)(void));
void INT1_setCallBack(void(*a_ptr)(void));
void INT2_setCallBack(void(*a_ptr)(void));

/**-------------------------END-------------------------------------**/


#endif /* INTERRUPT_H_ */
