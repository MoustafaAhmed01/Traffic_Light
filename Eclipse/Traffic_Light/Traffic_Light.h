 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: Traffic_Light.h
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

/**-------------------------INCLUDES Section------------------------**/
#include "std_types.h"

/**-------------------------Definitions & Config Section------------**/
#define CAR_PORT_ID				PORTA_ID
#define CAR_GREEN_LED_ID		PIN0_ID
#define CAR_YELLOW_LED_ID		PIN1_ID
#define CAR_RED_LED_ID			PIN2_ID

#define PEDESTRIAN_PORT_ID		PORTB_ID
#define PEDESTRIAN_GREEN_ID		PIN0_ID
#define PEDESTRIAN_YELLOW_ID	PIN1_ID
#define PEDESTRIAN_RED_ID		PIN2_ID
/**-------------------------Enum Section----------------------------**/
typedef enum
{
	Green,Yellow_1,Red,Yellow_2
}TL_LED;
/**-------------------------Function Dec. Section-------------------**/
/*
 * Description Initializing the traffic light
 */
void TL_Init(void);
/*-------------------------------------------------------------------*/
/*
 * Description:
 * Yellow Blinking
 */
void TL_YellowBlinking(void);
/*-------------------------------------------------------------------*/

/*
 * Description:
 * Used by the Pedestrian button
 */
void TL_PedestrianISR(void);

/*-------------------------------------------------------------------*/

/*
 * Description :
 * Function will be called every timer interrupt
 */
void TL_NormalSystemISR(void);
/**-------------------------END-------------------------------------**/


#endif /* TRAFFIC_LIGHT_H_ */
