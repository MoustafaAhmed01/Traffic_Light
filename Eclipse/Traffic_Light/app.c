/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: Main.c
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/

/**-------------------------Libraries Section---------------------**/
#include "Libraries.h"
#include "std_types.h"
#include "Traffic_Light.h"


/**-------------------------Function Def Section------------------**/


void Initializer()
{

	/* Initializing Traffic_Light */
	TL_Init();
	/*-------------------------------------------------------------------*/

	/* Activating  the SREG */
	SREG |= (1<<7);
}
/*-------------------------------------------------------------------*/

void APP_start()
{
	/* Initializing Everything at first  */
	Initializer();
}

/**-------------------------Main Section------------------**/
int main(void)
{
	/* Start */
	APP_start();

	while(1)
	{
		/* No need to do anything right here */
	}

	return 0;
}
/**-------------------------------END----------------------------**/
