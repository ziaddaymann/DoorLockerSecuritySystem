 /******************************************************************************
 *
 * [FILE NAME]: <timer.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <25/10/2022>
 *
 * [DESCRIPTION]: <Header file for TIMER1 Driver>
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../../LIB/std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER1_MAX_VALUE 65535

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NORMAL , COMPARE
} Timer1_Mode;

typedef enum
{
	No_clock,No_prescaling,Prescale_8,Prescale_64,Prescale_256,Prescale_1024
}Timer1_Clock;

typedef struct
{
		Timer1_Mode mode;
		uint16 initialvalue;
		uint16 comparevalue;
		Timer1_Clock prescale;
}Timer1_Configtype;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: A function that initialize a timer1 with dynamic configurations.
 *
 */
void Timer1_init(const Timer1_Configtype * Config_Ptr);

/*
 * Description: A function that Deinitialize a timer1 with dynamic configurations.
 *
 */
void Timer1_deInit(void);

/*
 * Description: A function that Call Back A Function.
 *
 */
void Timer1_setCallBack(void(*a_ptr)(void));

/*
 * Description: A function that set a new value.
 *
 */
void Timer1_setValue (uint8 newValue);

/*
 * Description: A function that clear the value.
 *
 */
void Timer1_clearValue(void);






#endif /* TIMER_H_ */
