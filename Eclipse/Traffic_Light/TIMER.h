/******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: TIMER.h
 *
 * Description: types for AVR
 *
 * Date Created: 15/10/2022
 *
 * Author: Moustafa Ahmed
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/**-------------------------INCLUDES Section------------------------**/

#include "std_types.h"

/**-------------------------Definitions & Config Section------------**/
#define PWM0_PORT_ID		PORTB_ID
#define PWM0_PIN_ID			PIN3_ID
/**-------------------------Enum Section----------------------------**/

/*--------------------------General Section--------------------------*/

typedef enum
{
	F_TIMER8=2,F_TIMER64,F_TIMER256,F_TIMER1024
}TIMER_prescaler;

/*--------------------------Timer0 Section--------------------------*/

/*--------------------------Timer1 Section--------------------------*/
/* Compare Output Mode for channel A */
typedef enum
{
	Normal_A,Toggle_A,Clear_A,Set_A
}TIMER1_CompareModeA;
/*-------------------------------------------------------------------*/

/* Compare Output Mode for channel B */
typedef enum
{
	Normal_B,Toggle_B,Clear_B,Set_B
}TIMER1_CompareModeB;
/*-------------------------------------------------------------------*/

/* Force Output Compare for channel A*/
typedef enum
{
	Channel_A_OFF,Channel_A_ON
}TIMER1_ForceCompareA;
/*-------------------------------------------------------------------*/

/* Force Output Compare for channel B*/
typedef enum
{
	Channel_B_OFF,Channel_B_ON
}TIMER1_ForceCompareB;
/*-------------------------------------------------------------------*/

/* Input capture noise canceler */
typedef enum
{
	NOISE_CANCELER_OFF,NOISE_CANCELER_ON
}TIMER1_NoiseControl;
/*-------------------------------------------------------------------*/

/* Input capture edge select */
typedef enum
{
	TIMER1_FALLING_EDGE,TIMER1_RAISING_EDGE
}TIMER1_EdgeControl;
/*-------------------------------------------------------------------*/

/* Controlling the waveform generation */
typedef enum
{
	NORMAL,PHASE_CORRECT_8,PHASE_CORRECT_9,PHASE_CORRECT_10,CTC_OCR1A,
	FAST_PWM_8,
	FAST_PWM_9,FAST_PWM_10,PWM_P_F_CORRECT_ICR1,PWM_P_F_CORRECT_OCR1A,
	PWM_PHASE_CORRECT_ICR1,PWM_PHASE_CORRECT_OCR1A,CTC_ICR1,RESERVED,
	FAST_PWM_OCR1,
	FAST_PWM_OCR1A

}TIMER1_WaveForm;
/*-------------------------------------------------------------------*/

/* Clock Select pre-scaling */
typedef enum
{
	NO_CLOCK,NO_PRESCALING,F_TIMER18,F_TIMER164,F_TIMER1256,F_TIMER11024,EX_FALLING,
	EX_RISING
}TIMER1_ClockSelect;
/*-------------------------------------------------------------------*/

/* Interrupt Register */
typedef enum
{
	DISABLE_INTERRUPT, ENABLE_INTERRUPT
}TIMER1_InterruptActivate;
/*-------------------------------------------------------------------*/

/*--------------------------Timer2 Section--------------------------*/


/**-------------------------Struct Section--------------------------**/

/*--------------------------Timer0 Section--------------------------*/
typedef struct
{
	TIMER_prescaler prescaler;
}TIMER0_ConfigType;

/*--------------------------Timer1 Section--------------------------*/

/* Please Copy the below comment before Initializing Timer1 */
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
 *  TCNT1_Value : 4850
 *  OCR1A_Value : 4883
 *  OCR1B_Value : ---
 */
typedef struct
{
	TIMER1_CompareModeA CompareModeA;
	TIMER1_CompareModeB CompareModeB;
	TIMER1_ForceCompareA ForceCompareA;
	TIMER1_ForceCompareB ForceCompareB;
	TIMER1_EdgeControl EdgeControl;
	TIMER1_NoiseControl NoiseControl;
	TIMER1_ClockSelect F_TIMER1_CLOCK;
	TIMER1_WaveForm WaveForm;
	TIMER1_InterruptActivate interruptA;
	TIMER1_InterruptActivate interruptB;
	TIMER1_InterruptActivate interruptOvf;
	uint16 TCNT1_Value;
	uint16 OCR1A_Value;
	uint16 OCR1B_Value;

}TIMER1_ConfigType;
/*--------------------------Timer2 Section--------------------------*/

/**-------------------------Function Dec. Section-------------------**/

/*
 * Initializing Timer1
 */
void Timer1_Init(TIMER1_ConfigType *Config_Ptr);
/*-------------------------------------------------------------------*/

/* Description: Function to set the Call Back function address. */
void Timer1_setCallBackOneA(void(*a_ptr)(void));
/*-------------------------------------------------------------------*/
/* Description: Function to set the Call Back function address. */
void Timer1_setCallBackOneB(void(*a_ptr)(void));
/*-------------------------------------------------------------------*/

/*
 * Initializing Timer0_PWM
 */
void Timer0_PWM_Init(TIMER0_ConfigType *Config_Ptr);
/*-------------------------------------------------------------------*/

/*
 * Setting Timer0_PWM
 */
void Timer0_PWM_Activate(uint8 *SetDuty_Ptr);
/*-------------------------------------------------------------------*/

/**-------------------------END-------------------------------------**/

#endif /* TIMER_H_ */
