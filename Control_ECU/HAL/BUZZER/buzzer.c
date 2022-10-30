 /******************************************************************************
 *
 * [FILE NAME]: <buzzer.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <25/10/2022>
 *
 * [DESCRIPTION]: <Source file for BUZZER Driver>
 *
 *******************************************************************************/

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: A function that initialize the buzzer.
 *
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection (BUZZER_PORT_ID , BUZZER_PIN_1 , PIN_OUTPUT);


	GPIO_writePin (BUZZER_PORT_ID , BUZZER_PIN_1 , LOGIC_LOW);
}

/*
 * Description: A function that start the buzzer.
 *
 */
void Buzzer_on(void)
{
	GPIO_writePin (BUZZER_PORT_ID , BUZZER_PIN_1 , LOGIC_HIGH);
}


/*
 * Description: A function that stop the buzzer.
 *
 */
void Buzzer_off(void)
{
	GPIO_writePin (BUZZER_PORT_ID , BUZZER_PIN_1 , LOGIC_LOW);
}
